#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8
#define MINES 10

// Board states
#define COVERED -1
#define MINE -2

typedef struct
{
    int value; // -2 for mine, 0-8 for number of adjacent mines
    int state; // -1 for covered, 0 for uncovered
} Cell;

Cell board[SIZE][SIZE];

void initializeBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j].value = 0;
            board[i][j].state = COVERED;
        }
    }
}

void placeMines()
{
    srand(time(NULL));
    int minesPlaced = 0;
    while (minesPlaced < MINES)
    {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (board[x][y].value != MINE)
        {
            board[x][y].value = MINE;
            minesPlaced++;
        }
    }
}

void calculateNumbers()
{
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j].value == MINE)
                continue;
            int count = 0;
            for (int k = 0; k < 8; k++)
            {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE && board[ni][nj].value == MINE)
                {
                    count++;
                }
            }
            board[i][j].value = count;
        }
    }
}

void printBoard()
{
    printf("   ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d  ", i);
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j].state == COVERED)
            {
                printf(". ");
            }
            else if (board[i][j].value == MINE)
            {
                printf("* ");
            }
            else
            {
                printf("%d ", board[i][j].value);
            }
        }
        printf("\n");
    }
}

void reveal(int x, int y)
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[x][y].state == 0)
        return;
    board[x][y].state = 0;

    if (board[x][y].value == 0)
    {
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (int k = 0; k < 8; k++)
        {
            reveal(x + dx[k], y + dy[k]);
        }
    }
}

int main()
{
    initializeBoard();
    placeMines();
    calculateNumbers();

    int gameOver = 0;
    while (!gameOver)
    {
        printBoard();
        printf("Enter coordinates to reveal (row col): ");
        int x, y;
        scanf("%d %d", &x, &y);

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
        {
            printf("Invalid coordinates. Try again.\n");
            continue;
        }

        if (board[x][y].value == MINE)
        {
            printf("You hit a mine! Game over.\n");
            gameOver = 1;
            break;
        }

        reveal(x, y);

        // Check if the player has won
        int coveredCells = 0;
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j].state == COVERED)
                {
                    coveredCells++;
                }
            }
        }

        if (coveredCells == MINES)
        {
            printf("Congratulations! You've won.\n");
            gameOver = 1;
        }
    }

    // Reveal the entire board at the end
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j].state = 0;
        }
    }
    printBoard();

    return 0;
}
