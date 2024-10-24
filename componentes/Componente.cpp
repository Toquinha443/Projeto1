#include <string>
#include <iostream>
#pragma once

class Componente
{
protected:
    bool ligado;
    bool conectado;
    int valor;
    std::string nome;

public:
    Componente(std::string nome) : nome(nome), ligado(false), conectado(false), valor(304) {}

    void ligar() { ligado = true; }
    void desligar() { ligado = false; }
    bool conectar() {
        conectado = true;
        return conectado;
    }
    void desconectar() { conectado = false; }

    // Método para pegar o valor do componente
    std::string getNome() const { return nome; }
    int getValor() const { return valor; }

    // Método para definir o valor do componente
    void passavalor(int novoValor) { this->valor = novoValor; }
};
