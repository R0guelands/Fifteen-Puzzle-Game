#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void do_it(int board[4][4]);
int manhattan_distance(int tabulueiro_alt[4][4]);

int main() {

    //int board[4][4] = {15, 2, 1, 12, 8, 5, 6, 11, 4, 9, 10, 7, 3, 14, 13, -1};
    int board[4][4] = {6, 13, 7, 10, 8, 9, 11, -1, 15, 2, 12, 5, 14, 3, 1, 4}; 
    int board2[4][4];
    int sn;

    printf("\nboard:\n");

    for (int x=0;x<4;x++) {
        printf("[ ");
        for (int y=0;y<4;y++){
            printf("%d ", board[x][y]);
        }
        printf("]");
        printf("\n");
    }

    printf("\nSeguir com este board? (0 - sim; 1 - nao): ");
    scanf("%d", &sn);

    if (sn == 1) {
        printf("\nDigite, casa por casa, o board desejado (digite -1 para a casa em branco):\n");
        for (int x=0;x<4;x++) {
            for (int y=0;y<4;y++){
                printf("(line:%d, column:%d): ", x, y);
                scanf("%d", &board2[x][y]);
            }
        }
        printf("\n\n");
        for (int x=0;x<4;x++) {
            printf("[ ");
            for (int y=0;y<4;y++){
                printf("%d ", board2[x][y]);
            }
            printf("]");
            printf("\n");
        }
    }

    printf("\nEste programa ira tentar resolver o presente board.\n");

    
    if (sn == 1) {
        do_it(board2);
    }else{
        do_it(board);
    }

}

void do_it (int board[4][4]) {

    int board_alt[4][4];
    int possibles[4];
    int possibles_manh[4];
    int possibles_cont;
    int position[2];
    int local;
    int moved = 0;
    int r;
    time_t t;
    srand((unsigned)time(&t));

    for (int xx=0;xx<4;xx++) {
        for (int yy=0;yy<4;yy++) {
            board_alt[xx][yy] = board[xx][yy];
        }
    }

    int counter = 0;
    int times_two = 0;

    while (manhattan_distance(board_alt) > 0) {

        r = rand() % (2);

        int possibles_manh_minor = 300;  

        for (int x=0;x<4;x++){
            possibles[x] = 0;
        }

        possibles_cont = 0;

        for (int x=0;x<4;x++){
            for (int y=0;y<4;y++){
                if (board_alt[x][y] == -1){
                    position[0] = x;
                    position[1] = y;
                }
            }
        }

        for (int x=0;x<4;x++){
            for (int y=0;y<4;y++){ 
                if ( (position[0] - x == 0 || position[1] - y == 0) && ((position[0] - x == 1 || position[1] - y == 1) || (position[0] - x == -1 || position[1] - y == -1) ) ) {
                    if (board_alt[x][y] != moved) {
                        possibles[possibles_cont] = board_alt[x][y];
                        board_alt[x][y] = -1;
                        board_alt[position[0]][position[1]] = possibles[possibles_cont];
                        possibles_manh[possibles_cont] = manhattan_distance(board_alt);           
                        if (r == 0) {
                            if (possibles_manh[possibles_cont] < possibles_manh_minor) {
                                possibles_manh_minor = possibles_manh[possibles_cont];
                                local = possibles_cont;
                            }                                          
                            board_alt[x][y] = possibles[possibles_cont]; 
                            board_alt[position[0]][position[1]] = -1;                           
                            possibles_cont += 1;   
                        }else{
                            if (possibles_manh[possibles_cont] <= possibles_manh_minor) {
                                possibles_manh_minor = possibles_manh[possibles_cont];
                                local = possibles_cont;
                            }                                          
                            board_alt[x][y] = possibles[possibles_cont]; 
                            board_alt[position[0]][position[1]] = -1;                          
                            possibles_cont += 1;  
                        }
                    }
                }
            }
        }

        for (int x=0;x<4;x++) {
            for (int y=0;y<4;y++) {
                if (board_alt[x][y] == possibles[local]) {
                    board_alt[x][y] = -1;
                    board_alt[position[0]][position[1]] = possibles[local];
                    moved = possibles[local];
                }
            }
        }

        counter += 1;

        if (manhattan_distance(board_alt) == 2) {
            times_two += 1;
            if (times_two == 100) {
                times_two = -1;
                break;
            }
        }
        
    }
    
    if (times_two != -1) {
        printf("\n-----------\n\nVITORIA!!!!!!\nPassos: %d, manhattan: %d\n\n",counter - 1, manhattan_distance(board_alt));
        for (int x=0;x<4;x++) {
            printf("[ ");
            for (int y=0;y<4;y++){
                printf("%d ", board_alt[x][y]);
            }
            printf("]");
            printf("\n");
        }

    }else{
        printf("\n-----------\n\nEste board nao possue resposta, sendo assim impossivel. Numero de passos: %d; Menor manhattan possivel: %d\n\n", counter, manhattan_distance(board_alt));
        for (int x=0;x<4;x++) {
            printf("[ ");
            for (int y=0;y<4;y++){
                printf("%d ", board_alt[x][y]);
            }
            printf("]");
            printf("\n");
        }
    }

}

int manhattan_distance(int tabulueiro_alt[4][4]) {

    int template[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,-1};
    int print[4][4];
    int manhattan_cont= 0;

    for (int x=0;x<4;x++) {
        for (int y=0;y<4;y++) {
            for (int line=0;line<4;line++) {
                for (int column=0;column<4;column++) {
                    if (template[x][y] == tabulueiro_alt[line][column] && tabulueiro_alt[line][column] != -1) {
                        print[line][column] = abs(line - x) + abs(column - y);
                        manhattan_cont += abs(line - x) + abs(column - y);
                    }
                }
            }
        }
    }

    return manhattan_cont;

} 