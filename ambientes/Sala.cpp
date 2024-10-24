#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "../sensores/Sensor.cpp"
#include "../atuadores/Atuador.cpp"

// Classe Sala que gerencia sensores e atuadores para controle de temperatura e luminosidade
class Sala
{
private:
    // Vetores para armazenar os sensores e atuadores da sala
    std::vector<Sensor *> sensores;
    std::vector<Atuador *> atuadores;

    // Parâmetros desejados para temperatura e luminosidade
    std::string nome;
    int temperaturaDesejada;
    int luxDesejado;
    int umidadeDesejada;

public:
    // Construtor que inicializa a sala
    Sala(std::string nomeSala, int tempDesejada, int luxInicial, int umidDesejada)
        : nome(nomeSala), temperaturaDesejada(tempDesejada), luxDesejado(luxInicial), umidadeDesejada(umidDesejada)
    {
        std::srand(std::time(nullptr)); // Inicializa a semente para geração de números aleatórios
    }
    // Adiciona um sensor à sala
    void adicionarSensor(Sensor *sensor)
    {
        sensores.push_back(sensor);
    }

    // Adiciona um atuador à sala
    void adicionarAtuador(Atuador *atuador)
    {
        atuadores.push_back(atuador);
    }

    // Retorna o nome da sala
    std::string getNomeSala() const
    {
        return nome;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////

    // Atualiza os sensores, verificando e ajustando a temperatura e luminosidade
    void atualizarSensores(int minutos)
    {
        for (auto sensor : sensores)
        {
            if (sensor != nullptr && sensor->getNome().find("Temperatura") != std::string::npos)
            {
                // Inicializa temperatura se for o valor padrão e ajusta o ambiente
                sensor->setSensor((sensor->getValor() == 304) ? 40 : sensor->getValor());
                ajustarTemperaturaAmbiente(sensor);
            }
            if (sensor != nullptr && sensor->getNome().find("Luminosidade") != std::string::npos)
            {
                // Calibra o sensor de luminosidade e ajusta o ambiente
                sensor->setCalibraSensor(luxDesejado);
                sensor->setSensor((sensor->getValor() == 304) ? 0 : sensor->getValor());
                ajustarLuminosidadeAmbiente(sensor, minutos);
            }
            if (sensor != nullptr && sensor->getNome().find("Umidade") != std::string::npos)
            {
                // Calibra o sensor de luminosidade e ajusta o ambiente
                sensor->setSensor((sensor->getValor() == 304) ? 0 : sensor->getValor());
                ajustarUmidadeAmbiente(sensor);
            }
        }
    }

    // Atualiza os atuadores com base nos valores dos sensores (Temperatura e Luminosidade)
    void atualizarAtuadores(int minutos)
    {
        for (auto sensor : sensores)
        {
            if (sensor != nullptr && sensor->getNome().find("Temperatura") != std::string::npos)
            {
                // Ajusta os atuadores de temperatura com base nos valores dos sensores
                ajustarAtuadoresTemperatura(sensor);
            }
            if (sensor != nullptr && sensor->getNome().find("Luminosidade") != std::string::npos)
            {
                // Ajusta o brilho da lâmpada com base nos valores dos sensores
                ajustarAtuadoresLampada(sensor, minutos);
            }
            if (sensor != nullptr && sensor->getNome().find("Umidade") != std::string::npos)
            {
                // Ajusta o brilho da lâmpada com base nos valores dos sensores
                ajustarAtuadoresUmidade(sensor);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////

    // Função para ajustar os atuadores de temperatura com base no sensor
    void ajustarAtuadoresTemperatura(Sensor *sensor)
    {
        int diferencaTemperatura = sensor->getValor() - temperaturaDesejada;

        if (sensor->getValor() < temperaturaDesejada)
        {
            // Liga o aquecedor e desliga ventilador e ar-condicionado
            atualizarAquecedor(true, 1);
            atualizarVentilador(false, 0);
            atualizarArCondicionado(false, 0);
        }
        else if (diferencaTemperatura >= 8) // Diferença maior ou igual a 8 graus
        {
            // Resfriamento rápido: liga ventilador e ar-condicionado
            atualizarAquecedor(false, 0);
            atualizarVentilador(true, 2);
            atualizarArCondicionado(true, 1);
        }
        else if (sensor->getValor() > temperaturaDesejada)
        {
            // Ajusta ventilador ou ar-condicionado com base na temperatura atual
            if (sensor->getValor() > 22)
            {
                atualizarAquecedor(false, 0);
                atualizarVentilador(true, 1);
                atualizarArCondicionado(false, 0);
            }
            else
            {
                atualizarAquecedor(false, 0);
                atualizarVentilador(false, 0);
                atualizarArCondicionado(true, 1);
            }
        }
        else
        {
            // Temperatura estável: desliga todos os atuadores
            atualizarAquecedor(false, 0);
            atualizarVentilador(false, 0);
            atualizarArCondicionado(false, 0);
        }
    }

    // Ajusta o brilho da lâmpada com base no sensor de luminosidade
    void ajustarAtuadoresLampada(Sensor *sensor, int minutos)
    {
        if (sensor == nullptr)
            return; // Verifica se o sensor não é nulo

        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Lampada")
            {
                // Calcula a luminosidade natural com base na hora do dia
                bool estaClaro = sensor->getCalibraSensor(1);

                if (!estaClaro)
                {
                    if (atuador->getConfigAtuador() < 100)
                    {
                        atualizarLampada(1);
                        atuador->setConfigAtuador(atuador->getConfigAtuador() + 1);
                    }
                }
                else
                {
                    // Ambiente mais claro que o desejado, diminui o brilho
                    if (atuador->getConfigAtuador() > 0)
                    {
                        atualizarLampada(1);
                        atuador->setConfigAtuador(atuador->getConfigAtuador() - 1);
                    }
                    else
                    {
                        atualizarLampada(0);
                    }
                }
            }
        }
    }

    // Função para ajustar os atuadores de umidade com base no sensor
    void ajustarAtuadoresUmidade(Sensor *sensor)
    {
        int diferencaUmidade = umidadeDesejada - sensor->getCalibraSensor(1);

        if (sensor->getValor() < umidadeDesejada)
        {
            // Liga o aquecedor e desliga ventilador e ar-condicionado
            atualizarUmidificador(true, 1);
            atualizarDesumidificador(false, 0);
        }
        else if (diferencaUmidade >= 8) // Diferença maior ou igual a 8%
        {
            // Resfriamento rápido: liga ventilador e ar-condicionado
            atualizarUmidificador(false, 2);
            atualizarDesumidificador(false, 0);
        }
        else if (sensor->getValor() > umidadeDesejada)
        {
            // Ajusta ventilador ou ar-condicionado com base na temperatura atual
            if (diferencaUmidade <= -8)
            {
                atualizarUmidificador(false, 0);
                atualizarDesumidificador(true, 2);
            }
            else
            {
                atualizarUmidificador(false, 0);
                atualizarDesumidificador(true, 1);
            }
        }
        else
        {
            atualizarUmidificador(false, 0);
            atualizarDesumidificador(false, 0);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////

    // Ajusta a temperatura com base nos atuadores e variação ambiental
    void ajustarTemperaturaAmbiente(Sensor *sensor)
    {
        if (sensor == nullptr)
            return; // Verifica se o sensor não é nulo

        // Variação ambiental entre -2 e +2
        int variacaoAmbiente = std::rand() % 5 - 2;

        // Ajusta a temperatura com base no status dos atuadores
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Aquecedor" && atuador->getValor() == 1)
            {
                sensor->setSensor(sensor->getValor() + 1); // Aumenta a temperatura
            }
            if (atuador->getNome() == "Ventilador" && atuador->getValor() == 1)
            {
                sensor->setSensor(sensor->getValor() - 1); // Diminui a temperatura
            }
            if (atuador->getNome() == "ArCondicionado" && atuador->getValor() == 1)
            {
                sensor->setSensor(sensor->getValor() - 2); // Diminui a temperatura mais rapidamente
            }
        }

        // Aplica a variação ambiental
        sensor->setSensor(sensor->getValor() + variacaoAmbiente);
    }

    // Ajusta a luminosidade com base na hora do dia simulada
    void ajustarLuminosidadeAmbiente(Sensor *sensor, int minutos)
    {
        if (sensor == nullptr)
            return; // Verifica se o sensor não é nulo

        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Lampada")
            {
                // Calcula a luminosidade natural com base na hora do dia
                int luxNatural = calcularLuxNatural(minutos);
                int brilhoAtual = atuador->getConfigAtuador(); // Brilho atual da lâmpada

                // Atualiza valor sensor
                sensor->setSensor(luxNatural + brilhoAtual * 10);
            }
        }
    }

    // Ajusta a umidade com base na hora do dia simulada
    void ajustarUmidadeAmbiente(Sensor *sensor)
    {
        if (sensor == nullptr)
            return; // Verifica se o sensor não é nulo

        // Variação ambiental entre -2 e +2
        int variacaoAmbiente = std::rand() % 5 - 2;

        for (auto atuador : atuadores)
        {
            float valorAtuador = atuador->getConfigAtuador();
            if (atuador->getNome() == "Umidificador" && atuador->getValor() == 1)
            {
                if (valorAtuador == 1)
                {
                    sensor->setSensor(sensor->getValor() + 1);
                }
                else if (valorAtuador == 2)
                {
                    sensor->setSensor(sensor->getValor() + 2);
                }
            }
            if (atuador->getNome() == "Desumidificador" && atuador->getValor() == 1)
            {
                if (valorAtuador == 1)
                {
                    sensor->setSensor(sensor->getValor() - 1);
                }
                else if (valorAtuador == 2)
                {
                    sensor->setSensor(sensor->getValor() - 2);
                }
            }
        }

        // Aplica a variação ambiental
        sensor->setSensor(sensor->getValor() + variacaoAmbiente);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    //                                  DADOS AMBIENTE
    /////////////////////////////////////////////////////////////////////////////////////

    // Calcula a luminosidade natural com base na hora do dia
    int calcularLuxNatural(int minutos)
    {
        // Minutos correspondentes ao início e fim do período de luz natural
        int inicioLuz = 360; // 6h em minutos
        int picoLuz = 720;   // 12h em minutos
        int fimLuz = 1080;   // 18h em minutos
        int picoLux = 600;   // Pico máximo de luz natural ao meio-dia

        if (minutos < inicioLuz || minutos > fimLuz)
        {
            return 0; // Sem luz natural fora do período de 6h a 18h
        }
        else if (minutos <= picoLuz)
        {
            // Aumenta a luz de forma linear até o pico ao meio-dia
            return (picoLux * (minutos - inicioLuz)) / (picoLuz - inicioLuz);
        }
        else
        {
            // Diminui a luz de forma linear após o meio-dia
            return picoLux - ((picoLux * (minutos - picoLuz)) / (fimLuz - picoLuz));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    //                                ATUALIZAR ATUADORES
    /////////////////////////////////////////////////////////////////////////////////////

    // Funções auxiliares para controlar os atuadores de temperatura
    void atualizarAquecedor(bool status, int i)
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Aquecedor")
            {
                atuador->setValor(status ? 1 : 0); // Liga ou desliga aquecedor
                atuador->setConfigAtuador(i);
            }
        }
    }

    void atualizarVentilador(bool status, int i)
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Ventilador")
            {
                atuador->setValor(status ? 1 : 0); // Liga ou desliga ventilador
                atuador->setConfigAtuador(i);
            }
        }
    }

    void atualizarArCondicionado(bool status, int i)
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "ArCondicionado")
            {
                atuador->setValor(status ? 1 : 0); // Liga ou desliga ar-condicionado
                atuador->setConfigAtuador(i);
            }
        }
    }

    void atualizarLampada(bool status)
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Lampada")
            {
                atuador->setValor(status ? 1 : 0); // Liga ou desliga ar-condicionado
            }
        }
    }

    void atualizarUmidificador(bool status, int i)
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Umidificador")
            {
                atuador->setValor(status ? 1 : 0); // Liga ou desliga ar-condicionado
                atuador->setConfigAtuador(i);
            }
        }
    }

    void atualizarDesumidificador(bool status, int i)
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Desumidificador")
            {
                atuador->setValor(status ? 1 : 0); // Liga ou desliga ar-condicionado
                atuador->setConfigAtuador(i);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    //                                PEGA DADOS SENSORES
    /////////////////////////////////////////////////////////////////////////////////////
    float getTemperaturaAtual(int i)
    {
        for (auto sensor : sensores)
        {
            if (sensor != nullptr && sensor->getNome() == "Temperatura")
            {
                return sensor->getCalibraSensor(i);
            }
        }
        return 0.0f; // Retorno padrão caso o sensor não seja encontrado
    }

    float getLuxAtual()
    {
        for (auto sensor : sensores)
        {
            if (sensor != nullptr && sensor->getNome() == "Luminosidade")
            {
                return sensor->getValor();
            }
        }
        return 0.0f; // Retorno padrão caso o sensor não seja encontrado
    }

    float getUmidade()
    {
        for (auto sensor : sensores)
        {
            if (sensor != nullptr && sensor->getNome() == "Umidade")
            {
                return sensor->getValor();
            }
        }
        return 0.0f; // Retorno padrão caso o sensor não seja encontrado
    }

    /////////////////////////////////////////////////////////////////////////////////////
    //                                PEGA STATUS ATUADORES
    /////////////////////////////////////////////////////////////////////////////////////

    int getStatusAquecedor()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Aquecedor")
                return atuador->getValor();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    int getStatusVentilador()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Ventilador")
                return atuador->getValor();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    int getStatusArCondicionado()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "ArCondicionado")
                return atuador->getValor();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    int getStatusLampada()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Lampada")
                return atuador->getValor();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    int getStatusUmidificador()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Umidificador")
                return atuador->getValor();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    int getStatusDesumidificador()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Desumidificador")
                return atuador->getValor();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    /////////////////////////////////////////////////////////////////////////////////////
    //                                PEGA CONFIGURAÇÃO ATUADORES
    /////////////////////////////////////////////////////////////////////////////////////

    int getConfigAquecedor()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Aquecedor")
                return atuador->getConfigAtuador();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    int getConfigVentilador()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Ventilador")
                return atuador->getConfigAtuador();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    int getConfigArCondicionado()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "ArCondicionado")
                return atuador->getConfigAtuador();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    int getConfigLampada()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Lampada")
                return atuador->getConfigAtuador();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    int getConfigUmidificador()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Umidificador")
                return atuador->getConfigAtuador();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }

    int getConfigDesumidificador()
    {
        for (auto atuador : atuadores)
        {
            if (atuador->getNome() == "Desumidificador")
                return atuador->getConfigAtuador();
        }
        return 404; // Retorno padrão se o atuador não for encontrado
    }
};
