#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

char** createEmptyMatrix(int X, int Y) {
    char** matrix = (char**)malloc(Y * sizeof(char*));
    for (int i = 0; i < Y; i++) {
        matrix[i] = (char*)malloc(X * sizeof(char));
        for (int j = 0; j < X; j++) {
            matrix[i][j] = '=';
        }
    }
    return matrix;
}

char** createMatrix(int X, int Y, int apX, int apY, int plX, int plY) {
    char** matrix = (char**)malloc(Y * sizeof(char*));
    for (int i = 0; i < Y; i++) {
        matrix[i] = (char*)malloc(X * sizeof(char));
        for (int j = 0; j < X; j++) {
            matrix[i][j] = '=';
        }
    }
    matrix[apY-1][apX-1] = '@';
    matrix[plY-1][plX-1] = '&';
    return matrix;
}

void printMatrix(char** matrix, int X, int Y, int points) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            printf("%c", matrix[i][j]);
            refresh();
        }
        printf("\n\r");
        refresh();
    }
    printf("%s", "Points: ");
    printf("%d", points);
    printf("\r\n");
    refresh();
}

int genAppleX(int plX, int X) {
    int appleX;
    do {
        appleX = rand()%(X+1);
    } while (appleX == plX);
    return appleX;
}
int genAppleY(int plY, int Y, int appleX, int X) {
    int appleY;
    do {
        appleY = rand()%(Y+1);
    } while (appleY == plY || (appleX == (X - 1) && appleY == 2));
    return appleY;
}

int main() {
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    int X = 30;
    int Y = 7;

    int playerX = (X+1)/2;
    int playerY = (Y+1)/2;

    int appleX = genAppleX(playerX, X);
    int appleY = genAppleY(playerY, Y, appleX, X);

    int points = 0;
    char keycode;

    char** matrix = createMatrix(X, Y, appleX, appleY, playerX, playerY);
    printMatrix(matrix, X, Y, points);

    while(1){
        keycode = getch();
        switch (keycode) {
            case 'w': //up
                if(playerY > 1) playerY -= 1;
                break;
            case 's': //down
                if(playerY < Y) playerY += 1;
                break;
            case 'a': //left
                if(playerX > 1) playerX -= 1;
                break;
            case 'd': //right
                if(playerX < X) playerX += 1;
                break;
            case 'q': //exit
                endwin();
                return 0;
            default:
                break;
        }

        if((playerX == appleX) && (playerY == appleY)) {
            appleX = genAppleX(playerX, X);
            appleY = genAppleY(playerY, Y, appleX, X);
            points += 1;
        }

        printf("\033[2J\033[H");
        matrix = createMatrix(X, Y, appleX, appleY, playerX, playerY);
        printMatrix(matrix, X, Y, points);
    }

    endwin();
    return 0;
}
