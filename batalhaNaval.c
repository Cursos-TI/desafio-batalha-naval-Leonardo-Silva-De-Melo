#include <stdio.h>
#include <stdbool.h> // Biblioteca para usar o tipo de dado 'bool' (true/false)

// --- Requisitos não funcionais: Legibilidade e Documentação ---
// Constantes que definem as regras do jogo.
// Manter essas definições facilita futuras modificações.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    // --- 1. Criar um Tabuleiro 10x10 ---
    // A declaração e inicialização do tabuleiro permanecem as mesmas.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Documentação: Este bloco inicializa o tabuleiro com 'AGUA' (0) em todas as posições.
    // Loops aninhados percorrem cada célula da matriz para garantir um tabuleiro limpo no início.
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // --- 2. Posicionar Quatro Navios ---
    // Coordenadas iniciais (canto superior esquerdo do navio) definidas no código.
    // Escolhi posições que não se sobrepõem para um resultado de sucesso.
    int navio_h_linha = 1, navio_h_coluna = 1; // Navio Horizontal
    int navio_v_linha = 3, navio_v_coluna = 8; // Navio Vertical
    int navio_d1_linha = 4, navio_d1_coluna = 1; // Navio Diagonal Principal ( \ )
    int navio_d2_linha = 6, navio_d2_coluna = 6; // Navio Diagonal Secundária ( / )

    bool sobreposicao_detectada = false;

    // --- Posicionamento do Navio Horizontal (igual ao nível anterior) ---
    if ((navio_h_coluna + TAMANHO_NAVIO) <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_h_linha][navio_h_coluna + i] = NAVIO;
        }
    } else {
        printf("ERRO: Navio horizontal fora dos limites!\n"); return 1;
    }

    // --- Posicionamento do Navio Vertical (igual ao nível anterior) ---
    if ((navio_v_linha + TAMANHO_NAVIO) <= TAMANHO_TABULEIRO) {
        // Validação de sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_v_linha + i][navio_v_coluna] == NAVIO) { sobreposicao_detectada = true; break; }
        }
        if (!sobreposicao_detectada) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[navio_v_linha + i][navio_v_coluna] = NAVIO;
            }
        } else {
            printf("ERRO: Sobreposição no navio vertical!\n"); return 1;
        }
    } else {
        printf("ERRO: Navio vertical fora dos limites!\n"); return 1;
    }

    // --- Posicionamento do Navio Diagonal Principal ( \ ) ---
    // Documentação: Para um navio na diagonal principal, tanto a linha quanto a coluna aumentam.
    // Portanto, a validação deve checar ambos os limites.
    if ((navio_d1_linha + TAMANHO_NAVIO) <= TAMANHO_TABULEIRO && (navio_d1_coluna + TAMANHO_NAVIO) <= TAMANHO_TABULEIRO) {
        // Validação de sobreposição: verifica as células [linha+i][coluna+i]
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_d1_linha + i][navio_d1_coluna + i] == NAVIO) { sobreposicao_detectada = true; break; }
        }
        if (!sobreposicao_detectada) {
            // Posiciona o navio incrementando linha e coluna simultaneamente.
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[navio_d1_linha + i][navio_d1_coluna + i] = NAVIO;
            }
        } else {
            printf("ERRO: Sobreposição no navio diagonal principal!\n"); return 1;
        }
    } else {
        printf("ERRO: Navio diagonal principal fora dos limites!\n"); return 1;
    }

    // --- Posicionamento do Navio Diagonal Secundária ( / ) ---
    // Documentação: Para um navio na diagonal secundária, a linha aumenta e a coluna diminui.
    // A validação de limite deve checar se a linha não excede o limite inferior e se a
    // coluna não excede o limite esquerdo (coluna >= 0).
    if ((navio_d2_linha + TAMANHO_NAVIO) <= TAMANHO_TABULEIRO && (navio_d2_coluna - (TAMANHO_NAVIO - 1)) >= 0) {
        // Validação de sobreposição: verifica as células [linha+i][coluna-i]
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_d2_linha + i][navio_d2_coluna - i] == NAVIO) { sobreposicao_detectada = true; break; }
        }
        if (!sobreposicao_detectada) {
            // Posiciona o navio incrementando a linha e decrementando a coluna.
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[navio_d2_linha + i][navio_d2_coluna - i] = NAVIO;
            }
        } else {
            printf("ERRO: Sobreposição no navio diagonal secundária!\n"); return 1;
        }
    } else {
        printf("ERRO: Navio diagonal secundária fora dos limites!\n"); return 1;
    }

    // --- 3. Exibir o Tabuleiro ---
    // A exibição do tabuleiro final permanece a mesma, mostrando o resultado completo.
    printf("\n--- Tabuleiro Final da Batalha Naval (Aventureiro) ---\n");
    // Adiciona um cabeçalho de colunas para melhor visualização
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Adiciona um cabeçalho de linhas
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0; // Indica que o programa foi executado com sucesso.
}