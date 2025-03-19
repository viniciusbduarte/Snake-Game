#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define LARGURA 60
#define ALTURA 20

typedef struct No {
    int x, y;
    struct No *proximo;
} No;

No *cabeca = NULL, *cauda = NULL;
int comidaX, comidaY;
int jogoAcabou = 0;
int direcao = 'd';
int pontuacao = 0;
int recorde = 0;

void gerarComida() {
    comidaX = (rand() % (LARGURA - 2)) + 1;
    comidaY = (rand() % (ALTURA - 2)) + 1;
}

void iniciarCobra() {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->x = LARGURA / 2;
    novoNo->y = ALTURA / 2;
    novoNo->proximo = NULL;
    cabeca = cauda = novoNo;
    gerarComida();
    jogoAcabou = 0;
    direcao = 'd';
    pontuacao = 0;
}

void moverCobra() {
    int novoX = cabeca->x, novoY = cabeca->y;

    if (direcao == 'w') novoY--;
    else if (direcao == 's') novoY++;
    else if (direcao == 'a') novoX--;
    else if (direcao == 'd') novoX++;

    if (novoX <= 0 || novoX >= LARGURA - 1 || novoY <= 0 || novoY >= ALTURA - 1) {
        jogoAcabou = 1;
        return;
    }

    No *temp = cabeca;
    while (temp) {
        if (temp->x == novoX && temp->y == novoY) {
            jogoAcabou = 1;
            return;
        }
        temp = temp->proximo;
    }

    No *novaCabeca = (No *)malloc(sizeof(No));
    novaCabeca->x = novoX;
    novaCabeca->y = novoY;
    novaCabeca->proximo = cabeca;
    cabeca = novaCabeca;

    if (novoX == comidaX && novoY == comidaY) {
        pontuacao++;
        gerarComida();
    } else {
        temp = cabeca;
        while (temp->proximo->proximo) {
            temp = temp->proximo;
        }
        free(temp->proximo);
        temp->proximo = NULL;
        cauda = temp;
    }
}

void desenharCobraASCII() {
    printf("\n\n           /^\\/^\\\n");
    printf("           _|__|  O|\n");
    printf("    /\\     /~     \\_/ \\\n");
    printf("    \\____|__________/  \\\n");
    printf("           \\_______      \\\n");
    printf("                   `\\     \\                 \\\n");
    printf("                     |     |                  \\\n");
    printf("                    /      /                    \\\n");
    printf("                   /     /                       \\\\\n");
    printf("                 /      /                         \\ \\\n");
    printf("                /     /                            \\  \\\n");
    printf("              /     /             _----_            \\   \\\n");
    printf("             /     /           _-~      ~-_         |   |\n");
    printf("            (      (        _-~    _--_    ~-_     _/   |\n");
    printf("             \\      ~-____-~    _-~    ~-_    ~-_-~    /\n");
    printf("               ~-_           _-~          ~-_       _-~\n");
    printf("                  ~--______-~                ~-___-~\n");
    printf("\n\n                        THE SNAKE GAME\n");
}







void desenhar() {
    system("cls");

    // Exibe a pontuação e o recorde no topo da tela
    for (int i=0; i <LARGURA; i++)printf("#");
    printf("\n");
    for (int i=0; i <LARGURA/4; i++)printf(" ");
    printf("Pontos: %d   |   Recorde: %d\n", pontuacao, recorde);


    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (i == 0 || i == ALTURA - 1 || j == 0 || j == LARGURA - 1) {
                printf("#");
            } else if (i == comidaY && j == comidaX) {
                printf("*");
            } else {
                int ehCorpo = 0;
                No *temp = cabeca;
                while (temp) {
                    if (temp->x == j && temp->y == i) {
                        printf("O");
                        ehCorpo = 1;
                        break;
                    }
                    temp = temp->proximo;
                }
                if (!ehCorpo) {
                    // Exibe o "GAME OVER" dentro do campo
                    if (jogoAcabou) {
                        int centroX = (LARGURA - 25) / 2;
                        int centroY = ALTURA / 2 - 4;
                        if (i == centroY && j >= centroX && j < centroX + 25) {
                            printf("%c", "#########################"[j - centroX]);
                        } else if (i == centroY + 1 && j >= centroX && j < centroX + 25) {
                            printf("%c", "#       GAME OVER       #"[j - centroX]);
                        } else if (i == centroY + 2 && j >= centroX && j < centroX + 25) {
                            printf("%c", "#########################"[j - centroX]);
                        } else if (i == centroY + 4 && j >= centroX && j < centroX + 25) {
                            printf("%c", "#########################"[j - centroX]);
                        } else if (i == centroY + 5 && j >= centroX && j < centroX + 25) {
                            printf("%c", "#  PLAY AGAIN? (s/n)    #"[j - centroX]);
                        } else if (i == centroY + 6 && j >= centroX && j < centroX + 25) {
                            printf("%c", "#########################"[j - centroX]);
                        } else {
                            printf(" ");
                        }
                    } else {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }


}

void entrada() {
    if (_kbhit()) {
        char tecla = _getch();
        if ((tecla == 'w' && direcao != 's') ||
            (tecla == 's' && direcao != 'w') ||
            (tecla == 'a' && direcao != 'd') ||
            (tecla == 'd' && direcao != 'a')) {
            direcao = tecla;
        }
    }
}

void PreJogo(){
        system("cls");
        desenharCobraASCII();
        Sleep(1000);
        system("cls");
        printf("  ####\n ##  ##\n     ##\n   ###\n     ##\n ##  ##\n  ####\n");
        Sleep(1000);
        system("cls");
        printf(" ####\n ##  ##\n     ##\n   ###\n  ##\n ##  ##\n ######\n");
        Sleep(1000);
        system("cls");
        printf("  ##\n ###\n  ##\n  ##\n  ##\n  ##\n######\n");
        Sleep(1000);
        system("cls");
        printf("  ####     ####      ##\n ##  ##   ##  ##     ##\n ##       ##  ##     ##\n ## ###   ##  ##     ##\n ##  ##   ##  ##\n ##  ##   ##  ##\n  ####     ####      ##\n");
        Sleep(1000);


}
void limparCobra() {
    No *temp;
    while (cabeca) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
}

int main() {
    char opcao;
    srand(time(NULL));
    do {
        PreJogo();
        iniciarCobra();
        while (!jogoAcabou) {
            desenhar();
            entrada();
            moverCobra();
            Sleep(100);
        }
        if (pontuacao > recorde) {
            recorde = pontuacao;
        }
        desenhar();
        opcao = _getch();
        limparCobra();
    } while (opcao == 's' || opcao == 'S');
    return 0;
}
