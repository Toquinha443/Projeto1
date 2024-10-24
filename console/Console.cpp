#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

// Função que limpa o console de forma dinâmica
void limparConsole()
{
#ifdef _WIN32
    system("cls");  // Limpa o console no Windows
#else
    system("clear"); // Limpa o console em sistemas UNIX (Linux e macOS)
#endif
}

// Função que imprime as informações dos sensores e atuadores de forma fluida para três salas
void atualizarConsole(const std::string& nomeSala1, int temperaturaAtual1, int aquecedorStatus1, int configAquecedor1,
                      int ventiladorStatus1, int configVentilador1, int arCondicionadoStatus1, int configArCondicionado1,
                      int luxAtual1, int lampadaStatus1, int configLampada1, int umidade1, int umidificadorStatus1,
                      int configUmidificador1, int desumidificadorStatus1, int configDesumidificador1,

                      const std::string& nomeSala2, int temperaturaAtual2, int aquecedorStatus2, int configAquecedor2,
                      int ventiladorStatus2, int configVentilador2, int arCondicionadoStatus2, int configArCondicionado2,
                      int luxAtual2, int lampadaStatus2, int configLampada2, int umidade2, int umidificadorStatus2,
                      int configUmidificador2, int desumidificadorStatus2, int configDesumidificador2,

                      const std::string& nomeSala3, int temperaturaAtual3, int aquecedorStatus3, int configAquecedor3,
                      int ventiladorStatus3, int configVentilador3, int arCondicionadoStatus3, int configArCondicionado3,
                      int luxAtual3, int lampadaStatus3, int configLampada3, int umidade3, int umidificadorStatus3,
                      int configUmidificador3, int desumidificadorStatus3, int configDesumidificador3,

                      int horas, int minutos)
{
    limparConsole();

    // Horário
    std::cout << "=========================================\n";
    std::cout << "Horário: " << std::setfill('0') << std::setw(2) << horas << ":" << std::setfill('0') << std::setw(2) << minutos << std::endl;
    std::cout << "=========================================\n";

    // Exibe informações para cada sala
    auto exibirInformacoesSala = [](const std::string& nomeSala, int temperatura, int aquecedorStatus, int configAquecedor,
                                    int ventiladorStatus, int configVentilador, int arCondicionadoStatus, int configArCondicionado,
                                    int lux, int lampadaStatus, int configLampada, int umidade, int umidificadorStatus,
                                    int configUmidificador, int desumidificadorStatus, int configDesumidificador)
    {
        std::cout << "=== " << nomeSala << " ===" << std::endl;
        std::cout << "Temperatura Atual: " << temperatura << "°C" << std::endl;
        std::cout << "Aquecedor: " << (aquecedorStatus ? "Ligado" : "Desligado") << " | Configuração: " << configAquecedor << std::endl;
        std::cout << "Ventilador: " << (ventiladorStatus ? "Ligado" : "Desligado") << " | Configuração: " << configVentilador << std::endl;
        std::cout << "Ar Condicionado: " << (arCondicionadoStatus ? "Ligado" : "Desligado") << " | Configuração: " << configArCondicionado << std::endl;
        std::cout << "Lux: " << lux << " lux | Lâmpada: " << (lampadaStatus ? "Ligada" : "Desligada") << " | Configuração: " << configLampada << "%" << std::endl;
        std::cout << "Umidade: " << umidade << "% | Umidificador: " << (umidificadorStatus ? "Ligado" : "Desligado") << " | Configuração: " << configUmidificador << std::endl;
        std::cout << "Desumidificador: " << (desumidificadorStatus ? "Ligado" : "Desligado") << " | Configuração: " << configDesumidificador << std::endl;
        std::cout << "-----------------------------------------\n";
    };

    exibirInformacoesSala(nomeSala1, temperaturaAtual1, aquecedorStatus1, configAquecedor1,
                          ventiladorStatus1, configVentilador1, arCondicionadoStatus1, configArCondicionado1,
                          luxAtual1, lampadaStatus1, configLampada1, umidade1, umidificadorStatus1,
                          configUmidificador1, desumidificadorStatus1, configDesumidificador1);

    exibirInformacoesSala(nomeSala2, temperaturaAtual2, aquecedorStatus2, configAquecedor2,
                          ventiladorStatus2, configVentilador2, arCondicionadoStatus2, configArCondicionado2,
                          luxAtual2, lampadaStatus2, configLampada2, umidade2, umidificadorStatus2,
                          configUmidificador2, desumidificadorStatus2, configDesumidificador2);

    exibirInformacoesSala(nomeSala3, temperaturaAtual3, aquecedorStatus3, configAquecedor3,
                          ventiladorStatus3, configVentilador3, arCondicionadoStatus3, configArCondicionado3,
                          luxAtual3, lampadaStatus3, configLampada3, umidade3, umidificadorStatus3,
                          configUmidificador3, desumidificadorStatus3, configDesumidificador3);
}
