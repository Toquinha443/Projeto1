#include "./ambientes/Sala.cpp"

#include "./sensores/Temperatura.cpp"
#include "./atuadores/Aquecedor.cpp"
#include "./atuadores/Ventilador.cpp"
#include "./atuadores/ArCondicionado.cpp"

#include "./sensores/Luminosidade.cpp"
#include "./atuadores/Lampada.cpp"

#include "./sensores/Umidade.cpp"
#include "./atuadores/Umidificador.cpp"
#include "./atuadores/Desumidificador.cpp"

#include "./console/Console.cpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

int main()
{
    // Criando três salas de coworking com parâmetros diferentes
    Sala sala1("Sala de Reunião", 20, 500, 70);
    Sala sala2("Open Space", 22, 600, 65);
    Sala sala3("Área de Concentração", 24, 700, 60);

    // Adicionando sensores e atuadores na Sala de Reunião
    sala1.adicionarSensor(new Temperatura("Temperatura"));
    sala1.adicionarAtuador(new Aquecedor("Aquecedor"));
    sala1.adicionarAtuador(new Ventilador("Ventilador"));
    sala1.adicionarAtuador(new ArCondicionado("ArCondicionado"));
    sala1.adicionarSensor(new Luminosidade("Luminosidade"));
    sala1.adicionarAtuador(new Lampada("Lampada"));
    sala1.adicionarSensor(new Umidade("Umidade"));
    sala1.adicionarAtuador(new Umidificador("Umidificador"));
    sala1.adicionarAtuador(new Desumidificador("Desumidificador"));

    // Adicionando sensores e atuadores no Open Space
    sala2.adicionarSensor(new Temperatura("Temperatura"));
    sala2.adicionarAtuador(new Aquecedor("Aquecedor"));
    sala2.adicionarAtuador(new Ventilador("Ventilador"));
    sala2.adicionarAtuador(new ArCondicionado("ArCondicionado"));
    sala2.adicionarSensor(new Luminosidade("Luminosidade"));
    sala2.adicionarAtuador(new Lampada("Lampada"));
    sala2.adicionarSensor(new Umidade("Umidade"));
    sala2.adicionarAtuador(new Umidificador("Umidificador"));
    sala2.adicionarAtuador(new Desumidificador("Desumidificador"));

    // Adicionando sensores e atuadores na Área de Concentração
    sala3.adicionarSensor(new Temperatura("Temperatura"));
    sala3.adicionarAtuador(new Aquecedor("Aquecedor"));
    sala3.adicionarAtuador(new Ventilador("Ventilador"));
    sala3.adicionarAtuador(new ArCondicionado("ArCondicionado"));
    sala3.adicionarSensor(new Luminosidade("Luminosidade"));
    sala3.adicionarAtuador(new Lampada("Lampada"));
    sala3.adicionarSensor(new Umidade("Umidade"));
    sala3.adicionarAtuador(new Umidificador("Umidificador"));
    sala3.adicionarAtuador(new Desumidificador("Desumidificador"));

    // Simulação de atualização dos sensores e atuadores por 1440 minutos (1 dia)
    for (int i = 0; i < 1440; i++) // 1440 minutos em um dia
    {
        // Calcula o horário correspondente à repetição atual (começando em 00:00)
        int horas = i / 60;
        int minutos = i % 60;

        // Atualizando sensores e atuadores de cada sala
        sala1.atualizarSensores(i);
        sala1.atualizarAtuadores(i);
        sala2.atualizarSensores(i);
        sala2.atualizarAtuadores(i);
        sala3.atualizarSensores(i);
        sala3.atualizarAtuadores(i);

        // Atualiza o console com as informações das três salas
        atualizarConsole(
            sala1.getNomeSala(), // Nome da sala
            static_cast<int>(sala1.getTemperaturaAtual(1)), sala1.getStatusAquecedor(), sala1.getConfigAquecedor(),
            sala1.getStatusVentilador(), sala1.getConfigVentilador(), sala1.getStatusArCondicionado(), sala1.getConfigArCondicionado(),
            static_cast<int>(sala1.getLuxAtual()), sala1.getStatusLampada(), sala1.getConfigLampada(),
            static_cast<int>(sala1.getUmidade()), sala1.getStatusUmidificador(), sala1.getConfigUmidificador(),
            sala1.getStatusDesumidificador(), sala1.getConfigDesumidificador(),
            sala2.getNomeSala(), // Nome da sala
            static_cast<int>(sala2.getTemperaturaAtual(1)), sala2.getStatusAquecedor(), sala2.getConfigAquecedor(),
            sala2.getStatusVentilador(), sala2.getConfigVentilador(), sala2.getStatusArCondicionado(), sala2.getConfigArCondicionado(),
            static_cast<int>(sala2.getLuxAtual()), sala2.getStatusLampada(), sala2.getConfigLampada(),
            static_cast<int>(sala2.getUmidade()), sala2.getStatusUmidificador(), sala2.getConfigUmidificador(),
            sala2.getStatusDesumidificador(), sala2.getConfigDesumidificador(),
            sala3.getNomeSala(), // Nome da sala
            static_cast<int>(sala3.getTemperaturaAtual(1)), sala3.getStatusAquecedor(), sala3.getConfigAquecedor(),
            sala3.getStatusVentilador(), sala3.getConfigVentilador(), sala3.getStatusArCondicionado(), sala3.getConfigArCondicionado(),
            static_cast<int>(sala3.getLuxAtual()), sala3.getStatusLampada(), sala3.getConfigLampada(),
            static_cast<int>(sala3.getUmidade()), sala3.getStatusUmidificador(), sala3.getConfigUmidificador(),
            sala3.getStatusDesumidificador(), sala3.getConfigDesumidificador(),
            horas, minutos
        );

        // Pausa de 500ms entre cada minuto simulado
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Controle do tempo de atualização
        std::cout << "----------------------\n";
    }

    return 0;
}
