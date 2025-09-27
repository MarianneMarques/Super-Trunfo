#include <stdio.h>
#include <string.h>

typedef struct {
    char codigo[8];
    char pais[64];
    unsigned long long populacao;
    double area;
    double pib;
    int pontos_turisticos;
    double densidade;
} Carta;

typedef enum {
    ATR_POP = 1,
    ATR_AREA,
    ATR_PIB,
    ATR_PTUR,
    ATR_DENS
} Atributo;

double valor_atributo(Carta c, Atributo a) {
    switch (a) {
        case ATR_POP: return (double)c.populacao;
        case ATR_AREA: return c.area;
        case ATR_PIB: return c.pib;
        case ATR_PTUR: return (double)c.pontos_turisticos;
        case ATR_DENS: return c.densidade;
        default: return 0;
    }
}

const char* nome_atributo(Atributo a) {
    switch (a) {
        case ATR_POP: return "População";
        case ATR_AREA: return "Área";
        case ATR_PIB: return "PIB";
        case ATR_PTUR: return "Pontos Turísticos";
        case ATR_DENS: return "Densidade (MENOR vence)";
        default: return "Desconhecido";
    }
}

int main() {
    Carta c1 = {"BR", "Brasil", 214000000ULL, 8515767.0, 1920.0, 28, 0};
    c1.densidade = (double)c1.populacao / c1.area;

    Carta c2 = {"US", "Estados Unidos", 336000000ULL, 9833517.0, 26850.0, 35, 0};
    c2.densidade = (double)c2.populacao / c2.area;

    printf("Comparação entre:\n1) %s\n2) %s\n", c1.pais, c2.pais);

    int escolha1, escolha2;
    printf("\nEscolha o primeiro atributo:\n");
    printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade\n");
    scanf("%d", &escolha1);

    do {
        printf("\nEscolha o segundo atributo (diferente do primeiro):\n");
        scanf("%d", &escolha2);
    } while (escolha2 == escolha1);

    double v1c1 = valor_atributo(c1, escolha1);
    double v1c2 = valor_atributo(c2, escolha1);
    double v2c1 = valor_atributo(c1, escolha2);
    double v2c2 = valor_atributo(c2, escolha2);

    printf("\n=== RESULTADO ===\n");
    printf("%s: %.2f vs %.2f\n", nome_atributo(escolha1), v1c1, v1c2);
    printf("%s: %.2f vs %.2f\n", nome_atributo(escolha2), v2c1, v2c2);

    double soma1 = v1c1 + v2c1;
    double soma2 = v1c2 + v2c2;

    printf("\nSoma dos atributos -> %s: %.2f | %s: %.2f\n",
           c1.pais, soma1, c2.pais, soma2);

    if (soma1 > soma2) printf("Vencedor: %s\n", c1.pais);
    else if (soma2 > soma1) printf("Vencedor: %s\n", c2.pais);
    else printf("Empate!\n");

    return 0;
}
