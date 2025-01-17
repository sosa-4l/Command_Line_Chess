#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

bool inside_board (int param) {
    if(param>7 || param< 0) return false;
    return true;
}

typedef struct peice
{
    char name;
    char team;
    int eliminated;
    int point;
    int row_num;
    int col_num;
    int moves;
};

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

struct peice *board[8][8] = {NULL};
struct peice *white_arr[2][8] = {NULL};
struct peice *black_arr[2][8] = {NULL};

 
 void white_init(void){
    for (int row =0; row< 2; row++) {
       for (int col = 0; col <8; col++){ //initialize everything to a pawn
                white_arr[row][col] = (struct peice*)malloc(sizeof(struct peice));
                white_arr[row][col]->name = 'P';
                white_arr[row][col]->team = 'W';
                white_arr[row][col]->eliminated = 0;
                white_arr[row][col]->point = 1;
                white_arr[row][col]->row_num = (row == 0) ? 1: 0;
                white_arr[row][col]->col_num = col;
                white_arr[row][col]->moves = 0;;
        } 
    }

    white_arr[1][0]->name = white_arr[1][7]->name = 'R';
    white_arr[1][0]->point = white_arr[1][7]->point = 5;

    white_arr[1][2]->name = white_arr[1][5]->name = 'B';
    white_arr[1][2]->point = white_arr[1][5]->point = 3;

    white_arr[1][1]->name = white_arr[1][6]->name = 'N';
    white_arr[1][1]->point = white_arr[1][6]->point = 3;

    white_arr[1][4]->name = 'Q';
    white_arr[1][4]->point = 9;
    
    white_arr[1][3]->name = 'K';
    white_arr[1][3]->point = 4;
 }

  void black_init(void){
    for (int row =0; row< 2; row++) {
       for (int col = 0; col <8; col++){ //initialize everything to a pawn
                black_arr[row][col] = (struct peice*)malloc(sizeof(struct peice));
                black_arr[row][col]->name = 'p';
                black_arr[row][col]->team = 'B';
                black_arr[row][col]->eliminated = 0;
                black_arr[row][col]->point = 1;
                black_arr[row][col]->row_num = (row == 0) ? 6: 7;;
                black_arr[row][col]->col_num = col;
                black_arr[row][col]->moves = 0;;
        } 
    }

    black_arr[1][0]->name = black_arr[1][7]->name = 'r';
    black_arr[1][0]->point = black_arr[1][7]->point = 5;

    black_arr[1][2]->name = black_arr[1][5]->name = 'b';
    black_arr[1][2]->point = black_arr[1][5]->point = 3;

    black_arr[1][1]->name = black_arr[1][6]->name = 'n';
    black_arr[1][1]->point = black_arr[1][6]->point = 3;

    black_arr[1][4]->name = 'q';
    black_arr[1][4]->point = 9;
    
    black_arr[1][3]->name = 'k';
    black_arr[1][3]->point = 4;
 }

 void board_init(){
    for (int col = 0; col<8; col++) {
        board[0][col] = white_arr[1][col];
        board[1][col] = white_arr[0][col];
    }
    for (int row = 6; row < 8; row++) {
        for (int col = 0; col<8; col++) {
            board[row][col] = black_arr[row-6][col];
        }
    }
 }

 void print_board(){
    printf("\n \n \n \n \n \n");
    printf(" ");
    for(int col= 0; col<8;col++){
        printf(" %c  ", 72-col);
    }
    printf("\n");
    printf(" --------------------------------\n");
    for(int row=0; row<8; row++){
        printf("|");
        for(int col=0; col<8; col++){
            if(!board[row][col]){
                printf("   ");
            } else{
                printf(" %c ", board[row][col]->name);
            }
            printf("|");
        }
        int tmp = row;
        printf("  %d\n", tmp+1);
        if (row < 7) {
            printf(" ---|---|---|---|---|---|---|---\n");
        }
    }
    printf(" --------------------------------\n");
}

