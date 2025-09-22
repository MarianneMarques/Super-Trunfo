#include <stdio.h>
#include <string.h>

typedef struct {
    char codigo[8];          // ex: "A01"
    char nome[64];           // ex: "Cidade X"
    unsigned long long populacao; // agora unsigned long long
    double area;             // km²
    double pib;              // mesma unidade para as duas cartas (ex.: bilhões)
    int pontos_turisticos;   // inteiro
    // calculados:
    double densidade;        // pop / area
    double pib_per_capita;   // pib / pop
    double super_poder;      // soma dos numéricos + inverso da densidade
} Carta;

void ler_carta(Carta *c, int idx) {
    printf("=== Carta %d ===\n", idx);

    printf("Codigo: ");
    scanf("%7s", c->codigo);

    printf("Nome: ");
    scanf(" %[^\n]", c->nome); // lê o nome completo com espaços

    printf("Populacao (inteiro nao-negativo): ");
    scanf("%llu", &c->populacao);

    printf("Area (km2): ");
    scanf("%lf", &c->area);

    printf("PIB (mesma unidade para ambas as cartas): ");
    scanf("%lf", &c->pib);

    printf("Numero de pontos turisticos (inteiro): ");
    scanf("%d", &c->pontos_turisticos);
}

void calcular_derivados(Carta *c) {
    c->densidade = (c->area > 0.0) ? ((double)c->populacao / c->area) : 0.0;
    c->pib_per_capita = (c->populacao > 0ULL) ? (c->pib / (double)c->populacao) : 0.0;
    double inv_densidade = (c->densidade > 0.0) ? (1.0 / c->densidade) : 0.0;

    c->super_poder = (double)c->populacao
                   + c->area
                   + c->pib
                   + (double)c->pontos_turisticos
                   + c->pib_per_capita
                   + inv_densidade;
}

int venceu_maior(double a, double b) { return (a > b) ? 1 : 0; }
int venceu_menor(double a, double b) { return (a < b) ? 1 : 0; }

int main(void) {
    Carta c1, c2;

    ler_carta(&c1, 1);
    ler_carta(&c2, 2);

    calcular_derivados(&c1);
    calcular_derivados(&c2);

    printf("\n=== Comparacao de Cartas (%s vs %s) ===\n", c1.nome, c2.nome);

    printf("Populacao: Carta %d venceu (%d)\n",
           venceu_maior((double)c1.populacao, (double)c2.populacao) ? 1 : 2,
           venceu_maior((double)c1.populacao, (double)c2.populacao));

    printf("Area: Carta %d venceu (%d)\n",
           venceu_maior(c1.area, c2.area) ? 1 : 2,
           venceu_maior(c1.area, c2.area));

    printf("PIB: Carta %d venceu (%d)\n",
           venceu_maior(c1.pib, c2.pib) ? 1 : 2,
           venceu_maior(c1.pib, c2.pib));

    printf("Pontos Turisticos: Carta %d venceu (%d)\n",
           venceu_maior((double)c1.pontos_turisticos, (double)c2.pontos_turisticos) ? 1 : 2,
           venceu_maior((double)c1.pontos_turisticos, (double)c2.pontos_turisticos));

    printf("Densidade Populacional: Carta %d venceu (%d)\n",
           venceu_menor(c1.densidade, c2.densidade) ? 1 : 2,
           venceu_menor(c1.densidade, c2.densidade));

    printf("PIB per Capita: Carta %d venceu (%d)\n",
           venceu_maior(c1.pib_per_capita, c2.pib_per_capita) ? 1 : 2,
           venceu_maior(c1.pib_per_capita, c2.pib_per_capita));

    printf("Super Poder: Carta %d venceu (%d)\n",
           venceu_maior(c1.super_poder, c2.super_poder) ? 1 : 2,
           venceu_maior(c1.super_poder, c2.super_poder));

    return 0;
}