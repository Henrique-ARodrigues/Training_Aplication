#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <filesystem>

Sistema::Sistema() {
    carregarDados();
}

Sistema::~Sistema() {
    salvarDados();
    // Deletar ponteiros de exercicios e fichas (sistema é dono)
    for (auto* ex : exercicios) delete ex;
    for (auto* f : fichas) delete f;
    exercicios.clear();
    fichas.clear();
}

static std::vector<std::string> split(const std::string& s, char sep) {
    std::vector<std::string> out;
    std::string cur;
    std::istringstream ss(s);
    while (std::getline(ss, cur, sep)) out.push_back(cur);
    return out;
}

// Carregar dados dos arquivos
void Sistema::carregarDados() {
    //Carregar exercicios.txt
    exercicios.clear();
    std::ifstream inEx("exercicios.txt");
    if (inEx.is_open()){
        std::string linha;
        while (std::getline(inEx, linha)){
            if(linha.empty()) continue;
            auto campos = split(linha, ';');
            if(campos.size() < 1) continue;
            int tipo = std::stoi(campos[0]);

            if (tipo == 1) {
                //cardio : 1; ID;NOME;DURACAO;CALORIA_POR_MIN;STATUS
                if (campos.size() < 6) continue;
                int id = std::stoi(campos[1]);
                std::string nome = campos[2];
                int duracao = std::stoi(campos[3]);
                double calMin = std::stod(campos[4]);
                bool status = (std::stoi(campos[5]) == 1);
                Cardio* c = new Cardio(id, nome, status, duracao, calMin);
                exercicios.push_back(c);
            } else if (tipo == 2) {
                //forca: 2;ID;NOME;CARGA;SERIES;REPETICOES;DESCANSO;STATUS
                if (campos.size() < 8) continue;
                int id = std::stoi(campos[1]);
                std::string nome = campos[2];
                double carga = std::stod(campos[3]);
                int series = std::stoi(campos[4]);
                int reps = std::stoi(campos[5]);
                int descanso = std::stoi(campos[6]);
                bool status = (std::stoi(campos[7]) == 1);
                Forca* f = new Forca(id, nome, status, carga, series, reps, descanso);
                exercicios.push_back(f);
            }
        }
        inEx.close();
    }

    // carregar ficxas.txt
    fichas.clear();
    std::ifstream inF("fichas.txt");
    if (inF.is_open()) {
        std::string linha;
        while (std::getline(inF, linha)) {
            if (linha.empty()) continue;
            auto campos = split(linha, ';');
            if (campos.size() < 3) continue;
            int idFicha = std::stoi(campos[0]);
            std::string nomeFicha = campos[1];
            int totalEx = std::stoi(campos[2]);

            Ficha* ficha = new Ficha(idFicha, nomeFicha);
            for (int i = 0; i < totalEx; ++i) {
                int idx = 3 + i;
                if (idx >= (int)campos.size()) break;
                int idEx = std::stoi(campos[idx]);
                Exercicio* ex = buscarExercicioPorId(idEx);
                if (ex != nullptr) ficha->adicionarExercicio(ex);
            }
            fichas.push_back(ficha);
        }
        inF.close();
    }

    historico.carregarDeArquivo();
}

// Salvar dados nos arquivos
void Sistema::salvarDados() {
    // Salvar exercicios.txt
    std::ofstream outEx("exercicios.txt", std::ios::trunc);
    if (outEx.is_open()) {
        for (auto* ex : exercicios) {
            int tipo = ex->getTipo();
            if (tipo == 1) {
                Cardio* c = dynamic_cast<Cardio*>(ex);
                if (!c) continue;
                outEx << "1;" << c->getId() << ";" << c->getNome() << ";" << c->getDuracao()
                      << ";" << c->getCaloriasPorMinuto() << ";" << (c->isAtivo() ? 1 : 0) << "\n";
            } else if (tipo == 2) {
                Forca* f = dynamic_cast<Forca*>(ex);
                if (!f) continue;
                outEx << "2;" << f->getId() << ";" << f->getNome() << ";" << f->getCarga()
                      << ";" << f->getSeries() << ";" << f->getRepeticoes() << ";" << f->getTempoDescanso()
                      << ";" << (f->isAtivo() ? 1 : 0) << "\n";
            }
        }
        outEx.close();
    }

    // Salvar fichas.txt
    std::ofstream outF("fichas.txt", std::ios::trunc);
    if (outF.is_open()) {
        for (auto* f : fichas) {
            outF << f->getId() << ";" << f->getNome() << ";" << (int)f->getExercicios().size();
            for (auto* ex : f->getExercicios()) {
                outF << ";" << ex->getId();
            }
            outF << "\n";
        }
        outF.close();
    }

    // Salvar histórico
    historico.salvarEmArquivo();
}


// Buscar exercício por ID
Exercicio* Sistema::buscarExercicioPorId(int id) {
    for (auto* ex : exercicios) {
        if (ex->getId() == id) return ex;
    }
    return nullptr;
}

// Buscar ficha por ID
Ficha* Sistema::buscarFichaPorId(int id) {
    for (auto* f : fichas) {
        if (f->getId() == id) return f;
    }
    return nullptr;
}

// Cadastrar novo exercício
void Sistema::cadastrarExercicio() {
    limparTela();
    std::cout << "=== CADASTRAR EXERCICIO ===\n";
    std::cout << "1. Cardio\n2. Forca\nOpcao: ";
    int opc;
    std::cin >> opc;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (opc == 1) {
        std::string nome;
        int duracao;
        double calMin;
        std::cout << "Nome: ";
        std::getline(std::cin, nome);
        std::cout << "Duracao (min): ";
        std::cin >> duracao;
        std::cout << "Calorias por minuto: ";
        std::cin >> calMin;
        Cardio* c = new Cardio(nome, duracao, calMin);
        exercicios.push_back(c);
        std::cout << "Cardio cadastrado com ID " << c->getId() << "!\n";
    } else if (opc == 2) {
        std::string nome;
        double carga;
        int series, reps, descanso;
        std::cout << "Nome: ";
        std::getline(std::cin, nome);
        if (nome.empty()) std::getline(std::cin, nome);
        std::cout << "Carga (kg): ";
        std::cin >> carga;
        std::cout << "Series: ";
        std::cin >> series;
        std::cout << "Repeticoes: ";
        std::cin >> reps;
        std::cout << "Tempo de descanso (s): ";
        std::cin >> descanso;
        Forca* f = new Forca(nome, carga, series, reps, descanso);
        exercicios.push_back(f);
        std::cout << "Forca cadastrada com ID " << f->getId() << "!\n";
    } else {
        std::cout << "Opcao invalida.\n";
    }

    pausar();
}

// Listar exercícios ativos
void Sistema::listarExercicios() {
    limparTela();
    std::cout << "=== EXERCICIOS ATIVOS ===\n";
    bool any = false;
    for (auto* ex : exercicios) {
        if (!ex->isAtivo()) continue;
        ex->exibirDetalhes();
        any = true;
    }
    if (!any) std::cout << "Nenhum exercicio ativo encontrado.\n";
    pausar();
}

// Desativar exercício
void Sistema::excluirExercicio() {
    limparTela();
    std::cout << "=== DESATIVAR EXERCICIO ===\n";
    listarExercicios();
    std::cout << "Digite o ID do exercicio a desativar: ";
    int id;
    std::cin >> id;
    Exercicio* ex = buscarExercicioPorId(id);
    if (ex == nullptr) {
        std::cout << "Exercicio nao encontrado.\n";
    } else {
        ex->desativar();
        std::cout << "Exercicio desativado.\n";
    }
    pausar();
}

// Criar nova ficha
void Sistema::criarFicha() {
    limparTela();
    std::cout << "=== CRIAR FICHA ===\n";
    std::cout << "Nome da ficha: ";
    std::string nome;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nome);
    Ficha* f = new Ficha(nome);
    fichas.push_back(f);
    std::cout << "Ficha criada com ID " << f->getId() << "!\n";
    pausar();
}

// Adicionar exercício à ficha
void Sistema::adicionarExercicioFicha() {
    limparTela();
    std::cout << "=== ADICIONAR EXERCICIO A FICHA ===\n";
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada.\n";
        pausar();
        return;
    }
    std::cout << "Fichas disponiveis:\n";
    for (auto* f : fichas) {
        std::cout << f->getId() << " - " << f->getNome() << "\n";
    }
    std::cout << "Digite o ID da ficha: ";
    int idFicha;
    std::cin >> idFicha;
    Ficha* ficha = buscarFichaPorId(idFicha);
    if (!ficha) {
        std::cout << "Ficha nao encontrada.\n";
        pausar();
        return;
    }

    // exibir exercicios ativos
    std::cout << "Exercicios ativos:\n";
    for (auto* ex : exercicios) {
        if (ex->isAtivo()) ex->exibirDetalhes();
    }
    std::cout << "Digite o ID do exercicio a adicionar: ";
    int idEx;
    std::cin >> idEx;
    Exercicio* ex = buscarExercicioPorId(idEx);
    if (!ex) {
        std::cout << "Exercicio nao encontrado.\n";
    } else {
        ficha->adicionarExercicio(ex);
        std::cout << "Exercicio adicionado na ficha.\n";
    }
    pausar();
}

// Listar todas as fichas
void Sistema::listarFichas() {
        limparTela();
    std::cout << "=== FICHAS ===\n";
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada.\n";
    } else {
        for (auto* f : fichas) {
            f->exibirFicha();
        }
    }
    pausar();
}

// Registrar treino realizado
void Sistema::registrarTreino() {
    limparTela();
    std::cout << "=== REGISTRAR TREINO ===\n";
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada.\n";
        pausar();
        return;
    }
    std::cout << "Fichas disponiveis:\n";
    for (auto* f : fichas) {
        std::cout << f->getId() << " - " << f->getNome() << "\n";
    }
    std::cout << "Digite o ID da ficha realizada: ";
    int idFicha;
    std::cin >> idFicha;
    Ficha* ficha = buscarFichaPorId(idFicha);
    if (!ficha) {
        std::cout << "Ficha nao encontrada.\n";
        pausar();
        return;
    }

    RegistroTreino r;
    r.dataHora = getDataHoraAtual();
    r.idFicha = ficha->getId();
    r.nomeFicha = ficha->getNome();
    r.tempoTotal = ficha->calcularTempoTotal();
    r.caloriasTotal = ficha->calcularCaloriasTotais();

    historico.adicionarRegistro(r);
    historico.salvarEmArquivo(); // salva imediatamente
    std::cout << "Treino registrado: " << r.dataHora << " | Tempo: " << r.tempoTotal << " min | Cal: " << r.caloriasTotal << "\n";
    pausar();
}

// Exibir histórico de treinos
void Sistema::exibirHistorico() {
    limparTela();
    historico.exibirHistorico();
    pausar();
}
