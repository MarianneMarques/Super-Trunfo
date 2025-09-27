// batalha_naval_habilidades.c
// Nível Mestre — Batalha Naval: habilidades especiais (Cone, Cruz, Octaedro)
// Cumpre: criação de matrizes de habilidade (0/1), sobreposição no tabuleiro 10x10,
// loops aninhados, condicionais, validação de limites e exibição clara no console.
//
// Símbolos no tabuleiro:
// 0 = Água, 3 = Navio, 5 = Área afetada por habilidade.
//
// Observação:
// - A habilidade CONE tem a ponta no "topo" da matriz e expande para baixo.
//   Ao sobrepor, o ponto de origem é alinhado na PONTA do cone.
// - As habilidades CRUZ e OCTAEDRO são centradas no ponto de origem.
//
// Compile: gcc -std=c99 batalha_naval_habilidades.c -o batalha
// Execute: ./batalha

#include <stdio.h>

#define N 10            // tamanho do tabuleiro
#define AGUA 0
#define NAVIO 3
#define AFETADO 5

// -------- Utilidades de impressão --------
void print_matriz_int(const char *titulo, int rows, int cols, int m[rows][cols]) {
    if (titulo) printf("%s\n", titulo);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_tabuleiro(int board[N][N]) {
    printf("TABULEIRO (0=água, 3=navio, 5=afetado)\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// -------- Criação das matrizes de habilidade (0/1) --------

// Cruz: tamanho deve ser ímpar (ex.: 5, 7). Centro em (mid, mid).
void cria_cruz(int size, int cruz[size][size]) {
    int mid = size / 2;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == mid || j == mid) cruz[i][j] = 1;
            else cruz[i][j] = 0;
        }
    }
}

// Octaedro (losango): usa distância Manhattan <= raio.
// size = 2*raio + 1 (ímpar). Centro em (mid, mid).
void cria_octaedro(int size, int octa[size][size]) {
    int mid = size / 2;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int di = (i > mid) ? i - mid : mid - i;
            int dj = (j > mid) ? j - mid : mid - j;
            if (di + dj <= mid) octa[i][j] = 1;  // dentro do losango
            else octa[i][j] = 0;
        }
    }
}

// Cone: ponta no topo (linha 0, coluna mid) e expandindo para baixo.
// radius controla o "abertura". Altura = radius+1; base_width = 2*radius + 1.
void cria_cone(int radius, int altura, int largura, int cone[altura][largura]) {
    // Por padrão, altura = radius + 1, largura = 2*radius + 1 (valores coerentes).
    int mid = largura / 2;
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            // largura efetiva cresce a cada linha: 2*i + 1
            int abertura = 2 * i + 1;
            int left  = mid - i;
            int right = mid + i;
            if (left < 0) left = 0;
            if (right >= largura) right = largura - 1;
            if (j >= left && j <= right) cone[i][j] = 1;
            else cone[i][j] = 0;
        }
    }
}

// -------- Sobreposição das habilidades no tabuleiro --------

// Sobrepõe matriz centrada no ponto de origem (para CRUZ e OCTAEDRO)
void sobrepoe_centrada(int board[N][N], int size, int mask[size][size], int origem_l, int origem_c) {
    int mid = size / 2;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (mask[i][j] == 1) {
                int tb_l = origem_l + (i - mid);
                int tb_c = origem_c + (j - mid);
                // valida limite
                if (tb_l >= 0 && tb_l < N && tb_c >= 0 && tb_c < N) {
                    board[tb_l][tb_c] = AFETADO;  // marca como afetado (sobrepõe visualmente)
                }
            }
        }
    }
}

// Sobrepõe CONE alinhando a PONTA do cone no ponto de origem.
// A matriz do cone cresce para "baixo" a partir da origem.
void sobrepoe_cone_por_ponta(int board[N][N], int altura, int largura, int cone[altura][largura],
                             int origem_l, int origem_c) {
    int mid = largura / 2;
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            if (cone[i][j] == 1) {
                int tb_l = origem_l + i;           // desce a partir da origem
                int tb_c = origem_c + (j - mid);   // centraliza horizontalmente em relação à coluna de origem
                if (tb_l >= 0 && tb_l < N && tb_c >= 0 && tb_c < N) {
                    board[tb_l][tb_c] = AFETADO;
                }
            }
        }
    }
}

// -------- Setup de navios para visualização --------
void zera_tabuleiro(int board[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            board[i][j] = AGUA;
}

void posiciona_navios_demo(int board[N][N]) {
    // Apenas alguns navios/células para visual:
    // Submarino (1 célula)
    board[2][2] = NAVIO;
    // Destroyer (2 células)
    board[5][6] = NAVIO;
    board[5][7] = NAVIO;
    // Cruzador (3 células)
    board[8][1] = NAVIO;
    board[8][2] = NAVIO;
    board[8][3] = NAVIO;
}

// -------- Programa principal --------
int main(void) {
    int board[N][N];
    zera_tabuleiro(board);
    posiciona_navios_demo(board);

    // --- Criar matrizes de habilidade ---
    // Cruz 5x5
    int size_cruz = 5;
    int cruz[size_cruz][size_cruz];
    cria_cruz(size_cruz, cruz);

    // Octaedro 5x5 (raio 2)
    int size_octa = 5;
    int octa[size_octa][size_octa];
    cria_octaedro(size_octa, octa);

    // Cone com "raio" 2 => altura=3, base=5
    int raio_cone = 2;
    int altura_cone = raio_cone + 1;     // 3
    int largura_cone = 2 * raio_cone + 1; // 5
    int cone[altura_cone][largura_cone];
    cria_cone(raio_cone, altura_cone, largura_cone, cone);

    // (Opcional) Exibir as matrizes de habilidade (0/1)
    print_matriz_int("Matriz da CRUZ (1=afetado):", size_cruz, size_cruz, cruz);
    print_matriz_int("Matriz do OCTAEDRO (1=afetado):", size_octa, size_octa, octa);
    print_matriz_int("Matriz do CONE (1=afetado, ponta no topo):", altura_cone, largura_cone, cone);

    // Exibir tabuleiro inicial
    print_tabuleiro(board);

    // --- Integrar habilidades ao tabuleiro ---
    // Defina aqui os pontos de origem (linha, coluna). Ajuste como quiser.
    // Observação: (0,0) é canto superior esquerdo.
    int origem_cruz_l = 3, origem_cruz_c = 3;   // centrada
    int origem_octa_l = 7, origem_octa_c = 7;   // centrada
    int origem_cone_l = 1, origem_cone_c = 5;   // ponta do cone

    sobrepoe_centrada(board, size_cruz, cruz, origem_cruz_l, origem_cruz_c);
    sobrepoe_centrada(board, size_octa, octa, origem_octa_l, origem_octa_c);
    sobrepoe_cone_por_ponta(board, altura_cone, largura_cone, cone, origem_cone_l, origem_cone_c);

    // Exibir tabuleiro final com as áreas afetadas
    print_tabuleiro(board);

    return 0;
}
