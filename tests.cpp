#include <iostream>
#include "Cardio.h"
#include "Forca.h"
#include "Ficha.h"
#include "Historico.h"
#include "Utils.h"

void testeCardio() {
    std::cout << "\n=== TESTE CARDIO ===\n";

    Cardio c("Corrida", 30, 10.5);

    c.exibirDetalhes();

    std::cout << "Tempo estimado: " << c.calcularTempoEstimado() << " minutos\n";
    std::cout << "Calorias gastas: " << c.calcularCaloriasGastas() << "\n";
    std::cout << "Tipo: " << c.getTipo() << "\n";
}

void testeForca() {
    std::cout << "\n=== TESTE FORCA ===\n";

    Forca f("Supino", 40.0, 4, 12, 90);

    f.exibirDetalhes();

    std::cout << "Tempo estimado: " << f.calcularTempoEstimado() << " minutos\n";
    std::cout << "Calorias gastas: " << f.calcularCaloriasGastas() << "\n";
    std::cout << "Tipo: " << f.getTipo() << "\n";
}

void testeFicha() {
    std::cout << "\n=== TESTE FICHA ===\n";

    Ficha ficha("Treino A");

    ficha.adicionarExercicio(new Cardio("Corda", 20, 8.0));
    ficha.adicionarExercicio(new Forca("Agachamento", 30.0, 3, 15, 60));

    ficha.exibirFicha();

    std::cout << "Tempo total: " << ficha.calcularTempoTotal() << " minutos\n";
    std::cout << "Calorias totais: " << ficha.calcularCaloriasTotais() << "\n";
}

void testeHistorico() {
    std::cout << "\n=== TESTE HISTORICO ===\n";

    Historico hist;

    RegistroTreino r;
    r.dataHora = getDataHoraAtual();
    r.idFicha = 1;
    r.nomeFicha = "Treino A";
    r.tempoTotal = 42.5;
    r.caloriasTotal = 320;

    hist.adicionarRegistro(r);

    hist.exibirHistorico();
}

int main() {
    std::cout << "=== INICIANDO TESTES ===\n";

    testeCardio();
    testeForca();
    testeFicha();
    testeHistorico();

    std::cout << "\n=== FIM DOS TESTES ===\n";
    return 0;
}
