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
int inicio = 0;       // posição da frente
int fim = 0;          // próxima posição livre
int quantidade = 0;   // quantidade atual na fila

// ----------- PILHA (linear) -------------
Peca pilha[TAMANHO_PILHA];
int topo = -1;        // índice do topo (inicia vazia)

int proximoID = 0;    // gera IDs únicos

// ----------------------------
// Gera uma nova peça automaticamente
// ----------------------------
Peca gerarPeca() {
    Peca nova;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = proximoID;
    proximoID++;
    return nova;
}

// ----------------------------
// Inserir na fila (enqueue)
// ----------------------------
void inserirPecaFila() {
    if (quantidade == TAMANHO_FILA) {
        printf("\nERRO: fila cheia.\n");
        return;
    }

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
    if (topo == TAMANHO_PILHA - 1) {
        printf("\nA pilha está cheia! Não é possível reservar.\n");
        return;
    }

    topo++;
    pilha[topo] = p;

    printf("\nPeça reservada: [%c %d]\n", p.nome, p.id);
}

// ----------------------------
// Desempilhar (pop)
// ----------------------------
void usarPecaReservada() {
    if (topo == -1) {
        printf("\nA pilha está vazia! Não há peça reservada.\n");
        return;
    }

    Peca usada = pilha[topo];
    topo--;

    printf("\nPeça usada da reserva: [%c %d]\n", usada.nome, usada.id);
}

// ----------------------------
// Jogar peça (remove da fila)
// ----------------------------
void jogarPeca() {
    if (quantidade == 0) {
        printf("\nFila vazia! Não há peça para jogar.\n");
        return;
    }

    Peca removida = removerPecaFila();
    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);

    // Sempre manter a fila cheia
    inserirPecaFila();
}

// ----------------------------
// Reservar peça (tira da fila → coloca na pilha)
// ----------------------------
void reservarPeca() {
    if (quantidade == 0) {
        printf("\nFila vazia! Não há peça para reservar.\n");
        return;
    }
    if (topo == TAMANHO_PILHA - 1) {
        printf("\nPilha cheia! Não é possível reservar mais peças.\n");
        return;
    }

    Peca removida = removerPecaFila();
    empilharPeca(removida);

    // repor a peça removida para manter fila cheia
    inserirPecaFila();
}

// ----------------------------
// Exibir estrutura atual
// ----------------------------
void exibirEstado() {
    printf("\n======================================\n");
    printf("Estado atual do jogo\n");

    // ---- Fila ----
    printf("\nFila de peças: ");
    if (quantidade == 0) {
        printf("(vazia)");
    } else {
        int pos = inicio;
        for (int i = 0; i < quantidade; i++) {
            printf("[%c %d] ", fila[pos].nome, fila[pos].id);
            pos = (pos + 1) % TAMANHO_FILA;
        }
    }

    
