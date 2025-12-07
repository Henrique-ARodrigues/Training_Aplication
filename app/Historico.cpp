#include "Historico.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>

// Adicionar registro ao histórico
void Historico::adicionarRegistro(const RegistroTreino& registro) {
    registros.push_back(registro);
}

// Exibir histórico completo
void Historico::exibirHistorico() const {
    if (registros.empty()){
        std::cout << "Hitórico vazio." << std::endl;
        return;
    }

    std::cout << "=== HISTORICO DE TREINOS ===" << std::endl;
        for (const auto& r : registros) {
            std::cout << r.dataHora
                << " | Ficha ID: " << r.idFicha
                << " | Nome: " << r.nomeFicha
                << " | Tempo: " << r.tempoTotal << " min"
                << " | Calorias: " <<r.caloriasTotal << " kcal"
                << std::endl;
        }
    
}

// Getter de registros
const std::vector<RegistroTreino>& Historico::getRegistros() const {
    return registros;
}

// Carregar histórico do arquivo
void Historico::carregarDeArquivo() {
    registros.clear();
    std::ifstream in("historico.txt");
    if(!in.is_open()) return;

    std::string linha;
    while (std::getline(in,linha)){
        if (linha.empty()) continue;
        std::istringstream ss(linha);
        std::string campo;

        RegistroTreino r;
        // data
        if(!std::getline(ss, campo, ';')) continue;
        r.dataHora = campo;

        //id da ficha
        if (!std::getline(ss, campo, ';')) continue;
        r.idFicha = std::stoi(campo);

        //nome da ficha
        if (!std::getline(ss, campo, ';'))continue;
        r.nomeFicha = campo;

        if(!std::getline(ss, campo, ';'))continue;
        try {
            r.tempoTotal = std::stod(campo);
        }catch(...){
            r.tempoTotal = 0.0;
        }

        registros.push_back(r);
    }

    in.close();
}

// Salvar histórico no arquivo
void Historico::salvarEmArquivo() const {
    std::ofstream out("historico.txt", std::ios::trunc);
    if (!out.is_open()) return;

    for (const auto& r : registros){
        out << r.dataHora << ';'
            << r.idFicha << ';'
            << r.nomeFicha << ';'
            << r.tempoTotal << ';'
            << r.caloriasTotal << '\n';
    }
    out.close();
}
