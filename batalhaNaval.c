#include <stdio.h>
#include <stdbool.h> // Para usar o tipo 'bool'
#include <stdlib.h>    // Para usar a função abs() (valor absoluto)

// --- Constantes Globais do Jogo ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define HABILIDADE_TAMANHO 5 // Tamanho fixo (5x5) para as matrizes de habilidade

// --- Representação Visual no Tabuleiro ---
#define AGUA 0
#define NAVIO 3
#define EFEITO_HABILIDADE 5 // Novo valor para representar a área de efeito

// --- Protótipos das Funções ---
// Boa prática para organizar o código e declarar as funções antes de usá-las.
void criarMatrizCone(int tamanho, int matriz[tamanho][tamanho]);
void criarMatrizCruz(int tamanho, int matriz[tamanho][tamanho]);
void criarMatrizOctaedro(int tamanho, int matriz[tamanho][tamanho]);
void aplicarHabilidade(int tab_principal[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int hab_tamanho, 
                       int hab_matriz[hab_tamanho][hab_tamanho], 
                       int origem_linha, 
                       int origem_coluna);
void exibirMatrizHabilidade(int tamanho, int matriz[tamanho][tamanho], const char* nome);


int main() {
    // =======================================================================
    // ETAPA 1: CONFIGURAÇÃO DO TABULEIRO E NAVIOS (Lógica dos níveis anteriores)
    // =======================================================================

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Posiciona os 4 navios (horizontal, vertical, e duas diagonais)
    // Coordenadas dos navios
    int navio_h_linha = 1, navio_h_coluna = 1;
    int navio_v_linha = 3, navio_v_coluna = 8;
    int navio_d1_linha = 4, navio_d1_coluna = 1;
    int navio_d2_linha = 6, navio_d2_coluna = 6;
    
    // Posicionamento (código omitido para brevidade, mas deve estar aqui)
    // ... assumindo que os navios do nível anterior foram posicionados aqui ...
    for (int i=0; i<3; i++) tabuleiro[navio_h_linha][navio_h_coluna+i] = NAVIO;
    for (int i=0; i<3; i++) tabuleiro[navio_v_linha+i][navio_v_coluna] = NAVIO;
    for (int i=0; i<3; i++) tabuleiro[navio_d1_linha+i][navio_d1_coluna+i] = NAVIO;
    for (int i=0; i<3; i++) tabuleiro[navio_d2_linha+i][navio_d2_coluna-i] = NAVIO;


    // =======================================================================
    // ETAPA 2: CRIAÇÃO E APLICAÇÃO DAS HABILIDADES ESPECIAIS (Nível Mestre)
    // =======================================================================

    // --- 2.1 Criar Matrizes de Habilidade ---
    // Declara três matrizes 5x5 para armazenar o padrão de cada habilidade.
    int matrizCone[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO];
    int matrizCruz[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO];
    int matrizOctaedro[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO];

    // Gera os padrões de '0' e '1' para cada matriz usando as funções.
    criarMatrizCone(HABILIDADE_TAMANHO, matrizCone);
    criarMatrizCruz(HABILIDADE_TAMANHO, matrizCruz);
    criarMatrizOctaedro(HABILIDADE_TAMANHO, matrizOctaedro);

    // Exibe as matrizes de habilidade geradas (para verificação)
    exibirMatrizHabilidade(HABILIDADE_TAMANHO, matrizCone, "Cone");
    exibirMatrizHabilidade(HABILIDADE_TAMANHO, matrizCruz, "Cruz");
    exibirMatrizHabilidade(HABILIDADE_TAMANHO, matrizOctaedro, "Octaedro (Losango)");

    // --- 2.2 Integrar Habilidades ao Tabuleiro ---
    // Define os pontos de origem (centro) para cada habilidade no tabuleiro principal.
    int cone_origem_linha = 2, cone_origem_coluna = 5;
    int cruz_origem_linha = 7, cruz_origem_coluna = 2;
    int octaedro_origem_linha = 5, octaedro_origem_coluna = 5;

    // Chama a função para sobrepor cada matriz de habilidade no tabuleiro principal.
    printf("\nAplicando habilidades no tabuleiro...\n");
    aplicarHabilidade(tabuleiro, HABILIDADE_TAMANHO, matrizCone, cone_origem_linha, cone_origem_coluna);
    aplicarHabilidade(tabuleiro, HABILIDADE_TAMANHO, matrizCruz, cruz_origem_linha, cruz_origem_coluna);
    aplicarHabilidade(tabuleiro, HABILIDADE_TAMANHO, matrizOctaedro, octaedro_origem_linha, octaedro_origem_coluna);

    // =======================================================================
    // ETAPA 3: EXIBIR O RESULTADO FINAL
    // =======================================================================
    printf("\n--- Tabuleiro Final da Batalha Naval (Mestre) ---\n");
    printf("Legenda: %d-Agua | %d-Navio | %d-Area de Efeito\n", AGUA, NAVIO, EFEITO_HABILIDADE);
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/**
 * Gera uma matriz em formato de cone (triângulo apontando para baixo).
 * A lógica utiliza condicionais para desenhar o padrão. Para cada linha 'i',
 * a área afetada ('1') se expande horizontalmente a partir do centro.
 */
void criarMatrizCone(int tamanho, int matriz[tamanho][tamanho]) {
    int centro = tamanho / 2;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            // A condição verifica se a coluna 'j' está dentro do "alcance" do cone
            // para a linha 'i' atual. O alcance aumenta a cada linha.
            if (j >= centro - i && j <= centro + i) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * Gera uma matriz em formato de cruz.
 * A lógica é a mais simples: uma posição é afetada ('1') se estiver
 * na linha central OU na coluna central.
 */
void criarMatrizCruz(int tamanho, int matriz[tamanho][tamanho]) {
    int centro = tamanho / 2;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (i == centro || j == centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * Gera uma matriz em formato de octaedro (losango/diamante).
 * Utiliza a "distância de Manhattan" a partir do centro. Uma posição é
 * afetada se a soma das distâncias vertical e horizontal ao centro for
 * menor ou igual ao raio (o próprio centro). abs() calcula o valor absoluto.
 */
void criarMatrizOctaedro(int tamanho, int matriz[tamanho][tamanho]) {
    int centro = tamanho / 2;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * Sobrepõe uma matriz de habilidade ao tabuleiro principal.
 */
void aplicarHabilidade(int tab_principal[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int hab_tamanho, 
                       int hab_matriz[hab_tamanho][hab_tamanho], 
                       int origem_linha, 
                       int origem_coluna) {
    
    int centro_habilidade = hab_tamanho / 2;

    // Itera sobre a pequena matriz de habilidade (5x5)
    for (int i = 0; i < hab_tamanho; i++) {
        for (int j = 0; j < hab_tamanho; j++) {
            // Se a posição na matriz de habilidade é uma área de efeito ('1')
            if (hab_matriz[i][j] == 1) {
                // Calcula a coordenada correspondente no tabuleiro principal.
                // A fórmula (i - centro_habilidade) calcula o deslocamento
                // em relação ao centro da habilidade.
                int target_linha = origem_linha + (i - centro_habilidade);
                int target_coluna = origem_coluna + (j - centro_habilidade);

                // Requisito: Validação para não desenhar fora do tabuleiro.
                // Verifica se a coordenada calculada está dentro dos limites de 0 a 9.
                if (target_linha >= 0 && target_linha < TAMANHO_TABULEIRO &&
                    target_coluna >= 0 && target_coluna < TAMANHO_TABULEIRO) {
                    
                    // Marca a posição no tabuleiro principal com o valor da habilidade.
                    tab_principal[target_linha][target_coluna] = EFEITO_HABILIDADE;
                }
            }
        }
    }
}

/**
 * Função utilitária para exibir uma matriz de habilidade.
 * Ajuda a visualizar os padrões gerados e a depurar o código.
 */
void exibirMatrizHabilidade(int tamanho, int matriz[tamanho][tamanho], const char* nome) {
    printf("--- Matriz de Habilidade: %s ---\n", nome);
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}