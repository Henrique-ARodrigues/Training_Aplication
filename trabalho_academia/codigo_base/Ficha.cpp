#include "Ficha.h"
#include <iostream>
#include <iomanip>

int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(std::string nome)
    : id(proximoId++), nome(nome) {}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, std::string nome)
   : id(id), nome(nome) {}


// Destrutor (não deletar exercícios, apenas limpar vector)
Ficha::~Ficha() {
    exercicios.clear();
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* exercicio) {
    exercicios.push_back(exercicio);
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const {
    std::cout << "\n ======== Ficha #" << id << " ========\n";
    std::cout << "\n Nome: " << nome << std::endl;

    if(exercicios.empty()) {
        std::cout << "Nenhum exercício cadastrado. \n";
        return;

    }

    std::cout << "\n=== Exercícios ===\n";

    for(const auto& e : exercicios ) {
        e -> exibirDetalhes();
    }
}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const {
    double total = 0.0;

    for(const auto& e : exercicios) {
        e -> calcularTempoEstimado();

    }

    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;
    
    for(const auto& e : exercicios) {
        e -> calcularCaloriasGastas();

    }

    return total;
}

// Getters
int Ficha::getId() const { 
    return id;
}

std::string Ficha::getNome() const { 
    return nome;
}

const std::vector<Exercicio*>& Ficha::getExercicios() const {
    static std::vector<Exercicio*> vazio; // Placeholder para compilar
    return exercicios;
}

// Atualizar próximo ID
void Ficha::atualizarProximoId(int maiorId) {
    proximoId = maiorId + 1;
}
