#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>

#define MAX 3

struct coordinates
{
    int x;
    int y;
};



int isInRange(struct coordinates coordinates)
{
    return (coordinates.x > 0 && coordinates.x < MAX) && (coordinates.y > 0 && coordinates.y < MAX);
}

void initializeArray(int array[])
{
    for(int i = 0; i < MAX*MAX; i++)
    {
        array[i] = i;
    }
}

int isInOrder(int board[MAX][MAX])
{
    int adder = 1;
    for(int i = 0; i < MAX; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            if(board[i][j] != adder)
            {
                return 0;
            }
            adder++;
            if (adder == 9)
            {
                return 1;
            }
        }
    }
    return 0;
}

struct coordinates findZero(int board[MAX][MAX])
{
    struct coordinates zero;
    for (int i = 0; i < MAX; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            if (board[i][j] == 0)
            {
                zero.x = j;
                zero.y = i;
                return zero;
            }
        }
    }
}

void swap(int board[MAX][MAX], struct coordinates *zero, int x, int y)
{
    struct coordinates position;
    position.x = x;
    position.y = y;
    if(isInRange(position))
    {
        int temp;
        temp = board[zero->x][zero->y];
        board[zero->x][zero->y] = board[x][y];
        board[x][y] = temp;
        zero->x = x;
        zero->y = y;
    }
}


int randomizeNumber(int array[], int *size)
{
    int index = rand() % (*size);
    int number = array[index];

    array[index] = array[(*size) - 1];
    (*size) = (*size) - 1;
    return number;
}

void initializeBoard(int board[MAX][MAX])
{
    int size = MAX*MAX;
    int array[MAX*MAX];

    initializeArray(array);
    for(int i = 0; i < MAX; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            board[i][j] = randomizeNumber(array, &size);
        }
    }
}

void printBoard(int board[MAX][MAX])
{
    for(int i=0; i < MAX; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            printf("%d", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void numberPuzzle(int board[MAX][MAX])
{   
    initializeBoard(board);
    printBoard(board);
    struct coordinates zero = findZero(board);

    initscr();
    keypad(stdscr, TRUE);
    timeout(0);

    int key;

    while (!isInOrder(board)) {
        key = getch();
        switch (key) {
            case KEY_UP:
                swap(board, &zero, zero.x, zero.y + 1);
                printBoard(board);
                printf("Seta para cima pressionada.\n");
                break;
            case KEY_DOWN:
                swap(board, &zero, zero.x, zero.y - 1);
                printBoard(board);
                printf("Seta para baixo pressionada.\n");
                break;
            case KEY_LEFT:
                swap(board, &zero, zero.x - 1, zero.y);
                printBoard(board);
                printf("Seta para esquerda pressionada.\n");
                break;
            case KEY_RIGHT:
                swap(board, &zero, zero.x + 1, zero.y + 1);
                printBoard(board);
                printf("Seta para direita pressionada.\n");
                break;
        }
    }

    endwin();

}





int main()
{
    srand(0);
    int board[MAX][MAX];
    numberPuzzle(board);

    return 0;
}