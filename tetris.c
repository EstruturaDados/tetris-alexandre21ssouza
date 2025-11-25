#include <stdio.h>
#include <stdlib.h>

// Quantidade máxima da fila (fixa)
#define TAMANHO_FILA 5

// Estrutura que representa cada peça do Tetris
typedef struct {
    char nome;   // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;      // Identificador único
} Peca;

// Fila circular
Peca fila[TAMANHO_FILA];

int inicio = 0;  // posição da frente da fila
int fim = 0;     // próxima posição livre para inserir
int quantidade = 0; // quantidade atual de elementos na fila

int proximoID = 0; // usado para gerar IDs únicos automaticamente

// ----------------------------
// Função que gera uma peça nova automaticamente
// ----------------------------
Peca gerarPeca() {
    Peca nova;

    // Tipos possíveis de peça
    char tipos[4] = {'I', 'O', 'T', 'L'};

    nova.nome = tipos[rand() % 4];
    nova.id = proximoID; // ID único
    proximoID++;

    return nova;
}

// ----------------------------
// Inserir peça (enqueue)
// ----------------------------
void inserirPeca() {
    if (quantidade == TAMANHO_FILA) {
        printf("\nFila cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAMANHO_FILA; // fila circular
    quantidade++;

    printf("\nPeça inserida com sucesso!\n");
}

// ----------------------------
// Remover peça (dequeue)
// ----------------------------
void jogarPeca() {
    if (quantidade == 0) {
        printf("\nFila vazia! Não há peça para jogar.\n");
        return;
    }

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAMANHO_FILA; // avança circularmente
    quantidade--;

    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
}

// ----------------------------
// Exibir estado da fila
// ----------------------------
void exibirFila() {
    printf("\n---------------------------\n");
    printf("Fila de peças:\n");

    if (quantidade == 0) {
        printf("(vazia)\n");
    } else {
        int pos = inicio;
        for (int i = 0; i < quantidade; i++) {
            printf("[%c %d] ", fila[pos].nome, fila[pos].id);
            pos = (pos + 1) % TAMANHO_FILA;
        }
        printf("\n");
    }

    printf("---------------------------\n");
}

// ----------------------------
// Função principal
// ----------------------------
int main() {
    int opcao;

    // Inserir 5 peças iniciais
    for (int i = 0; i < TAMANHO_FILA; i++) {
        inserirPeca();
    }

    // Loop do menu
    do {
        exibirFila();

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca();
                break;

            case 2:
                inserirPeca();
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
