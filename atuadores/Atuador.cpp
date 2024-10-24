#include "../componentes/Componente.cpp"
#include <iostream>
#pragma once

class Atuador : public Componente
{
public:
    Atuador(std::string nome) : Componente(nome) {}

    // Método para definir o estado do atuador (ligado ou desligado)
    bool setValor(int novoValor)
    {
        passavalor(novoValor);
        return true;
    }

    // Método virtual para configurar o atuador (velocidade, potencia)
    virtual bool setConfigAtuador(int novoValor) { return false; }

    // Método virtual para obter as configurações do atuador
    virtual float getConfigAtuador() const { return 0.0f; }
};
