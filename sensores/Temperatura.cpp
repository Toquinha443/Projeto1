#include "Sensor.cpp"
#include <vector>
#include <iostream>

class Temperatura : public Sensor
{
public:
    Temperatura(std::string nome) : Sensor(nome) {}

    float getTemperaturaEmC() const { return getValor(); }
    float getTemperaturaEmF() const { return (getValor() * 9 / 5) + 32; }
    float getTemperaturaEmK() const { return getValor() + 273.15; }

    // Consulta calibragem do sensor
    virtual float getCalibraSensor(int i) const
    {
        if (i == 1)
        {
            return getTemperaturaEmC();
        }
        else if (i == 2)
        {
            return getTemperaturaEmF();
        }
        else if (i == 3)
        {
            return getTemperaturaEmK();
        }

        return 0.0f;
    }
};
