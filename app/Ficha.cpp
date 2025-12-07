#include "Ficha.h"
#include <iostream>
#include <iomanip>

int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(std::string nome)
    : id(proximoId++), nome(nome) {}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, std::string nome)
    : id(id), nome(nome)
{
    // Correção de IDs 
    if (id >= proximoId) {
        proximoId = id + 1;
    }
}

// Destrutor (não deletar exercícios)
Ficha::~Ficha() {
    exercicios.clear();
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* exercicio) {
    exercicios.push_back(exercicio);
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const {

    std::cout << "\n======== Ficha #" << id << " ========\n";
    std::cout << "Nome: " << nome << "\n";

    if (exercicios.empty()) {
        std::cout << "Nenhum exercício cadastrado.\n";
        return;
    }

    std::cout << "\n=== Exercícios ===\n";

    for (const auto& e : exercicios) {
        e->exibirDetalhes();
    }

    std::cout << "\nTempo total: " << calcularTempoTotal() << " min\n";
    std::cout << "Calorias totais: " << calcularCaloriasTotais() << " kcal\n";
}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const {
    double total = 0.0;

    for (const auto& e : exercicios) {
        total += e->calcularTempoEstimado();
    }

    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;

    for (const auto& e : exercicios) {
        total += e->calcularCaloriasGastas();
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
    return exercicios;
}

// Atualizar próximo ID
void Ficha::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
        proximoId = maiorId + 1;
    }
}
