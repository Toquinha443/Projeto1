#include "Atuador.cpp"
#include <iostream>

class Aquecedor : public Atuador
{
private:
    int potencia;

public:
    Aquecedor(std::string nome) : Atuador(nome), potencia(0) {}

    // Ajusta o potencia da lâmpada
    bool setPotencia(int potencia)
    {
        this->potencia = potencia;
        return true;
    }

    // Retorna o valor do potencia
    int getPotencia() const { return potencia; }

    // Define a configuração do atuador
    virtual bool setConfigAtuador(int i)
    {
        if (i >= 0)
        {
            setPotencia(i);
            return true;
        }
        return false;
    }

    // Consulta a configuração do atuador
    virtual float getConfigAtuador() const
    {
        return static_cast<float>(getPotencia());
    }
};
