#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void displayBoard(int size, char *valueTab);

void main(int argc, char **argv)
{
    // get size (4 - 16), quit option
    // get difficoulty (1 - 4), quit option
    // prepare mines table

    // gameplay in a loop:
    // get value

    char minesTab[64] = {0};
    char revealTab[64] = {0};
    for (int i = 0; i < 64; i++)
    {
        int randVal10 = (rand() * rand()) % 100;
        minesTab[i] = (randVal10 < 8) ? 'x' : ' ';
    }
    displayBoard(8, revealTab);

    int number;
    scanf("%d", &number);
}

void displayBoard(int size, char *valueTab)
{
    char firstRow[500] = "    ";
    char tableRow[500] = "   +";
    char tableVal[500] = " A |";

    int off = strlen(tableRow);
    // off += sprintf(tableEdge + off, "---+");

    for (int i = 0; i < size; i++)
    {
        sprintf(tableRow + strlen(tableRow), "---+");
        sprintf(firstRow + strlen(firstRow), " %c  ", 'A' + i);
        off += 4;
    }
    off = 0;
    printf("%s\n", firstRow);
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            sprintf(tableVal + strlen(tableVal), " %c |", valueTab[(j + 1) * (i + 1) - 1]);
            off += 4;
        }
        printf("%s\n", tableRow);
        printf("%s\n", tableVal);
        sprintf(tableVal, " %c |", 'B' + j);
        off = 0;
    }
    printf("%s\n", tableRow);

    // printf("%3d oC", 12);
}