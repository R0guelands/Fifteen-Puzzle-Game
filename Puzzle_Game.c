#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void do_it(int tabuleiro[4][4]);
int distancia_manhattan(int tabulueiro_alt[4][4]);

int main() {

    //int tabuleiro[4][4] = {15, 2, 1, 12, 8, 5, 6, 11, 4, 9, 10, 7, 3, 14, 13, -1};
    int tabuleiro[4][4] = {6, 13, 7, 10, 8, 9, 11, -1, 15, 2, 12, 5, 14, 3, 1, 4}; 
    int tabuleiro2[4][4];
    int sn;

    printf("\nTabuleiro:\n");

    for (int x=0;x<4;x++) {
        printf("[ ");
        for (int y=0;y<4;y++){
            printf("%d ", tabuleiro[x][y]);
        }
        printf("]");
        printf("\n");
    }

    printf("\nSeguir com este tabuleiro? (0 - sim; 1 - nao): ");
    scanf("%d", &sn);

    if (sn == 1) {
        printf("\nDigite, casa por casa, o tabuleiro desejado (digite -1 para a casa em branco):\n");
        for (int x=0;x<4;x++) {
            for (int y=0;y<4;y++){
                printf("(linha:%d, coluna:%d): ", x, y);
                scanf("%d", &tabuleiro2[x][y]);
            }
        }
        printf("\n\n");
        for (int x=0;x<4;x++) {
            printf("[ ");
            for (int y=0;y<4;y++){
                printf("%d ", tabuleiro2[x][y]);
            }
            printf("]");
            printf("\n");
        }
    }

    printf("\nEste programa ira tentar resolver o presente tabuleiro.\n");

    
    if (sn == 1) {
        do_it(tabuleiro2);
    }else{
        do_it(tabuleiro);
    }

}

void do_it (int tabuleiro[4][4]) {

    int tabuleiro_alt[4][4];
    int possiveis[4];
    int possiveis_manh[4];
    int possiveis_cont;
    int posicao[2];
    int local;
    int movida = 0;
    int r;
    time_t t;
    srand((unsigned)time(&t));

    for (int xx=0;xx<4;xx++) {
        for (int yy=0;yy<4;yy++) {
            tabuleiro_alt[xx][yy] = tabuleiro[xx][yy];
        }
    }

    int contador_geral = 0;
    int vzs_dois = 0;

    while (distancia_manhattan(tabuleiro_alt) > 0) {

        r = rand() % (2);

        int possiveis_manh_menor = 300;  

        for (int x=0;x<4;x++){
            possiveis[x] = 0;
        }

        possiveis_cont = 0;

        for (int x=0;x<4;x++){
            for (int y=0;y<4;y++){
                if (tabuleiro_alt[x][y] == -1){
                    posicao[0] = x;
                    posicao[1] = y;
                }
            }
        }

        for (int x=0;x<4;x++){
            for (int y=0;y<4;y++){ 
                if ( (posicao[0] - x == 0 || posicao[1] - y == 0) && ((posicao[0] - x == 1 || posicao[1] - y == 1) || (posicao[0] - x == -1 || posicao[1] - y == -1) ) ) {
                    if (tabuleiro_alt[x][y] != movida) {
                        possiveis[possiveis_cont] = tabuleiro_alt[x][y];
                        tabuleiro_alt[x][y] = -1;
                        tabuleiro_alt[posicao[0]][posicao[1]] = possiveis[possiveis_cont];
                        possiveis_manh[possiveis_cont] = distancia_manhattan(tabuleiro_alt);           
                        if (r == 0) {
                            if (possiveis_manh[possiveis_cont] < possiveis_manh_menor) {
                                possiveis_manh_menor = possiveis_manh[possiveis_cont];
                                local = possiveis_cont;
                            }                                          
                            tabuleiro_alt[x][y] = possiveis[possiveis_cont]; 
                            tabuleiro_alt[posicao[0]][posicao[1]] = -1;                           
                            possiveis_cont += 1;   
                        }else{
                            if (possiveis_manh[possiveis_cont] <= possiveis_manh_menor) {
                                possiveis_manh_menor = possiveis_manh[possiveis_cont];
                                local = possiveis_cont;
                            }                                          
                            tabuleiro_alt[x][y] = possiveis[possiveis_cont]; 
                            tabuleiro_alt[posicao[0]][posicao[1]] = -1;                          
                            possiveis_cont += 1;  
                        }
                    }
                }
            }
        }

        for (int x=0;x<4;x++) {
            for (int y=0;y<4;y++) {
                if (tabuleiro_alt[x][y] == possiveis[local]) {
                    tabuleiro_alt[x][y] = -1;
                    tabuleiro_alt[posicao[0]][posicao[1]] = possiveis[local];
                    movida = possiveis[local];
                }
            }
        }

        contador_geral += 1;

        if (distancia_manhattan(tabuleiro_alt) == 2) {
            vzs_dois += 1;
            if (vzs_dois == 100) {
                vzs_dois = -1;
                break;
            }
        }
        
    }
    
    if (vzs_dois != -1) {
        printf("\n-----------\n\nVITORIA!!!!!!\nPassos: %d, manhattan: %d\n\n",contador_geral - 1, distancia_manhattan(tabuleiro_alt));
        for (int x=0;x<4;x++) {
            printf("[ ");
            for (int y=0;y<4;y++){
                printf("%d ", tabuleiro_alt[x][y]);
            }
            printf("]");
            printf("\n");
        }

    }else{
        printf("\n-----------\n\nEste tabuleiro nao possue resposta, sendo assim impossivel. Numero de passos: %d; Menor manhattan possivel: %d\n\n", contador_geral, distancia_manhattan(tabuleiro_alt));
        for (int x=0;x<4;x++) {
            printf("[ ");
            for (int y=0;y<4;y++){
                printf("%d ", tabuleiro_alt[x][y]);
            }
            printf("]");
            printf("\n");
        }
    }

}

int distancia_manhattan(int tabulueiro_alt[4][4]) {

    int gabarito[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,-1};
    int print[4][4];
    int manhattan_cont= 0;

    for (int x=0;x<4;x++) {
        for (int y=0;y<4;y++) {
            for (int linha=0;linha<4;linha++) {
                for (int coluna=0;coluna<4;coluna++) {
                    if (gabarito[x][y] == tabulueiro_alt[linha][coluna] && tabulueiro_alt[linha][coluna] != -1) {
                        print[linha][coluna] = abs(linha - x) + abs(coluna - y);
                        manhattan_cont += abs(linha - x) + abs(coluna - y);
                    }
                }
            }
        }
    }

    return manhattan_cont;

} 