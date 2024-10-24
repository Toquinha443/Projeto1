#include "Atuador.cpp"

class Umidificador : public Atuador
{
private:
    int potencia;

public:
    Umidificador(std::string nome) : Atuador(nome), potencia(0) {}

    // Ajusta o potencia da lâmpada
    bool setConfiguracao(int potencia)
    {
        this->potencia = potencia;
        return true;
    }

    // Retorna o valor do brilho
    int getConfiguracao() const { return potencia; }

    // Define a configuração do atuador
    virtual bool setConfigAtuador(int i)
    {
        if (i >= 0)
        {
            setConfiguracao(i);
            return true;
        }
        return false;
    }

    // Consulta a configuração do atuador
    virtual float getConfigAtuador() const
    {
        return static_cast<float>(getConfiguracao());
    }
};