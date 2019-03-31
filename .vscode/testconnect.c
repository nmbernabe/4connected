#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

void initBoard(int **board, int *rowInd, int, int);
void printBoard(int **board, int, int);
int colFree(int **board, int);

int main(int argc, char *argv[]){
    int columns = 0;
    int rows = 0;
    int changed = 0;
    
    
   
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
    initBoard(board, rowInd, columns, rows);

    printBoard(board, rows, columns);

    
}

void initBoard(int **board, int *rowInd, int c, int r) {
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            board[i][j] = 0;
        }
    }

    for (int k = 1; k <= c; k++) {
        rowInd[k] = 1;
    }
}

void printBoard(int **board, int c, int r) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", board[i][j]);
        }
    }
}

int colFree(int **board, int column) {
    if (board[column][0] == 0)
        return 1; //column is free return true
    else
        return 0; //column is occupied return false
    
}

int playTurn(int **board, int player, int column, int r, int *changed) {
    int row = 0;
    while (row < r && board[column][row] == 0) {
        row++;
    }
    if (row == 0)
        return 0; //return false
    board[column][row] = player;
    changed = 1;
    return 1; //return true
}

int removeTop(int **board, int column, int r, int *changed) {
    int row = 0;
    while (row < r && board[column][row] == 0) {
        row++;
    }
    if (row == r) 
        return 0; //return false
    board[column][row] == 0;
    changed = 1;
    return 1; //return true
}

int isWin(int **board, int c, int r, int *changed) {
    if (changed == 0) {
        return 0; //return false
    }

    changed == 0;
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            if (board[i][j] == 0)
                continue;
            
            int hor = 0;
            int vert = 0;

            if ((i + 3) < c)
                hor = 1;
            if ((j + 3) < r)
                vert = 1;

            if (!(hor) && !(vert)) //checks vertical and horizontal
                continue;

            int forDiag = 0;
            int backDiag = 0;

            if (hor && vert)
                forDiag = 1;
            if (vert && ((i - 3) >= 0))
                backDiag = 0;

            for (int k = 1; k < 4; k++) { //cheacks diagonals
                if (hor && board[i][j] == board[i + k][j]) 
                    hor = 1;
                else
                    hor = 0;
                if (vert && board[i][j] == board[i][j + k]) 
                    vert = 1;
                else
                    vert = 0;
                if (forDiag && board[i][j] == board[i + k][j + k])
                    forDiag = 1;
                else 
                    forDiag = 0;
                if (backDiag && board[i][j] == board[i - k][j + k])
                    backDiag = 1;
                else 
                    backDiag = 0;
                if (!hor && !vert && !forDiag && !backDiag)
                    break;
            }
            if (hor || vert || forDiag || backDiag) {
                return board[i][j];
            }
        }
    }
    return 0;
}

int isFull(int **board, int c, int r) {
    for (int i = 0; i < c; i++) {
        if (board[i][0] != 0)
            return 0;
    }
    return 1;
}