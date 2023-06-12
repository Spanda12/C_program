#include <stdio.h>

char board[3][3]; // 3x3 board

void initializeBoard() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    int i;
    printf("\n---+---+---\n");
    for (i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        printf("---+---+---\n");
    }
}

int checkWin() {
    int i;

    // Check rows
    for (i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == 'X') return 1;
            else if (board[i][0] == 'O') return 2;
        }
    }

    // Check columns
    for (i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == 'X') return 1;
            else if (board[0][i] == 'O') return 2;
        }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        if (board[1][1] == 'X') return 1;
        else if (board[1][1] == 'O') return 2;
    }

    return 0; // No winner
}

int makeMove(int player, int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
        return 0; // Invalid move
    }

    if (player == 1) {
        board[row][col] = 'X';
    } else {
        board[row][col] = 'O';
    }

    return 1; // Valid move
}

int main() {
    int currentPlayer = 1; // Player 1 starts
    int row, col;
    int winner = 0;

    initializeBoard();

    printf("Tik Tak Toe Game\n");

    do {
        displayBoard();

        printf("Player %d, enter your move (row column): ", currentPlayer);
        scanf("%d %d", &row, &col);

        if (makeMove(currentPlayer, row, col)) {
            winner = checkWin();

            if (winner != 0) {
                displayBoard();
                printf("Player %d wins!\n", currentPlayer);
            } else {
                // Switch player
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        } else {
            printf("Invalid move. Try again.\n");
        }
    } while (winner == 0);

    return 0;
}
