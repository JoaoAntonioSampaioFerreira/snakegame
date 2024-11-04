#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#define MAXX 80
#define MAXY 24

struct Posicao {
    int x, y;
};

struct NodoCobra {
    struct Posicao pos;
    struct NodoCobra *proximo;
};

struct Cobra {
    struct NodoCobra *cabeca;
    int tamanho;
};

struct Comida {
    struct Posicao pos;
};

struct Jogo {
    struct Cobra *cobra;
    struct Comida *comida;
    int fimDeJogo;
    char direcao;
};

void iniciarJogo(struct Jogo *jogo);
void desenharJogo(struct Jogo *jogo);
void atualizarJogo(struct Jogo *jogo);
void encerrarJogo(struct Jogo *jogo);

int main() {
    static int tecla = 0;
    struct Jogo jogo;
    srand(time(0));

    iniciarJogo(&jogo);

    screenInit(1);
    keyboardInit();
    timerInit(100);

    while (!jogo.fimDeJogo) {
        desenharJogo(&jogo);

        if (keyhit()) {
            tecla = readch();
            switch (tecla) {
                case 'w':
                case 'a':
                case 's':
                case 'd':
                    jogo.direcao = tecla;
                    break;
                case 'q':
                    jogo.fimDeJogo = 1;
                    break;
            }
        }

        if (timerTimeOver() == 1) {
            atualizarJogo(&jogo);
        }
    }

    encerrarJogo(&jogo);

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

void iniciarJogo(struct Jogo *jogo) {
    jogo->cobra = (struct Cobra *)malloc(sizeof(struct Cobra));
    jogo->cobra->cabeca = (struct NodoCobra *)malloc(sizeof(struct NodoCobra));
    jogo->cobra->cabeca->pos.x = MAXX / 2;
    jogo->cobra->cabeca->pos.y = MAXY / 2;
    jogo->cobra->cabeca->proximo = NULL;
    jogo->cobra->tamanho = 3;

    struct NodoCobra *atual = jogo->cobra->cabeca;
    for (int i = 1; i < jogo->cobra->tamanho; ++i) {
        atual->proximo = (struct NodoCobra *)malloc(sizeof(struct NodoCobra));
        atual->proximo->pos.x = jogo->cobra->cabeca->pos.x - i;
        atual->proximo->pos.y = jogo->cobra->cabeca->pos.y;
        atual->proximo->proximo = NULL;
        atual = atual->proximo;
    }

    jogo->comida = (struct Comida *)malloc(sizeof(struct Comida));

    int margem = 5;
    jogo->comida->pos.x = rand() % (MAXX - 2 * margem) + margem;
    jogo->comida->pos.y = rand() % (MAXY - 2 * margem) + margem;

    jogo->fimDeJogo = 0;
    jogo->direcao = 'd';
}

void desenharJogo(struct Jogo *jogo) {
    screenClear();
    usleep(10000);

    screenGotoxy(0, 0);
    for (int i = 0; i < MAXX; ++i) {
        printf("-");
    }

    for (int i = 1; i < MAXY - 1; ++i) {
        screenGotoxy(0, i);
        printf("|");
        screenGotoxy(MAXX - 1, i);
        printf("|");
    }

    screenGotoxy(0, MAXY - 1);
    for (int i = 0; i < MAXX; ++i) {
        printf("-");
    }

    struct NodoCobra *atual = jogo->cobra->cabeca;
    while (atual != NULL) {
        screenGotoxy(atual->pos.x, atual->pos.y);
        printf("O");
        atual = atual->proximo;
    }
    screenGotoxy(jogo->comida->pos.x, jogo->comida->pos.y);
    printf("*");

    screenUpdate();
    usleep(10000);
}

void atualizarJogo(struct Jogo *jogo) {
    struct Posicao novaPos = jogo->cobra->cabeca->pos;
    switch (jogo->direcao) {
        case 'w':
            novaPos.y--;
            break;
        case 's':
            novaPos.y++;
            break;
        case 'a':
            novaPos.x--;
            break;
        case 'd':
            novaPos.x++;
            break;
    }

    if (novaPos.x < 1 || novaPos.x >= MAXX - 1 || novaPos.y < 1 || novaPos.y >= MAXY - 1) {
        jogo->fimDeJogo = 1;
        return;
    }

    struct NodoCobra *novaCabeca = (struct NodoCobra *)malloc(sizeof(struct NodoCobra));
    novaCabeca->pos = novaPos;
    novaCabeca->proximo = jogo->cobra->cabeca;

    jogo->cobra->cabeca = novaCabeca;

    if (novaPos.x == jogo->comida->pos.x && novaPos.y == jogo->comida->pos.y) {
        int margem = 5;
        jogo->comida->pos.x = rand() % (MAXX - 2 * margem) + margem;
        jogo->comida->pos.y = rand() % (MAXY - 2 * margem) + margem;
    } else {
        struct NodoCobra *atual = jogo->cobra->cabeca;
        while (atual->proximo->proximo != NULL) {
            atual = atual->proximo;
        }
        free(atual->proximo);
        atual->proximo = NULL;
    }

    struct NodoCobra *atual = jogo->cobra->cabeca->proximo;
    while (atual != NULL) {
        if (novaPos.x == atual->pos.x && novaPos.y == atual->pos.y) {
            jogo->fimDeJogo = 1;
            return;
        }
        atual = atual->proximo;
    }
}

void encerrarJogo(struct Jogo *jogo) {
    struct NodoCobra *atual = jogo->cobra->cabeca;
    while (atual != NULL) {
        struct NodoCobra *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(jogo->cobra);
    free(jogo->comida);
}