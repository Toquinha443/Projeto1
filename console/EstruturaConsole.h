#ifndef ESTRUTURA_CONSOLE_H
#define ESTRUTURA_CONSOLE_H

#include <ncurses.h>

// Declaração da função para desenhar a barra de progresso
void draw_progress_bar(int position, int max_width);

// Função para rodar o console
void run_console();

#endif
