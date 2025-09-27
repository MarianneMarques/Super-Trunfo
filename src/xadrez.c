#include <stdio.h>

/*  =========================
    CONFIGURAÇÃO DO DESAFIO
    =========================
    Defina aqui quantas casas cada peça vai “andar”.
    Não há entrada do usuário; o enunciado permite valores fixos no código.
*/
enum {
    PASSOS_TORRE_CIMA   = 3,
    PASSOS_TORRE_DIREITA= 2,

    PASSOS_BISPO_NE     = 4,  // “nordeste”: cima + direita
    PASSOS_BISPO_SO     = 2,  // “sudoeste”: baixo + esquerda (para mostrar ida/volta)

    PASSOS_RAINHA_CIMA  = 2,  // parte “torre” (reta)
    PASSOS_RAINHA_NO    = 3,  // parte “bispo” (diagonal: cima + esquerda)

    REPETICOES_CAVALO   = 5   // quantas vezes tentaremos “2 para cima e 1 para direita”
};

/* Utilitários obrigatórios da saída */
static void print_cima(void)     { printf("Cima\n"); }
static void print_baixo(void)    { printf("Baixo\n"); }
static void print_esquerda(void) { printf("Esquerda\n"); }
static void print_direita(void)  { printf("Direita\n"); }

/* =========================
   TORRE (recursividade)
   =========================
   Move em linha reta. Teremos duas funções recursivas simples:
   - para cima
   - para direita
*/
static void torre_cima_rec(int n) {
    if (n <= 0) return;      // caso base
    print_cima();
    torre_cima_rec(n - 1);   // passo recursivo
}

static void torre_direita_rec(int n) {
    if (n <= 0) return;
    print_direita();
    torre_direita_rec(n - 1);
}

/* =========================
   BISPO (recursividade)
   =========================
   Diagonal é “um passo vertical + um passo horizontal” por casa.
   Abaixo, duas diagonais:
   - NE: Cima + Direita
   - SO: Baixo + Esquerda
*/
static void bispo_NE_rec(int n) {
    if (n <= 0) return;
    print_cima();
    print_direita();
    bispo_NE_rec(n - 1);
}

static void bispo_SO_rec(int n) {
    if (n <= 0) return;
    print_baixo();
    print_esquerda();
    bispo_SO_rec(n - 1);
}

/* =========================
   BISPO (loops aninhados)
   =========================
   O enunciado pede também uma versão com loops aninhados:
   - loop externo = componente vertical
   - loop interno = componente horizontal
   A cada “casa” na diagonal, imprimimos 1 passo vertical e 1 horizontal.
*/
static void bispo_NE_loops(int casas) {
    for (int v = 0; v < casas; ++v) {       // vertical (externo)
        print_cima();
        for (int h = 0; h < 1; ++h) {       // horizontal (interno)
            print_direita();
        }
    }
}

static void bispo_SO_loops(int casas) {
    for (int v = 0; v < casas; ++v) {
        print_baixo();
        for (int h = 0; h < 1; ++h) {
            print_esquerda();
        }
    }
}

/* =========================
   RAINHA (recursividade)
   =========================
   Combina torre + bispo. Para evidenciar a recursão, dividimos em:
   - parte reta (cima)
   - parte diagonal (NO: cima + esquerda)
*/
static void rainha_parte_reta_cima_rec(int n) {
    if (n <= 0) return;
    print_cima();
    rainha_parte_reta_cima_rec(n - 1);
}

static void rainha_diagonal_NO_rec(int n) {
    if (n <= 0) return;
    print_cima();
    print_esquerda();
    rainha_diagonal_NO_rec(n - 1);
}

/* =========================
   CAVALO (loops aninhados + condições)
   =========================
   Movimento solicitado: “duas casas para cima e uma para a direita”.
   Usamos loops aninhados, com if/continue/break para controlar o fluxo.
   Aqui não há tabuleiro real; apenas simulamos a sequência pedida.
*/
static void cavalo_loops(void) {
    int concluidos = 0;

    for (int tentativa = 0; tentativa < REPETICOES_CAVALO; ++tentativa) {
        // Primeiro, duas para cima
        for (int i = 0; i < 2; ++i) {
            // Se por algum motivo quisermos pular (exemplo de uso de continue)
            if (i < 0) {      // condição impossível, apenas para demonstrar o recurso
                continue;
            }
            print_cima();
        }

        // Depois, avaliamos a “condição” para a casa lateral
        int pode_ir_direita = 1;  // ligue/desligue para testar o fluxo

        if (!pode_ir_direita) {
            // Mostra controle de fluxo: cancela este L e vai para a próxima tentativa
            continue;
        }

        // Uma para a direita
        print_direita();

        ++concluidos;

        // Exemplo de uso de break: se já fizemos 3 L, encerramos antes do limite
        if (concluidos >= 3) {
            break;
        }
    }
}

/* =========================
   MAIN: orquestra a impressão
   ========================= */
int main(void) {
    /* TORRE – recursivo */
    torre_cima_rec(PASSOS_TORRE_CIMA);
    torre_direita_rec(PASSOS_TORRE_DIREITA);

    printf("\n");  // separador entre peças

    /* BISPO – recursivo (NE e SO) */
    bispo_NE_rec(PASSOS_BISPO_NE);
    printf("\n");
    bispo_SO_rec(PASSOS_BISPO_SO);

    printf("\n");  // separador entre peças

    /* BISPO – loops aninhados (mesmo padrão acima) */
    bispo_NE_loops(2);
    printf("\n");
    bispo_SO_loops(2);

    printf("\n");  // separador entre peças

    /* RAINHA – recursivo: parte reta + parte diagonal */
    rainha_parte_reta_cima_rec(PASSOS_RAINHA_CIMA);
    rainha_diagonal_NO_rec(PASSOS_RAINHA_NO);

    printf("\n");  // separador entre peças

    /* CAVALO – loops aninhados + continue/break */
    cavalo_loops();

    printf("\n");  // linha em branco final
    return 0;
}
