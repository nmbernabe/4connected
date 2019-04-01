#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

void playVsPlay(char *board, int, int);
void playVsComp(char *board, int, int);
void printBoard(char *board, int , int);
int takeTurn(char *board, int player, int, int, const char*);
int checkWin(char *board, int, int);
int checkFour(char *board, int, int, int, int);
int horizontalCheck(char *board, int, int);
int verticalCheck(char *board, int, int);
int diagonalCheck(char *board, int, int);

int main(int argc, char *argv[]){
    int columns = 0;
    int rows = 0;
    int choice = 0;
    
   
    while (columns < 4) {
        printf("How many columns on the board (at least 4):");
        scanf("%d", &columns);

    }
    while (rows < 4) {
        printf("How many rows on the board (at least 4):");
        scanf("%d", &rows); 
    }

    char board[rows * columns];

    while (choice != 3) {
        printf("Choose Game Mode:\n1. Player vs. Player\n2. Player vs. Computer\n3. Exit\n");
        scanf("%d", &choice);
        if (choice == 1)
            playVsPlay(board, rows, columns);
        if (choice == 2)
            playVsComp(board, rows, columns);
    }
    return 0;

}

void playVsPlay(char *board, int rows, int columns){
    const char *PIECES = "XO";
    int cont = 1;
    int turn = 0;
    int done = 0;
    
    while (cont == 1) {
        memset(board, ' ', rows * columns);

        for(turn = 0; turn < rows * columns && !done; turn++){
            printBoard(board, rows, columns);   
            while(!takeTurn(board, turn % 2, rows, columns, PIECES)){
                printBoard(board, rows, columns);   
                printf("**Column full!**\n");
            }
            done = checkWin(board, rows, columns);
        } 
        printBoard(board, rows, columns);

        if(turn == rows * columns && !done)
            printf("It's a tie!");
        else {
            turn--;
            printf("Player %d (%c) wins!\n", turn % 2 + 1, PIECES[turn % 2]);
        }

        printf("Continue Playing Player vs. Player mode?\n1. Yes\n2. No\n");
        scanf("%d", &cont);
        turn = 0;
        done = 0;
    }
}

void playVsComp(char *board, int rows, int columns) {
    const char *PIECES = "XO";
    int cont = 1;
    int turn = 0;
    int done = 0;
    
    while (cont == 1) {
        memset(board, ' ', rows * columns);

        for(turn = 0; turn < rows * columns && !done; turn++){
            printBoard(board, rows, columns);
            if (turn%2 == 1) {
                int col = 1;
                for(int r = rows - 1; r >= 0; r--){
                    if(board[columns * r + col] == ' ')
                    board[columns * r + col] = 'O';
                }
            }   
            while(!takeTurn(board, turn % 2, rows, columns, PIECES)){
                printBoard(board, rows, columns);   
                printf("**Column full!**\n");
            }
            done = checkWin(board, rows, columns);
        } 
        printBoard(board, rows, columns);

        if(turn == rows * columns && !done)
            printf("It's a tie!");
        else {
            turn--;
            printf("Player %d (%c) wins!\n", turn % 2 + 1, PIECES[turn % 2]);
        }

        printf("Continue Playing Player vs. Player mode?\n1. Yes\n2. No\n");
        scanf("%d", &cont);
        turn = 0;
        done = 0;
    }
}

void printBoard(char *board, int r, int c){
    system("clear");
    printf("\n    ****Connect Four****\n");

    for(int row = 0; row < r; row++){
        for(int col = 0; col < c; col++){
            printf("| %c ",  board[c * row + col]);
        }
        printf("|\n");
        printf("-");
        for (int i = 0; i < c; i++) {
            printf("----");
        }
        printf("\n");
    }

    printf("  1");
    for (int i = 1; i < c; i++) {
        if (i >= 9)
            printf("  %d", i+1);
        else
            printf("   %d", i+1);
   }
   printf("\n");

   for(int index = 0; index < r * c; index++){
        printf("%c ", board[index]);
   }
}

int takeTurn(char *board, int player, int r, int c, const char *PIECES){
    int row, col = 0;
    printf("Player %d (%c):\nEnter column number: ", player + 1, PIECES[player]);

    while(1){ 
        if(1 != scanf("%d", &col) || col < 1 || col > c ){
            while(getchar() != '\n');
                printf("Number out of bounds! Try again.");
        } 
        else 
            break;
    }
    col--;

    for(row = r - 1; row >= 0; row--){
        if(board[c * row + col] == ' '){
            board[c * row + col] = PIECES[player];
            return 1;
        }
    }

    return 0;

}

int checkWin(char *board, int r, int c){
    return (horizontalCheck(board, r, c) || verticalCheck(board, r ,c) || diagonalCheck(board, r, c));

}

int checkFour(char *board, int a, int b, int c, int d){
    return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != ' ');

}

int horizontalCheck(char *board, int r, int c){
    int row, col, idx;
    const int WIDTH = 1;

    for(row = 0; row < r; row++){
        for(col = 0; col < c - 3; col++){
            idx = c * row + col;
            if(checkFour(board, idx, idx + WIDTH, idx + WIDTH * 2, idx + WIDTH * 3))
                return 1;
        }
    }
    return 0;

}

int verticalCheck(char *board, int r, int c){
    int row, col, idx;
    const int HEIGHT = c;

    for(row = 0; row < r - 3; row++){
        for(col = 0; col < c; col++){
            idx = c * row + col;
            if(checkFour(board, idx, idx + HEIGHT, idx + HEIGHT * 2, idx + HEIGHT * 3))
                return 1;
        }
    }
    return 0;

}

int diagonalCheck(char *board, int r, int c){
   int row, col, idx, count = 0;
   const int DIAG_RGT = (c - 1), DIAG_LFT = (c + 1);

    for(row = 0; row < r - 3; row++){
        for(col = 0; col < c; col++){
            idx = c * row + col;
            if(count <= 3 && checkFour(board, idx, idx + DIAG_LFT, idx + DIAG_LFT * 2, idx + DIAG_LFT * 3) || count >= 3 && checkFour(board, idx, idx + DIAG_RGT, idx + DIAG_RGT * 2, idx + DIAG_RGT * 3))
                return 1;
            count++;
        }
        count = 0;
    }
   return 0;

}

void syncTables(int **board, char **b, int c, int r) {
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            if(b[i][j] = 'X')
                board [i][j] = 1;
            else if (b[i][j] = 'O') 
                board [i][j] = 2;
            else
                board[i][j] = 0;
        }
    }
}

void clearScreen() {
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif // WIN32
}