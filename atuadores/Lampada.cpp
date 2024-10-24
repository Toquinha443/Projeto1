#include "Atuador.cpp"

class Lampada : public Atuador
{
private:
    int brilho;

public:
    Lampada(std::string nome) : Atuador(nome), brilho(0) {}

    // Ajusta o brilho da lâmpada
    bool setBrilho(int brilho)
    {
        this->brilho = brilho;
        return true;
    }

    // Retorna o valor do brilho
    int getBrilho() const { return brilho; }

    // Define a configuração do atuador
    virtual bool setConfigAtuador(int i)
    {
        if (i > 0)
        {
            setBrilho(i);
            return true;
        }
        return false;
    }

    // Consulta a configuração do atuador
    virtual float getConfigAtuador() const
    {
        return static_cast<float>(getBrilho());
    }
};
