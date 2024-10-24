#include <ncurses.h>
#include "EstruturaConsole.h"

void draw_progress_bar(int y, int x, int position, int max_width) {
    mvprintw(y, x, "[");
    for (int i = 1; i < max_width; ++i) {
        if (i <= position)
            mvprintw(y, x + i, "=");  // Preenchimento da barra
        else
            mvprintw(y, x + i, " ");
    }
    mvprintw(y, x + max_width, "]");
    refresh();
}

void display_atuadores_status() {
    mvprintw(1, 1, "+------------------------------+");
    mvprintw(2, 1, "|          Atuadores           |");
    mvprintw(3, 1, "+------------------------------+");
    mvprintw(4, 1, "| 1. Aquecedor:          [ON]  |");
    mvprintw(5, 1, "| 2. Ar Condicionado:    [OFF] |");
    mvprintw(6, 1, "| 3. Desumidificador:    [OFF] |");
    mvprintw(7, 1, "| 4. Lâmpada:            [ON]  |");
    mvprintw(8, 1, "| 5. Umidificador:       [ON]  |");
    mvprintw(9, 1, "| 6. Ventilador:         [OFF] |");
    mvprintw(10, 1, "+------------------------------+");
}

void display_sensores_status() {
    mvprintw(12, 1, "+------------------------------+");
    mvprintw(13, 1, "|           Sensores           |");
    mvprintw(14, 1, "+------------------------------+");
    mvprintw(15, 1, "| 1. Temperatura:        22°C  |");
    mvprintw(16, 1, "| 2. Umidade:            60%%   |");
    mvprintw(17, 1, "| 3. Luminosidade:       75%%   |");
    mvprintw(18, 1, "| 4. Presença:           [DETECTADO] |");
    mvprintw(19, 1, "+------------------------------+");
}

void run_console() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    int max_width = 20;  // Largura máxima das barras de progresso
    int light_position = 10;  // Posição inicial da barra de luminosidade
    int temp_position = 10;   // Posição inicial da barra de temperatura

    MEVENT event;

    while (true) {
        clear();  // Limpa a tela para redesenhar

        display_atuadores_status();  // Mostra o status dos atuadores
        display_sensores_status();   // Mostra o status dos sensores

        // Desenha a barra de progresso para controle de luminosidade
        mvprintw(21, 1, "+---------------------------------+");
        mvprintw(22, 1, "| Controle de Intensidade da Luz: |");
        draw_progress_bar(23, 1, light_position, max_width);

        // Desenha a barra de progresso para controle de temperatura
        mvprintw(25, 1, "+----------------------------------+");
        mvprintw(26, 1, "| Controle de Temperatura:       |");
        draw_progress_bar(27, 1, temp_position, max_width);
        mvprintw(28, 1, "+----------------------------------+");

        int ch = getch();
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_PRESSED) {
                    // Controle da barra de intensidade da luz
                    if (event.y == 23) {
                        light_position = (event.x - 2);  // Ajusta posição com base no clique
                        if (light_position < 0) light_position = 0;
                        if (light_position > max_width) light_position = max_width;
                    }
                    // Controle da barra de temperatura
                    if (event.y == 27) {
                        temp_position = (event.x - 2);  // Ajusta posição com base no clique
                        if (temp_position < 0) temp_position = 0;
                        if (temp_position > max_width) temp_position = max_width;
                    }
                }
            }
        } else if (ch == 's') {
            break;  // Pressiona 's' para sair
        }
    }

    endwin();
}
