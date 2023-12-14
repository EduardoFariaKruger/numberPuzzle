#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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




int main()
{
    srand(0);
    int board[MAX][MAX];
    initializeBoard(board);
    printBoard(board);

    return 0;
}