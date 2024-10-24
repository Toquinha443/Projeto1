#include "Sensor.cpp"

class Umidade : public Sensor
{
public:
    Umidade(std::string nome) : Sensor(nome) {}
    
    float getUmidadeRelativa() const { return getValor(); }

    // Calibra o sensor para luminosidade escolhida
    virtual bool setCalibraSensor(int i)
    {
        if (i > 0)
        {
            return true;
        }
        return false;
    }

    // Consulta calibragem do sensor
    virtual float getCalibraSensor(int i) const
    {
        if (i == 1)
        {
            return static_cast<float>(getUmidadeRelativa());
        }

        return 0.0f;
    }
};