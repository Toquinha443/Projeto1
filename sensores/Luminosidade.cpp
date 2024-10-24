#include "Sensor.cpp"

class Luminosidade : public Sensor
{
private:
    int limiarClaridade;

public:
    Luminosidade(std::string nome) : Sensor(nome), limiarClaridade(0) {}

    // Define claridade do ambiente
    void setLimiarClaridade(int claridade) { this->limiarClaridade = claridade; }

    // Valida claridade do ambiente com margem
    bool estaClaro() const { return getValor() >= limiarClaridade; }

    // Calibra o sensor para luminosidade escolhida
    virtual bool setCalibraSensor(int i)
    {
        if (i > 0)
        {
            setLimiarClaridade(i);
            return true;
        }
        return false;
    }

    // Consulta calibragem do sensor
    virtual float getCalibraSensor(int i) const
    {
        if (i == 1)
        {
            return static_cast<float>(estaClaro() ? 1 : 0);
        }

        return 0.0f; // Valor default caso o índice não seja 1
    }
};
