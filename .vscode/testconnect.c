#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

void initBoard(int **board, int, int);
void playVsPlay(int **board, int, int);
int colFree(int **board, int);
int playTurn(int **board, int, int, int, int *changed);
int removeTop(int **board, int, int, int *changed);
int isWin(int **board, int, int, int *changed);
int isFull(int **board, int, int);
int minMax(int **board, int, int, int *changed, int, int);
void printBoard(char **board, int , int);
void syncTables(int **board, char **b, int, int);
void printb(int **board, int, int);



int main(int argc, char *argv[]){
    int columns = 0;
    int rows = 0;
    int changed = 0;
    int player1 = 1;
    int player2 = 2;
    int choice = 0;
    
    
    
   
    while (columns < 4) {
        printf("How many columns on the board (at least 4):");
        scanf("%d", &columns);

    }
    while (rows < 4) {
        printf("How many rows on the board (at least 4):");
        scanf("%d", &rows); 
    }
    
    int **board = (int **)malloc(columns * sizeof(int *));
    for (int i = 0; i < columns; i++)
        board[i] = (int *)malloc(rows * sizeof(int));
    int **score = (int **)malloc(columns * sizeof(int *));
    for (int i = 0; i < columns; i++)
        score[i] = (int *)malloc(2 * sizeof(int));
    initBoard(board, columns, rows);

    while (choice != 3) {
        printf("Choose Game Mode:\n1. Player vs. Player\n2. Player vs. Computer\n3. Exit\n");
        scanf("%d", &choice);
        if (choice == 1)
            playVsPlay(board, rows, columns);
        //if (choice == 2)
            //playVsComp(board, rows, columns);
    }

    for (int i = 0; i < columns; i++) {
        if(!playTurn(board, player2, i, rows, &changed))
            continue;
        score[i][1] = minMax(board, columns, rows, &changed, 6, 0);
        removeTop(board, i, rows, &changed);
    }

    int maxScore = score[0][1];
    for (int k = 0; k < columns; k++) {
        if (maxScore < score[k][1])
            maxScore = score[k][1];
    }

     int index = 0;

    while(score[index][1] != maxScore) {
        index = (rand() % columns);
    }

    


    
}

void initBoard(int **board, int c, int r) {
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            board[i][j] = 0;
        }
    }
}

void playVsPlay(int **board, int rows, int columns){
    const char *PIECES = "XO";
    int cont = 1;
    int turn = 0;
    int done = 0;
    int player = 0;
    int changed = 0;
    
    char **b = (char **)malloc(columns * sizeof(char *));
    for (int i = 0; i < columns; i++)
        b[i] = (char *)malloc(rows * sizeof(char));

    while (cont == 1) {
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++)
                b[i][j] == ' ';
        }

        for(turn = 0; turn < rows * columns && !done; turn++){
            syncTables(board, b, columns, rows);
            printBoard(b, columns, rows);
            
                int col = 0;
                printf("Player %d (%c):\nEnter column number: ", (turn % 2) + 1, PIECES[player]);

                while(1){ 
                    if(1 != scanf("%d", &col) || col < 1 || col > columns ){
                        while(getchar() != '\n');
                        printf("Number out of bounds! Try again.");
                    } 
                    else 
                        break;
                }
                col--;
                if (!playTurn(board, ((turn % 2) + 1), col, rows, &changed)) {
                    syncTables(board, b, columns, rows);
                    printBoard(b, columns, rows);   
                    printf("**Column full!**\n");
                    continue;
                }
                printb(board, columns, rows);
            
            done = isWin(board, columns, rows, &changed);
            
        } 
        syncTables(board, b, columns, rows);
        printBoard(b, rows, columns);

        if(turn == rows * columns && !done)
            printf("It's a tie!\n");
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

void printb(int **board, int c, int r) {
    for(int col = 0; col < c; col++){
        for(int row = 0; row < r; row++){
            printf("%d ",  board[col][row]);
        }
        printf("\n");
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
    board[row - 1][column] = player;
    *changed = 1;
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
    *changed = 1;
    return 1; //return true
}

int isWin(int **board, int c, int r, int *changed) {
    if (*changed == 0) {
        return 0; //return false
    }

    *changed = 0;
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

int minMax(int **board, int c, int r, int *changed, int depth, int maxiPlayer) {
    if (depth <= 0)
        return 0;

    if (isWin(board, c, r, changed) == 2)
        return depth;
    if (isWin(board, c, r, changed) == 1)
        return -depth;
    if(isFull(board, c, r))
        return 0;
    

    int bestVal;
    if (maxiPlayer)
        bestVal = -1;
    else
        bestVal = 1;
    
    for (int i = 0; i < c; i++) {
        int player;
        if (maxiPlayer)
            player = 2;
        else
            player = 1;

        if(!playTurn(board, player, i, r, changed))
            continue;
        int v = minMax(board, c, r, changed, (depth - 1), !maxiPlayer);
        if (maxiPlayer) {
            if (bestVal <= v)
                bestVal = v;
        }
        else {
            if (v <= bestVal)
                bestVal = v;
        }
        removeTop(board, i, r, changed);
    }
    return bestVal;
}
void printBoard(char **b, int c, int r){
    system("clear");
    printf("\n    ****Connect Four****\n");

    for(int row = 0; row < r; row++){
        for(int col = 0; col < c; col++){
            printf("| %c ",  b[col][row]);
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

}

void syncTables(int **board, char **b, int c, int r) {
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            if(board[i][j] == 1)
                b[i][j] = 'X';
            else if (board[i][j] == 2) 
                b[i][j] = 'O';
            else
                b[i][j] = ' ';
        }
    }
}