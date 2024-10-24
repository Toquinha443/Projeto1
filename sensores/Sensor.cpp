#include "../componentes/Componente.cpp"
#include <iostream>
#pragma once

class Sensor : public Componente
{
public:
    Sensor(std::string nome) : Componente(nome) {}

    // Método para definir a leitura do sendor
    bool setSensor(int novoValor)
    {
        passavalor(novoValor);
        return true;
    }

    // Método virtual para calibrar o sensor
    virtual bool setCalibraSensor(int novoValor) { return false; }

    // Método virtual para obter as configurações do sensor
    virtual float getCalibraSensor(int i) const { return 0.0f; }
};
