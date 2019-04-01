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
void syncTables(int **board, char *b, int, int);
int playTurn(int **board, int, int, int, int *changed);
int minMax(int **board, int, int, int *changed, int, int);
int removeTop(int **board, int, int, int *changed);

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

    int changed;

    int **b = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++)
        b[i] = (int *)malloc(c * sizeof(int));
    int **score = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++){
        score[i] = (int *)malloc(2 * sizeof(int));
        score[i][2] = 0;
    }
        

    syncTables(b, board, c, r);

    for (int i = 0; i < c; i++) {
        if(!playTurn(b, 2, i, r, &changed))
            continue;
        score[i][1] = minMax(b, c, r, &changed, 6, 0);
        removeTop(b, i, r, &changed);
    }

    int maxScore = score[0][1];
    for (int k = 0; k < c; k++) {
        if (maxScore < score[k][1])
            maxScore = score[k][1];
    }

     int index = 0;

    while(score[index][1] != maxScore) {
        index = (rand() % c);
    }

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
   printf("next best move is %d\n", index);
   
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

int playTurn(int **board, int player, int column, int r, int *changed) {
    int row = 0;
    
    while (row < r && board[column][row] == 0) {
        row++;
    }
    if (row == 0)
        return 0; //return false
    board[row][column] = player;
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


void syncTables(int **board, char *b, int c, int r) {
    for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
            if(b[c * row + col] == 'X')
                board [row][col] = 1;
            else if (b[c * row + col] == 'O') 
                board [row][col] = 2;
            else
                board[row][col] = 0;
        }
    }
    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++){
           printf("%d ", board[i][j]);
       }
   }
   printf("\n");
}

int isWin(int **board, int c, int r, int *changed) {
    if (*changed == 0) {
        return 0; //return false
    }

    *changed = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (board[i][j] == 0)
                continue;
            
            int hor = 0;
            int vert = 0;

            if ((i + 3) < r)
                hor = 1;
            if ((j + 3) < c)
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
        if (board[0][i] != 0)
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

void clearScreen() {
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif // WIN32
}