#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

// Estrutura que representa cada peça do Tetris
typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // Identificador único
} Peca;

// ----------- FILA (circular) -------------
Peca fila[TAMANHO_FILA];
int inicio = 0;
int fim = 0;
int quantidade = 0;

// ----------- PILHA (linear) -------------
Peca pilha[TAMANHO_PILHA];
int topo = -1;

int proximoID = 0;

// ----------------------------
// Gera uma nova peça automaticamente
// ----------------------------
Peca gerarPeca() {
    Peca nova;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = proximoID++;
    return nova;
}

// ----------------------------
// Inserir na fila (enqueue)
// ----------------------------
void inserirPecaFila() {
    if (quantidade == TAMANHO_FILA) return;

    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAMANHO_FILA;
    quantidade++;
}

// ----------------------------
// Remover da fila (dequeue)
// ----------------------------
Peca removerPecaFila() {
    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAMANHO_FILA;
    quantidade--;
    return removida;
}

// ----------------------------
// Empilhar (push)
// ----------------------------
void empilharPeca(Peca p) {
    topo++;
    pilha[topo] = p;
}

// ----------------------------
// Desempilhar (pop)
// ----------------------------
Peca desempilhar() {
    Peca p = pilha[topo];
    topo--;
    return p;
}

// ----------------------------
// Jogar peça
// ----------------------------
void jogarPeca() {
    if (quantidade == 0) {
        printf("\nFila vazia!\n");
        return;
    }

    Peca removida = removerPecaFila();
    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);

    // Repor automaticamente
    inserirPecaFila();
}

// ----------------------------
// Reservar peça (fila → pilha)
// ----------------------------
void reservarPeca() {
    if (quantidade == 0) {
        printf("\nFila vazia!\n");
        return;
    }
    if (topo == TAMANHO_PILHA - 1) {
        printf("\nPilha cheia! Não é possível reservar.\n");
        return;
    }

    Peca removida = removerPecaFila();
    empilharPeca(removida);

    printf("\nPeça reservada: [%c %d]\n", removida.nome, removida.id);

    inserirPecaFila();
}

// ----------------------------
// Usar peça reservada (pilha → fora do jogo)
// ----------------------------
void usarPecaReservada() {
    if (topo == -1) {
        printf("\nPilha vazia! Não há peça para usar.\n");
        return;
    }

    Peca usada = desempilhar();
    printf("\nPeça usada da reserva: [%c %d]\n", usada.nome, usada.id);
}

// ----------------------------
// Trocar peça da fila com topo da pilha
// ----------------------------
void trocarFrenteComTopo() {
    if (topo == -1) {
        printf("\nA pilha está vazia! Não é possível trocar.\n");
        return;
    }
    if (quantidade == 0) {
        printf("\nA fila está vazia! Não é possível trocar.\n");
        return;
    }

    Peca temp = fila[inicio];
    fila[inicio] = pilha[topo];
    pilha[topo] = temp;

    printf("\nTroca realizada entre frente da fila e topo da pilha!\n");
}

// ----------------------------
// Troca múltipla (3 peças)
// ----------------------------
void trocarTresPecas() {
    if (quantidade < 3) {
        printf("\nA fila não possui 3 peças para trocar.\n");
        return;
    }
    if (topo < 2) {
        printf("\nA pilha não possui 3 peças para trocar.\n");
        return;
    }

    int posFila = inicio;

    for (int i = 0; i < 3; i++) {
        Peca temp = fila[posFila];
        fila[posFila] = pilha[topo - i];
        pilha[topo - i] = temp;

        posFila = (posFila + 1) % TAMANHO_FILA;
    }

    printf("\nTroca múltipla realizada entre as 3 primeiras da fila e as 3 da pilha!\n");
}

// ----------------------------
// Exibir estado atual
// ----------------------------
void exibirEstado() {
    printf("\n======================================\n");
    printf("Estado atual do jogo\n");

    // ---- Fila ----
    printf("\nFila de peças:  ");
    if (quantidade == 0) {
        printf("(vazia)");
    } else {
        int pos = inicio;
        for (int i = 0; i < quantidade; i++) {
            printf("[%c %d] ", fila[pos].nome, fila[pos].id);
            pos = (pos + 1) % TAMANHO_FILA;
        }
    }

    // ---- Pilha ----
    printf("\nPilha de reserva (Topo -> base): ");
    if (topo == -1) {
        printf("(vazia)");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n======================================\n");
}

// ----------------------------
// Função principal
// ----------------------------
int main() {
    int opcao;

    // Preencher fila inicial
    for (int i = 0; i < TAMANHO_FILA; i++) {
        inserirPecaFila();
    }

    do {
        exibirEstado();

        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Trocar 3 primeiras da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: jogarPeca(); break;
            case 2: reservarPeca(); break;
            case 3: usarPecaReservada(); break;
            case 4: trocarFrenteComTopo(); break;
            case 5: trocarTresPecas(); break;
            case 0: printf("\nEncerrando...\n"); break;
            default: printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
