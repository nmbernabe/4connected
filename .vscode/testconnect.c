#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

void initBoard(int **board, int *rowInd, int, int);
void printBoard(int **board, int, int);
int bestplay(int **board, int *rowInd, int **score, int, int);

int main(int argc, char *argv[]){
    int columns = 0;
    int rows = 0;
    
    
   
    while (columns < 4) {
        printf("How many columns on the board (at least 4):");
        scanf("%d", &columns);

    }
    while (rows < 4) {
        printf("How many rows on the board (at least 4):");
        scanf("%d", &rows); 
    }
    
    int **board = (int **)malloc((rows + 1) * sizeof(int *));
    for (int i = 0; i < (rows + 1); i++)
        board[i] = (int *)malloc((columns + 1) * sizeof(int));
    int rowInd[columns + 1];
    int **score = (int **)malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++)
        board[i] = (int *)malloc((columns + 1) * sizeof(int));
    initBoard(board, rowInd, rows, columns);

    printBoard(board, rows, columns);

    int best = bestplay(board, rowInd, score, rows, columns);
}

void initBoard(int **board, int *rowInd, int r, int c) {
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            board[i][j] = 0;
        }
    }

    for (int k = 1; k <= c; k++) {
        rowInd[k] = 1;
    }
}

void printBoard(int **board, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", board[i][j]);
        }
    }
}

int bestplay(int **board, int *rowInd, int **score, int r, int c) {
    int bestColumn;
    int found = 0;
    int player1 = 1;
    int payer2 = 2;

    //initialize scores to zero
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= c; j++) {
            score[i][j] = 0;
        }
    }
}