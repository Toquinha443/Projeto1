#include "Sensor.cpp"

class Presenca : public Sensor {  // Aqui mudamos o nome para "Presenca"
public:
    Presenca(std::string nome) : Sensor(nome) {}

    void atualizar() override {
        bool novaPresenca = rand() % 2; // Gera 0 ou 1, que representa "false" ou "true"
        setValor(novaPresenca); // Atualiza o valor na classe base (0 para false, 1 para true)
    }
};
