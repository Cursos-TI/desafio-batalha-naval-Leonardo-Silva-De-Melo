#include <stdio.h>
#include <stdbool.h> // Biblioteca para usar o tipo de dado 'bool' (true/false)

// --- Requisitos não funcionais: Legibilidade e Documentação ---
// Constantes para definir as características do jogo.
// Usar constantes torna o código mais legível e fácil de modificar.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    // --- 1. Represente o Tabuleiro ---
    // Declaração da matriz 10x10 que representará o nosso tabuleiro.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Documentação: Este bloco de código inicializa o tabuleiro.
    // Usamos dois loops 'for' aninhados para percorrer cada célula da matriz.
    // Cada célula (posição) do tabuleiro é preenchida com o valor de 'AGUA' (0).
    printf("Inicializando o tabuleiro %dx%d...\n", TAMANHO_TABULEIRO, TAMANHO_TABULEIRO);
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // --- 2. Posicione os Navios ---
    // As coordenadas iniciais dos navios são definidas diretamente no código,
    // conforme a simplificação para o nível básico.
    // Lembre-se que em C, os índices de arrays começam em 0.
    // Linha 2, Coluna 1 (horizontal) e Linha 4, Coluna 5 (vertical).
    int navio_horizontal_linha = 2;
    int navio_horizontal_coluna = 1;

    int navio_vertical_linha = 4;
    int navio_vertical_coluna = 5;

    // --- Posicionamento do Navio Horizontal com Validação ---
    // Documentação: Antes de posicionar, validamos se o navio cabe no tabuleiro.
    // A condição verifica se a coluna inicial mais o tamanho do navio não ultrapassa
    // o limite do tabuleiro.
    if ((navio_horizontal_coluna + TAMANHO_NAVIO) <= TAMANHO_TABULEIRO) {
        // Se a validação for bem-sucedida, um loop 'for' posiciona o navio.
        // Ele preenche as posições na matriz com o valor 'NAVIO' (3).
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_horizontal_linha][navio_horizontal_coluna + i] = NAVIO;
        }
    } else {
        // Caso a validação falhe, uma mensagem de erro é exibida.
        printf("ERRO: Navio horizontal fora dos limites do tabuleiro!\n");
        return 1; // Encerra o programa indicando um erro.
    }

    // --- Posicionamento do Navio Vertical com Validação ---
    // Documentação: Aqui, realizamos duas validações importantes.
    bool sobreposicao_detectada = false;

    // 1. Requisito funcional: Validar limites do tabuleiro.
    if ((navio_vertical_linha + TAMANHO_NAVIO) <= TAMANHO_TABULEIRO) {
        
        // 2. Requisito funcional: Validar sobreposição de navios.
        // Este loop verifica as células onde o navio vertical seria posicionado.
        // Se alguma dessas células já estiver ocupada por outro 'NAVIO',
        // a variável 'sobreposicao_detectada' se torna 'true'.
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_vertical_linha + i][navio_vertical_coluna] == NAVIO) {
                sobreposicao_detectada = true;
                break; // Se encontrou sobreposição, pode parar de verificar.
            }
        }

        // Se não houve sobreposição, posiciona o navio.
        if (!sobreposicao_detectada) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[navio_vertical_linha + i][navio_vertical_coluna] = NAVIO;
            }
        } else {
            printf("ERRO: Sobreposição detectada ao tentar posicionar o navio vertical!\n");
            return 1; // Encerra o programa indicando um erro.
        }

    } else {
        printf("ERRO: Navio vertical fora dos limites do tabuleiro!\n");
        return 1; // Encerra o programa indicando um erro.
    }


    // --- 3. Exiba o Tabuleiro ---
    // Documentação: Este bloco final exibe o estado atual do tabuleiro no console.
    // Novamente, loops aninhados são usados para percorrer a matriz.
    // printf("%d ", ...) imprime o valor da célula seguido de um espaço para formatação.
    // printf("\n"); é usado ao final de cada linha para criar a estrutura de grade.
    printf("\n--- Tabuleiro Final da Batalha Naval ---\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Pula para a próxima linha no console.
    }

    // Retorna 0 para indicar que o programa foi executado com sucesso.
    return 0;
}
