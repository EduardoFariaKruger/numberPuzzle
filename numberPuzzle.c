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


/*
    funcao que verifica se uma coordenada esta contida na matriz M[MAX][MAX]
*/
int isInRange(struct coordinates coordinates)
{
    return (coordinates.x >= 0 && coordinates.x < MAX) && (coordinates.y >= 0 && coordinates.y < MAX);
}


/*
    funcao de inicializacao do vetor auxiliar
*/
void initializeArray(int array[])
{
    for(int i = 0; i < MAX*MAX; i++)
    {
        array[i] = i;
    }
}


/*
    checa se as 8 primeiras posicoes do tabuleiro estao em ordem de 1 a 8
*/
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


/*
    funcao que retorna as coordenadas do valor 0 na matriz
*/
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


/*
    funcao que faz a troca entre 2 posicoes da matriz. No caso do zero é garantido que ele estara dentro da matriz, porem o programa verifica se a coordenada (x, y)
    esta contida na matriz
*/
void swap(int board[MAX][MAX], struct coordinates *zero, int x, int y)
{
    struct coordinates position;
    position.x = x;
    position.y = y;

    if (isInRange(position))
    {
        int temp;
        temp = board[zero->y][zero->x];
        board[zero->y][zero->x] = board[y][x];
        board[y][x] = temp;
        zero->x = x;
        zero->y = y;
    }
}

/*
    funcao que retorna um numero e o remove do vetor
*/
int randomizeNumber(int array[], int *size)
{
    int index = rand() % (*size);
    int number = array[index];

    array[index] = array[(*size) - 1];
    (*size) = (*size) - 1;
    return number;
}


/*
    essa funcao usa de um vetor auxiliar para distribuir numeros entre 0 e 8 (sem multiplicidade) em posicoes aleatorias da matriz
*/
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
    clear(); //limpa o terminal (ncurses)
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printw("%d ", board[i][j]);
        }
        printw("\n");
    }
    refresh(); //atualiza a tela (ncurses)
}

void numberPuzzle(int board[MAX][MAX])
{   
    initializeBoard(board); //inicializa o tabuleiro com os numeros em posicoes aleatorias
    struct coordinates zero = findZero(board); //coordenada inicial da casa desocupada (ou casa 0)


    /*
        inicia o ncurses
    */
    initscr();
    keypad(stdscr, TRUE);
    timeout(0);

    printBoard(board); //faz a impressao inicial do tabuleiro para o jogador comecar

    int key; //variável que vai guardar o ASCII da tacla pressionada

    /*
        laco principal do jogo. Enquanto o tabuleiro nao estiver organizado corretamente o programa ainda vai aceitar inputs
    */
    while (!isInOrder(board))
    {
        key = getch(); //aguarda um input do usuario

        switch (key) //switch que controla o que acontece dependendo da tecla pressionada
        {
            case KEY_DOWN:
                swap(board, &zero, zero.x, zero.y - 1);
                printBoard(board);
                printw("Seta para cima pressionada.\n");
                break;
            case KEY_UP:
                swap(board, &zero, zero.x, zero.y + 1);
                printBoard(board);
                printw("Seta para baixo pressionada.\n");
                break;
            case KEY_RIGHT:
                swap(board, &zero, zero.x - 1, zero.y);
                printBoard(board);
                printw("Seta para esquerda pressionada.\n");
                break;
            case KEY_LEFT:
                swap(board, &zero, zero.x + 1, zero.y);
                printBoard(board);
                printw("Seta para direita pressionada.\n");
                break;
            case 27: //caso o usuario aperte a tecla esc o programa encerra
                printBoard(board);
                printw("Não foi dessa vez :(");
                endwin();
                exit(0);
        }
    }
    endwin(); //encerra o ncurses
}


int main()
{
    srand(0);
    int board[MAX][MAX];
    numberPuzzle(board);
    return 0;
}