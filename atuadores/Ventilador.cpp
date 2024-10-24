#include "Atuador.cpp"
#include <iostream>

class Ventilador : public Atuador
{
private:
    int velocidade;

public:
    Ventilador(std::string nome) : Atuador(nome), velocidade(0) {}

    // Ajusta o velocidade da lâmpada
    bool setVelocidade(int velocidade)
    {
        this->velocidade = velocidade;
        return true;
    }

    // Retorna o valor do velocidade
    int getVelocidade() const { return velocidade; }

    // Define a configuração do atuador
    virtual bool setConfigAtuador(int i)
    {
        if (i >= 0)
        {
            setVelocidade(i);
            return true;
        }
        return false;
    }

    // Consulta a configuração do atuador
    virtual float getConfigAtuador() const
    {
        return static_cast<float>(getVelocidade());
    }
};