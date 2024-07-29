#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 8
#define HEIGHT 8
#define NUM_MINES 10

char board[WIDTH][HEIGHT];
int mine_locations[NUM_MINES][2]; // x and y coordinates of mines

// Function to initialize the game by setting mines randomly
void init_game()
{
    int mines = 0;
    for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < HEIGHT; ++j)
        {
            board[i][j] = 'E'; // 'E' stands for empty
            board[i][i] = 'M'; // setting diagonals as mines
        }
    }

    for (int i = 0; i < NUM_MINES; ++i)
    {
        do
        {
            mine_locations[i][0] = rand() % WIDTH;
            mine_locations[i][1] = rand() % HEIGHT;
        } while (board[mine_locations[i][0]][mine_locations[i][1]] == 'M');
    }
}

// Function to reveal the cell and update the neighboring cells' states
void reveal(int x, int y)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    if (board[x][y] == 'M')
    {
        printf("You hit a mine! Game over!\n");
        exit(0);
    }

    board[x][y] = '.' + count_neighbors(x, y); // mark the cell with its number of neighbors

    for (int i = x - 1; i <= x + 1; ++i)
    {
        for (int j = y - 1; j <= y + 1; ++j)
        {
            if (i < 0 || i >= WIDTH || j < 0 || j >= HEIGHT)
                continue;
            reveal(i, j);
        }
    }
}

// Function to count the number of neighboring mines
int count_neighbors(int x, int y)
{
    int count = 0;
    for (int i = x - 1; i <= x + 1; ++i)
    {
        for (int j = y - 1; j <= y + 1; ++j)
        {
            if ((i != x || j != y) && board[i][j] == 'M')
                count++;
        }
    }
    return count;
}

int main()
{
    srand(time(NULL)); // seed the random number generator
    init_game();

    int reveal_x, reveal_y;
    printf("Welcome to Minesweeper!\n");
    while (true)
    {
        print_board();
        printf("Enter row and column to reveal: ");
        scanf("%d%d", &reveal_x, &reveal_y);
        if (reveal_x < 0 || reveal_x >= WIDTH || reveal_y < 0 || reveal_y >= HEIGHT)
            continue;
        reveal(reveal_x, reveal_y);
    }

    return 0;
}

// Function to print the game board
void print_board()
{
    for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < HEIGHT; ++j)
            printf("%c ", board[i][j]);
        printf("\n");
    }
}