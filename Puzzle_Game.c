#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int do_it(int tabuleiro[4][4]);

int main(){

    int x, y;
    int tabuleiro[4][4] = {15, 2, 1, 12, 8, 5, 6, 11, 4, 9, 10, 7, 3, 14, 13, -1};
    char sn;

    printf("\nTabuleiro:\n");

    for (x=0;x<4;x++) {

        printf("[ ");
        for (y=0;y<4;y++){

            printf("%d ", tabuleiro[x][y]);

        }
        printf("]");
        printf("\n");

    }

    printf("Deseja continuar com o presente tabuleiro? (s/n) ");
    scanf(" %c", &sn);

    if (sn == 's'){

            do_it(tabuleiro);

    }else if (sn == 'n'){

        printf("Cadastre uma nova matriz 4x4, com numeros de 1 a 15, deixando uma unica casa em branco via '-1':\n");
        for (x=0;x<4;x++) {

            for (y=0;y<4;y++){

                printf("Casa [%d][%d] = ", x, y);
                scanf("%d", &tabuleiro[x][y]);

            }

        }
        printf("Seu tabuleiro:\n");
        for (x=0;x<4;x++) {

            printf("[ ");
            for (y=0;y<4;y++){

                printf("%d ", tabuleiro[x][y]);

            }
            printf("]");
            printf("\n");

        }

        do_it(tabuleiro);

    }else{

        printf("Invalido. Encerrando a operacao.");

    }

}

int do_it (int tabuleiro[4][4]){

    time_t t;

    srand((unsigned) time(&t));

    int tentativas;
    int pontos[1] = {0};
    int contador = 0;
    int posicao[2] = {0, 0};
    int possiveis_cont;
    int x, y, r, r_max, pontos_cont;
    int tabuleiro_final[4][4];
    int tabuleiro_copia[4][4];
    int possiveis[4];
    int gabarito[4][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -1};
    int melhor[4][4];

    for (x=0;x<4;x++){
        for (y=0;y<4;y++){
            tabuleiro_final[x][y] = tabuleiro[x][y];
            tabuleiro_copia[x][y] = tabuleiro[x][y];
        }
    }

    printf("Quantas tentativas o programa tera?\n");
    scanf("%d", &tentativas);

    while (contador != tentativas){

        for (x=0;x<4;x++){
            possiveis[x] = 0;
        }

        possiveis_cont = 0;
        r_max = 0;     
        r = 0;   
        pontos_cont = 0;
        
        for (x=0;x>2;x++){
            posicao[x] = 0;
        }

        for (x=0;x<4;x++){
            for (y=0;y<4;y++){
                if (tabuleiro_final[x][y] == -1){
                    posicao[0] = x;
                    posicao[1] = y;
                }
            }
        }

        for (x=0;x<4;x++){
            for (y=0;y<4;y++){
                if ( (posicao[0] - x == 0 || posicao[1] - y == 0) && ((posicao[0] - x == 1 || posicao[1] - y == 1) || (posicao[0] - x == -1 || posicao[1] - y == -1) ) ){
                    possiveis[possiveis_cont] = tabuleiro_final[x][y];
                    possiveis_cont = possiveis_cont + 1;
                }
            }
        }

        for (x=0;x<4;x++){
            if (possiveis[x] != 0){
                r_max = r_max + 1;
            }
        }

        r = rand() % (r_max);
        
        for (x=0;x<4;x++){
            for (y=0;y<4;y++){
                if (tabuleiro_copia[x][y] == possiveis[r]){
                    tabuleiro_final[x][y] = (-1);
                } 
            }
        }

        for (x=0;x<4;x++){
            for (y=0;y<4;y++){
                if (tabuleiro_copia[x][y] == (-1)){
                    tabuleiro_final[x][y] = possiveis[r];
                }
            }
        }

        for (x=0;x<4;x++){
            for (y=0;y<4;y++){
                tabuleiro_copia[x][y] = tabuleiro_final[x][y];
            }
        }

        for (x=0;x<4;x++){
            for (y=0;y<4;y++){
                if(tabuleiro_final[x][y] == gabarito[x][y]){
                    pontos_cont = pontos_cont + 1;
                }
            }
        }
        if (pontos_cont > pontos[0]){
            pontos[0] = pontos_cont;
            for (x=0;x<4;x++){
                for (y=0;y<4;y++){
                    melhor[x][y] = tabuleiro_final[x][y];
                }
            }
        }

        contador = contador + 1;
    }

    printf("\nTabuleiro Original:\n");
    for (x=0;x<4;x++) {

        printf("[ ");
        for (y=0;y<4;y++){

            printf("%d ", tabuleiro[x][y]);

        }
        printf("]");
        printf("\n");

    }

    printf("\nTabuleiro Final:\n");
    for (x=0;x<4;x++) {

        printf("[ ");
        for (y=0;y<4;y++){

            printf("%d ", tabuleiro_final[x][y]);

        }
        printf("]");
        printf("\n");

    }

    printf("\nTabuleiro da melhor Pontuacao:\n");
    for (x=0;x<4;x++) {

        printf("[ ");
        for (y=0;y<4;y++){

            printf("%d ", melhor[x][y]);

        }
        printf("]");
        printf("\n");

    }

    printf("\nMelhor Pontuacao: %d/16 casas corretas.\n", pontos[0]);

}