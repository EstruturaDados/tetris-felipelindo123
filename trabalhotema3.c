//nivel novato//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5   // tamanho fixo da fila

// -------------------------
// Definição da estrutura peça
// -------------------------
typedef struct {
    char tipo;   // 'I', 'O', 'T', 'L'
    int id;      // identificador único
} Peca;

// -------------------------
// Fila Circular
// -------------------------
typedef struct {
    Peca itens[TAM];
    int ini;   // índice do início
    int fim;   // índice do final
    int qtd;   // quantidade atual
} Fila;

// -------------------------
// Função para gerar novas peças automaticamente
// -------------------------
Peca gerarPeca() {
    Peca nova;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    nova.tipo = tipos[rand() % 4];
    nova.id = rand() % 10000; // número aleatório como ID
    return nova;
}

// Inicializa a fila com 5 peças
void inicializarFila(Fila *f) {
    f->ini = 0;
    f->fim = 0;
    f->qtd = 0;

    for (int i = 0; i < TAM; i++) {
        Peca p = gerarPeca();
        f->itens[f->fim] = p;
        f->fim = (f->fim + 1) % TAM;
        f->qtd++;
    }
}

// Retorna 1 se fila cheia
int filaCheia(Fila *f) {
    return f->qtd == TAM;
}

// Retorna 1 se fila vazia
int filaVazia(Fila *f) {
    return f->qtd == 0;
}

// Enfileirar (inserir peça automaticamente)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! (mas isso nunca deve ocorrer no nível novato)\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM;
    f->qtd++;
}

// Desenfileirar (jogar peça)
Peca dequeue(Fila *f) {
    Peca removida = {'X', -1};
    if (filaVazia(f)) {
        printf("Fila vazia! Não há peça para jogar.\n");
        return removida;
    }
    removida = f->itens[f->ini];
    f->ini = (f->ini + 1) % TAM;
    f->qtd--;
    return removida;
}

// Visualizar fila
void exibirFila(Fila *f) {
    printf("\n--- Fila Atual ---\n");
    int idx = f->ini;
    for (int i = 0; i < f->qtd; i++) {
        Peca p = f->itens[idx];
        printf("[%c | ID %d]\n", p.tipo, p.id);
        idx = (idx + 1) % TAM;
    }
    printf("------------------\n");
}

// -------------------------
// Programa Principal
// -------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    int opc;

    do {
        printf("\n==== MENU NIVEL NOVATO ====\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: {
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("Você jogou a peça: %c (ID %d)\n", jogada.tipo, jogada.id);
                }
                break;
            }
            case 2: {
                Peca nova = gerarPeca();
                enqueue(&fila, nova);
                printf("Nova peça inserida: %c (ID %d)\n", nova.tipo, nova.id);
                break;
            }
            case 3:
                exibirFila(&fila);
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opc != 0);

    return 0;
}
//nivel aventureiro//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// -------------------------
// Estrutura de Peça
// -------------------------
typedef struct {
    char tipo;
    int id;
} Peca;

// -------------------------
// Fila Circular
// -------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int ini;
    int fim;
    int qtd;
} Fila;

// -------------------------
// Pilha
// -------------------------
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;


// -------------------------
// Função para gerar automaticamente uma peça
// -------------------------
Peca gerarPeca() {
    Peca p;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    p.tipo = tipos[rand() % 4];
    p.id = rand() % 10000;
    return p;
}


// -------------------------
// Fila - Funções
// -------------------------
void inicializarFila(Fila *f) {
    f->ini = 0;
    f->fim = 0;
    f->qtd = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        Peca p = gerarPeca();
        f->itens[f->fim] = p;
        f->fim = (f->fim + 1) % TAM_FILA;
        f->qtd++;
    }
}

int filaVazia(Fila *f) {
    return (f->qtd == 0);
}

int filaCheia(Fila *f) {
    return (f->qtd == TAM_FILA);
}

Peca dequeue(Fila *f) {
    Peca removida = {'X', -1};

    if (filaVazia(f)) {
        printf("Fila vazia! (não deveria ocorrer)\n");
        return removida;
    }

    removida = f->itens[f->ini];
    f->ini = (f->ini + 1) % TAM_FILA;
    f->qtd--;
    return removida;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! (não deveria ocorrer)\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->qtd++;
}

void exibirFila(Fila *f) {
    printf("\n--- FILA DE PEÇAS FUTURAS ---\n");

    int idx = f->ini;
    for (int i = 0; i < f->qtd; i++) {
        Peca p = f->itens[idx];
        printf("[%c | ID %d]\n", p.tipo, p.id);
        idx = (idx + 1) % TAM_FILA;
    }

    printf("------------------------------\n");
}


// -------------------------
// Pilha - Funções
// -------------------------
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return (p->topo == -1);
}

int pilhaCheia(Pilha *p) {
    return (p->topo == TAM_PILHA - 1);
}

void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) {
        printf("PILHA CHEIA! Não é possível reservar mais peças.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = x;
}

Peca pop(Pilha *p) {
    Peca removida = {'X', -1};

    if (pilhaVazia(p)) {
        printf("Nenhuma peça reservada!\n");
        return removida;
    }

    removida = p->itens[p->topo];
    p->topo--;
    return removida;
}

void exibirPilha(Pilha *p) {
    printf("\n--- PILHA DE RESERVA ---\n");
    if (pilhaVazia(p)) {
        printf("[VAZIA]\n");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c | ID %d]\n", p->itens[i].tipo, p->itens[i].id);
        }
    }
    printf("-------------------------\n");
}


// -------------------------
// MENU PRINCIPAL — NIVEL AVENTUREIRO
// -------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opc;

    do {
        printf("\n========= MENU NÍVEL AVENTUREIRO =========\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça (push)\n");
        printf("3 - Usar peça reservada (pop)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: {
                // Jogar peça
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("Você jogou: %c (ID %d)\n", jogada.tipo, jogada.id);

                    // Inserção automática para manter a fila cheia
                    Peca nova = gerarPeca();
                    enqueue(&fila, nova);
                }
                break;
            }

            case 2: {
                // Reservar peça na pilha
                if (pilhaCheia(&pilha)) {
                    printf("Pilha cheia! Não pode reservar.\n");
                } else {
                    Peca frente = dequeue(&fila);
                    printf("Peça %c (ID %d) reservada!\n", frente.tipo, frente.id);
                    push(&pilha, frente);

                    // Repor peça automaticamente na fila
                    enqueue(&fila, gerarPeca());
                }
                break;
            }

            case 3: {
                // Usar peça reservada
                Peca usada = pop(&pilha);
                if (usada.id != -1) {
                    printf("Você usou a peça da reserva: %c (ID %d)\n",
                           usada.tipo, usada.id);
                }
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

        // Sempre exibir estado após ações
        exibirFila(&fila);
        exibirPilha(&pilha);

    } while (opc != 0);

    return 0;
}




//nivel mestre//




#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3
#define TAM_HIST 20   // histórico pequeno, suficiente para desfazer

// -------------------------------
// Estruturas
// -------------------------------
typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca itens[TAM_FILA];
    int ini;
    int fim;
    int qtd;
} Fila;

typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// Histórico simples: guarda peças usadas
typedef struct {
    Peca itens[TAM_HIST];
    int topo;
} Historico;


// -------------------------------
// Geração de peças
// -------------------------------
Peca gerarPeca() {
    Peca p;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    p.tipo = tipos[rand() % 4];
    p.id = rand() % 10000;
    return p;
}


// -------------------------------
// Histórico
// -------------------------------
void histInicializar(Historico *h) {
    h->topo = -1;
}

void histRegistrar(Historico *h, Peca p) {
    if (h->topo < TAM_HIST - 1) {
        h->itens[++h->topo] = p;
    }
}

Peca histDesfazer(Historico *h) {
    if (h->topo == -1)
        return (Peca){'X', -1};
    return h->itens[h->topo--];
}


// -------------------------------
// Fila
// -------------------------------
void filaInicializar(Fila *f) {
    f->ini = 0;
    f->fim = 0;
    f->qtd = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        Peca p = gerarPeca();
        f->itens[f->fim] = p;
        f->fim = (f->fim + 1) % TAM_FILA;
        f->qtd++;
    }
}

int filaVazia(Fila *f) {
    return f->qtd == 0;
}

Peca filaFrente(Fila *f) {
    if (filaVazia(f)) return (Peca){'X', -1};
    return f->itens[f->ini];
}

Peca dequeue(Fila *f) {
    if (filaVazia(f))
        return (Peca){'X', -1};

    Peca p = f->itens[f->ini];
    f->ini = (f->ini + 1) % TAM_FILA;
    f->qtd--;
    return p;
}

void enqueue(Fila *f, Peca p) {
    if (f->qtd == TAM_FILA) return;

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->qtd++;
}

void exibirFila(Fila *f) {
    printf("\n--- FILA ---\n");
    int idx = f->ini;
    for (int i = 0; i < f->qtd; i++) {
        Peca p = f->itens[idx];
        printf("[%c | %d]\n", p.tipo, p.id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("------------\n");
}


// -------------------------------
// Pilha
// -------------------------------
void pilhaInicializar(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

void push(Pilha *p, Peca x) {
    if (!pilhaCheia(p))
        p->itens[++p->topo] = x;
}

Peca pop(Pilha *p) {
    if (pilhaVazia(p))
        return (Peca){'X', -1};
    return p->itens[p->topo--];
}

Peca topo(Pilha *p) {
    if (pilhaVazia(p)) return (Peca){'X', -1};
    return p->itens[p->topo];
}

void exibirPilha(Pilha *p) {
    printf("\n--- PILHA ---\n");
    if (pilhaVazia(p)) printf("[vazia]\n");
    else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c | %d]\n", p->itens[i].tipo, p->itens[i].id);
        }
    }
    printf("-------------\n");
}


// -------------------------------
// Inverter fila e pilha
// -------------------------------
void inverterEstruturas(Fila *f, Pilha *p) {
    Pilha temp;
    pilhaInicializar(&temp);

    // 1) Passa toda a fila para pilha auxiliar
    while (!filaVazia(f)) {
        push(&temp, dequeue(f));
    }

    // 2) Passa toda a pilha original para fila
    while (!pilhaVazia(p)) {
        enqueue(f, pop(p));
    }

    // 3) Passa pilha auxiliar de volta à pilha
    while (!pilhaVazia(&temp)) {
        push(p, pop(&temp));
    }
}


// -------------------------------
// Trocar fila e pilha (topo <-> frente)
// -------------------------------
void trocar(Fila *f, Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Não há peça reservada para trocar.\n");
        return;
    }

    Peca frente = filaFrente(f);
    Peca topoP = topo(p);

    // troca simples
    f->itens[f->ini] = topoP;
    p->itens[p->topo] = frente;

    printf("Peças trocadas!\n");
}


// -------------------------------
// Programa Principal
// -------------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    Historico hist;

    filaInicializar(&fila);
    pilhaInicializar(&pilha);
    histInicializar(&hist);

    int opc;

    do {
        printf("\n======= MENU NÍVEL MESTRE =======\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar topo da pilha com frente da fila\n");
        printf("5 - Desfazer última jogada\n");
        printf("6 - Inverter fila e pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: {
                // Jogar peça
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("Jogou: %c (%d)\n", jogada.tipo, jogada.id);
                    histRegistrar(&hist, jogada);
                    enqueue(&fila, gerarPeca());
                }
                break;
            }

            case 2: {
                // Reservar peça
                if (!pilhaCheia(&pilha)) {
                    Peca p = dequeue(&fila);
                    push(&pilha, p);
                    histRegistrar(&hist, p);
                    enqueue(&fila, gerarPeca());
                } else {
                    printf("Pilha cheia!\n");
                }
                break;
            }

            case 3: {
                // Usar peça reservada
                Peca p = pop(&pilha);
                if (p.id != -1) {
                    printf("Usou peça reservada: %c (%d)\n", p.tipo, p.id);
                    histRegistrar(&hist, p);
                }
                break;
            }

            case 4:
                trocar(&fila, &pilha);
                break;

            case 5: {
                // Desfazer última jogada
                Peca desf = histDesfazer(&hist);
                if (desf.id != -1)
                    printf("Última jogada removida do histórico: %c (%d)\n", desf.tipo, desf.id);
                else
                    printf("Nada para desfazer!\n");
                break;
            }

            case 6:
                inverterEstruturas(&fila, &pilha);
                printf("Estruturas invertidas!\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

        exibirFila(&fila);
        exibirPilha(&pilha);

    } while (opc != 0);

    return 0;
}

