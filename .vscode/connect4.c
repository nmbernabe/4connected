#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

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
    int turn, done = 0;
    int cont = 1;
   
    while (columns < 4) {
        printf("How many columns on the board (at least 4):");
        scanf("%d", &columns);

    }

    while (rows < 4) {
        printf("How many rows on the board (at least 4):");
        scanf("%d", &rows); 
    }

    const char *PIECES = "XO";
    char board[rows * columns];
    memset(board, ' ', rows * columns);

    while (cont == 1) {
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

        printf("Continue Playing?\n1. Yes\n2. No\n");
        scanf("%d", &cont);
    }

    return 0;
}
void printBoard(char *board, int r, int c){
   system("clear");
   puts("\n    ****Connect Four****\n");
   for(int row = 0; row < r; row++){
      for(int col = 0; col < c; col++){
         printf("| %c ",  board[c * row + col]);
      }
      puts("|");
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

}
int takeTurn(char *board, int player, int r, int c, const char *PIECES){
   int row, col = 0;
   printf("Player %d (%c):\nEnter number coordinate: ", player + 1, PIECES[player]);

   while(1){ 
      if(1 != scanf("%d", &col) || col < 1 || col > c ){
         while(getchar() != '\n');
         printf("Number out of bounds! Try again.");
      } else { 
         break;
      }
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
          if(checkFour(board, idx, idx + WIDTH, idx + WIDTH * 2, idx + WIDTH * 3)){
             return 1;
          }
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
          if(checkFour(board, idx, idx + HEIGHT, idx + HEIGHT * 2, idx + HEIGHT * 3)){
              return 1;
          }
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
         if(count <= 3 && checkFour(board, idx, idx + DIAG_LFT, idx + DIAG_LFT * 2, idx + DIAG_LFT * 3) || count >= 3 && checkFour(board, idx, idx + DIAG_RGT, idx + DIAG_RGT * 2, idx + DIAG_RGT * 3)){
            return 1;
         }
         count++;
      }
      count = 0;
   }
   return 0;

}
void clearScreen() {
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif // WIN32
}