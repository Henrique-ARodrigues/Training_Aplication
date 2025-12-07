#include "Forca.h"
#include <iostream>
#include <iomanip>

// Construtor para novos cadastros
Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome) {
        this->carga = carga;
        this->series = series;
        this->repeticoes = repeticoes;
        this->tempoDescanso = tempoDescanso;
}

// Construtor para leitura de arquivo
Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo) {
        this->carga = carga;
        this->series = series;
        this->repeticoes = repeticoes;
        this->tempoDescanso = tempoDescanso;
}

// Exibir detalhes do exercício
void Forca::exibirDetalhes() const {
    std::cout << "[FORCA] ID: " << id 
              << " | Nome: " << nome
              << " | Status: " << (ativo ? "Ativo" : "Inativo")
              << " | Carga: " << carga << " kg"
              << " | Séries: " << series
              << " | Reps: " << repeticoes
              << " | Descanso: " << tempoDescanso << "s"
              << std::endl;
}

// Calcular tempo estimado (em minutos)
double Forca::calcularTempoEstimado() const {
    double tempoExecucao = series * repeticoes * 3; // em segundos
    double tempoDescansoTotal = series * tempoDescanso;
    return (tempoExecucao + tempoDescansoTotal) / 60.0;
}

// Calcular calorias gastas
double Forca::calcularCaloriasGastas() const {
    return series * repeticoes * carga * 0.15;
}

// Retornar tipo do exercício (2 = Força)
int Forca::getTipo() const {
    return 2;
}

// Getters
double Forca::getCarga() const { 
    return carga;
}

int Forca::getSeries() const { 
    return series;
}

int Forca::getRepeticoes() const { 
    return repeticoes;
}

int Forca::getTempoDescanso() const { 
    return tempoDescanso;
}
