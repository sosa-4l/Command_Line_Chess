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

bool pawn_move(int old_row, int old_col, int new_row, int new_col){
    int row_dif = abs(old_row-new_row);
    if (row_dif > 2 || row_dif == 0){
        return false;
    } else if (row_dif == 2) {
        if (board[old_row][old_col]->moves != 0) {
            return false;
        }
        if (old_col != new_col) return false;
        if (board[new_row][new_col]) return false;
        return true;
    } else {
        if (old_col == new_col && !board[new_row][new_col]) {
            return true;
        } else if (abs(old_col - new_col) == 1 && board[new_row][new_col]->team != board[old_row][old_col]->team){
            return true;
        } else{
            return false;
        }
    }
}

bool bishop_move(int old_row, int old_col, int new_row, int new_col) {
    int row_increment, col_increment;
    row_increment = (old_row < new_row) ? 1 : -1;
    col_increment = (old_col < new_col) ? 1 : -1;

    int cur_row = old_row + row_increment;
    int cur_col = old_col + col_increment;
    while(cur_col>-1 && cur_col<8 && cur_row>-1 && cur_row<8) {
        if(cur_row== new_row && cur_col== new_col){
            if(!board[new_row][new_col]) {
                return true;
            } else return !(board[new_row][new_col]->team == board[old_row][old_col]->team);
        } else {
            if (board[cur_row][cur_col]) {
                return false;
            }
        }
        cur_col = cur_col + col_increment;
        cur_row = cur_row + row_increment;
    }
    return false;
}

bool knight_move(int old_row, int old_col, int new_row, int new_col) {
    int row_diff = new_row - old_row;
    int col_diff = new_col - old_col;

    bool check_1 = (abs(row_diff) == 1) && (abs(col_diff) == 2);
    bool check_2 = (abs(row_diff) == 2) && (abs(col_diff) == 1);

    if(!(check_1 || check_2)) return false;

    if(!board[new_row][new_col]) {
        return true;
    } else return !(board[new_row][new_col]->team == board[old_row][old_col]->team);
}

bool rook_move(int old_row, int old_col, int new_row, int new_col) {
    int count;
    if (old_row == new_row) {
        count = (old_col < new_col) ? 1 : -1;
        int cur_col = old_col+count;
        while(cur_col >-1 && cur_col<8) {
        if(cur_col== new_col){
            if(!board[new_row][new_col]) {
                return true;
            } else return !(board[new_row][new_col]->team == board[old_row][old_col]->team);
        } else {
            if (board[old_row][cur_col]) {
                return false;
            }
        }
        cur_col += count;
        }
    } else if (old_col == new_col) {
        count = (old_row < new_row) ? 1 : -1;
        int cur_row = old_row+count;
        while(cur_row >-1 && cur_row<8) {
        if(cur_row== new_row){
            if(!board[new_row][new_col]) {
                return true;
            } else return !(board[new_row][new_col]->team == board[old_row][old_col]->team);
        } else {
            if (board[cur_row][old_col]) {
                return false;
            }
        }
        cur_row += count;
        }
    }
    return false;
}

bool queen_move (int old_row, int old_col, int new_row, int new_col) {
    return (rook_move(old_row, old_col, new_row, new_col) || bishop_move(old_row, old_col, new_row, new_col));
}

bool king_move(int old_row, int old_col, int new_row, int new_col) {
    int row_diff = new_row - old_row;
    int col_diff = new_col - old_col;

    bool check_1 = (abs(row_diff) == 1) || (abs(row_diff) == 0);
    bool check_2 = (abs(col_diff) == 1) || (abs(col_diff) == 0);

    if(!(check_1 && check_2)) return false;

    if(!board[new_row][new_col]) {
        return true;
    } else return !(board[new_row][new_col]->team == board[old_row][old_col]->team);
}

struct peice *update_board (int old_row, int old_col, int new_row, int new_col) {
    struct peice *tmp = board[new_row][new_col];
    if (board[new_row][new_col]) {
        board[new_row][new_col]->eliminated = 1;
    }
    board[new_row][new_col] = board[old_row][old_col]; 
    board[old_row][old_col] = NULL;
    board[new_row][new_col]->moves++;
    board[new_row][new_col]->row_num = new_row;
    board[new_row][new_col]->col_num = new_col;
    return tmp;
}

void revert_board (struct peice* old_peice, int old_row, int old_col, int new_row, int new_col) {
    if (old_peice) {
        old_peice->eliminated = 0;
    }
    board[old_row][old_col] = board[new_row][new_col] ;
    board[new_row][new_col] = old_peice; 
    board[old_row][old_col]->moves--;
    board[old_row][old_col]->row_num = old_row;
    board[old_row][old_col]->col_num = old_col;
}

bool white_check(int king_row, int king_col) {
    int col_no;
    int row_no;
    for(int row = 0; row<2; row++){
        for (int col=0; col<8; col++){
            if (black_arr[row][col]->eliminated) continue;

            col_no = black_arr[row][col]->col_num;
            row_no = black_arr[row][col]->row_num;

            if(black_arr[row][col]->name == 'p' && pawn_move(row_no, col_no, king_row, king_col)) {
                return true;
            } else if (black_arr[row][col]->name == 'b' && bishop_move(row_no, col_no, king_row, king_col)) {
                return true;
            } else if (black_arr[row][col]->name == 'r' && rook_move(row_no, col_no, king_row, king_col)) {
                return true;
            } else if (black_arr[row][col]->name == 'q' && queen_move(row_no, col_no, king_row, king_col)) {
                return true;
            } else if (black_arr[row][col]->name == 'n' && knight_move(row_no, col_no, king_row, king_col)) {
                return true;
            } else if (black_arr[row][col]->name == 'k' && king_move(row_no, col_no, king_row, king_col)) {
                return true;
            } 
        }
    }
    return false;
}

bool black_check(int king_row, int king_col) {
    int col_no;
    int row_no;
    for(int row = 0; row<2; row++){
        for (int col=0; col<8; col++){
            if (white_arr[row][col]->eliminated) continue;

            col_no = white_arr[row][col]->col_num;
            row_no = white_arr[row][col]->row_num;

            if(white_arr[row][col]->name == 'P' && pawn_move(row_no, col_no, king_row, king_col)) {
                return true;
            } else if (white_arr[row][col]->name == 'B' && bishop_move(row_no, col_no, king_row, king_col)) {
                return true;
            } else if (white_arr[row][col]->name == 'R' && rook_move(row_no, col_no, king_row, king_col)) {
                return true;
            } else if (white_arr[row][col]->name == 'Q' && queen_move(row_no, col_no, king_row, king_col)) {
                return true;
            } else if (white_arr[row][col]->name == 'N' && knight_move(row_no, col_no, king_row, king_col)) {
                return true;
            } else if (white_arr[row][col]->name == 'K' && king_move(row_no, col_no, king_row, king_col)) {
                return true;
            } 
        }
    }
    return false;
}

bool white_checkmate_xwrap(int row_val, int col_val){
        if ((!board[row_val][col_val]) ){
            return white_check(row_val, col_val);
        } if ((board[row_val][col_val]->team =='B')){
            struct peice* tmp = update_board(white_arr[1][3]->row_num, white_arr[1][3]->col_num, row_val, col_val);
            if (white_check(row_val, col_val)){ 
                return true;
            } else return false;
        }else return false;
}

bool black_checkmate_xwrap(int row_val, int col_val){
        if ((!board[row_val][col_val]) || (board[row_val][col_val]->team =='W')){
            return black_check(row_val, col_val);
        } else return false;
}

bool white_checkmate(void){
    int king_row = white_arr[1][3]->row_num;
    int king_col = white_arr[1][3]->col_num ;

    for(int j=-1;j<2;j++){
        int tmp_row = king_row+j;
        for(int i=-1; i<2;i++){
            int tmp_col = king_col+i;
            if (inside_board(tmp_col) && inside_board(tmp_row)) {
                if(!white_checkmate_xwrap(tmp_row,tmp_col)) return false;
            } else continue;
        }
    }
    return false;
    
}

bool black_checkmate(void){
    int king_row = black_arr[1][3]->row_num;
    int king_col = black_arr[1][3]->col_num ;
   for(int j=-1;j<2;j++){
        int tmp_row = king_row+j;
        for(int i=-1; i<2;i++){
            int tmp_col = king_col+i;
            if (inside_board(tmp_col) && inside_board(tmp_row)) {
                if(!black_checkmate_xwrap(tmp_row,tmp_col)) return false;
            } else continue;
        }
    }
    return false;
    
}

bool white_stale(void){
    int king_row = white_arr[1][3]->row_num;
    int king_col = white_arr[1][3]->col_num ;

    if (!white_checkmate()) return false;

    for (int row=0; row<2; row++){
        for(int col=0;col<8;col++){
            if (white_arr[row][col]->eliminated) continue;
            int row_no = white_arr[row][col]->row_num;
            int col_no = white_arr[row][col]->col_num;
            if(white_arr[row][col]->name == 'P'){
                struct peice * tmp = white_arr[row][col];
                board[row_no][col_no] = NULL;
                bool temp_check =white_check(king_row, king_col);
                board[row_no][col_no] = tmp;
                if(temp_check) continue;

                if (!board[row_no+1][col_no]) {
                    return false;
                } else if (board[row_no+1][col_no+1]) {
                    if(board[row_no+1][col_no+1]->team == 'b') return false;
                }
            } else {
                struct peice * tmp = white_arr[row][col];
                board[row_no][col_no] = NULL;
                bool temp_check =white_check(king_row, king_col);
                board[row_no][col_no] = tmp;
                if(!temp_check) return false;
            }
        }
    }
    return true;
}

bool black_stale(void){
    int king_row = black_arr[1][3]->row_num;
    int king_col = black_arr[1][3]->col_num;

    if (!black_checkmate) return false;

    for (int row=0; row<2; row++){
        for(int col=0;col<8;col++){
            if (black_arr[row][col]->eliminated) continue;
            int row_no = black_arr[row][col]->row_num;
            int col_no = black_arr[row][col]->col_num;
            if(black_arr[row][col]->name == 'p'){
                struct peice * tmp = black_arr[row][col];
                board[row_no][col_no] = NULL;
                bool temp_check =black_check(king_row, king_col);
                board[row_no][col_no] = tmp;
                if(temp_check) continue;

                if (!board[row_no][col_no-1]) {
                    return false;
                } else if (board[row_no+1][col_no-1]) {
                    if(board[row_no+1][col_no-1]->team == 'w') return false;
                } else if (board[row_no-1][col_no-1]) {
                    if(board[row_no-1][col_no-1]->team == 'w') return false;
                }
            } else {
                struct peice * tmp = black_arr[row][col];
                board[row_no][col_no] = NULL;
                bool temp_check =black_check(king_row, king_col);
                board[row_no][col_no] = tmp;
                if(!temp_check) return false;
            }
        }
    }
    return true;
}

void black_player();

void white_player(){ 
    if(white_check(white_arr[1][3]->row_num, white_arr[1][3]->col_num )) {
       printf("Player White is on check\n");
       if(white_checkmate()) {
        printf("And that is checkmate..\nPlayer Black Wins!!\n");
        return;
       }
   }
   
    printf("White Player's Turn...\n");
    int init_col;
    int col;
    int old_row;
    int new_row;
    if (scanf(" %c%d %c%d", &init_col, &old_row, &col, &new_row) != 4) {
        printf("Invalid move entry, retry\n");
        clear_input();
        white_player();
        return;
    }
    init_col = toupper(init_col);
    col = toupper(col);

    int old_col = abs(init_col-72);
    int new_col = abs(col-72);
    old_row = old_row - 1;
    new_row = new_row -1;

    struct peice *old_peice = NULL;

   if (old_row > 7 || old_row < 0 || new_row > 7 || new_row < 0) {
        printf("Invalid move, Try Again\n");
        white_player();
        return;
    } 
    if (old_col > 7 || old_col < 0 || new_col > 7 || new_col < 0) {
        printf("Invalid move, Try Again\n");
        white_player();
        return;
    } 
    if (board[old_row][old_col] == NULL || board[old_row][old_col]->team == 'B' ) {
        printf("Invalid move, Try Again\n");
        white_player();
        return;
    } else {
        if(board[old_row][old_col]->name == 'P' && pawn_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else if (board[old_row][old_col]->name == 'B' && bishop_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else if (board[old_row][old_col]->name == 'R' && rook_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else if (board[old_row][old_col]->name == 'Q' && queen_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else if (board[old_row][old_col]->name == 'N' && knight_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else if (board[old_row][old_col]->name == 'K' && king_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else {
            printf("Invalid move, Try again.\n");
            white_player();
            return;
        }
    }

    if(white_check(white_arr[1][3]->row_num, white_arr[1][3]->col_num )) {
        printf("Invalid Move, You are on Check\n");
        revert_board(old_peice, old_row, old_col, new_row, new_col);
        white_player();
        return;
    }

    print_board();
    black_player();
}

void black_player(){
    if(black_check(black_arr[1][3]->row_num, black_arr[1][3]->col_num )) {
        printf("Player Black is on check\n");
        if(black_checkmate()) {
        printf("And that is checkmate..\nPlayer White Wins!!\n");
        return;
        }
   }
   
    printf("Black Player's Turn...\n");
    int init_col;
    int col;
    int old_row;
    int new_row;
    int scan = scanf(" %c%d %c%d", &init_col, &old_row, &col, &new_row);
    if (scan != 4) {
        printf("Invalid move entry, retry\n");
        clear_input();
        black_player();
        return;
    }
    init_col = toupper(init_col);
    col = toupper(col);

    int old_col = abs(init_col-72);
    int new_col = abs(col-72);
    old_row = old_row - 1;
    new_row = new_row -1;

    struct peice *old_peice = NULL;

   if (old_row > 7 || old_row < 0 || new_row > 7 || new_row < 0) {
        printf("Invalid move, Try Again\n");
        black_player();
        return;
    } 
    if (old_col > 7 || old_col < 0 || new_col > 7 || new_col < 0) {
        printf("Invalid move, Try Again\n");
        black_player();
        return;
    } 
    if (board[old_row][old_col] == NULL || board[old_row][old_col]->team == 'W' ) {
        printf("Invalid move, Try Again\n");
        black_player();
        return;
    } else {
        if(board[old_row][old_col]->name == 'p' && pawn_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else if (board[old_row][old_col]->name == 'b' && bishop_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else if (board[old_row][old_col]->name == 'r' && rook_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else if (board[old_row][old_col]->name == 'q' && queen_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else if (board[old_row][old_col]->name == 'n' && knight_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else if (board[old_row][old_col]->name == 'k' && king_move(old_row, old_col, new_row, new_col)) {
            old_peice = update_board(old_row, old_col, new_row, new_col);
        } else {
            printf("Invalid move, Try again.\n");
            black_player();
            return;
        }
    }

    if(black_check(black_arr[1][3]->row_num, black_arr[1][3]->col_num )) {
        printf("Invalid Move, You are on Check\n");
        revert_board(old_peice, old_row, old_col, new_row, new_col);
        black_player();
        return;
    }

    print_board();
    white_player();
}


 int main(){
    setlocale(LC_ALL, "");
    black_init();
    white_init();
    board_init();
    print_board();
    white_player();
    // printf("%c\n", board[1][1]->name);
 }