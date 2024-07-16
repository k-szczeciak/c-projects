#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void displayBoard(int size, char *valueTab);

void main(int argc, char **argv)
{

    // int number;
    // printf("size = ");
    // scanf("%d", &number);
    // printf("\number = %d\n", number);

    // prepare "mine field"
    char valueTab[64] = {0};
    for (int i = 0; i < 64; i++)
    {
        int randVal10 = (rand() * rand()) % 100;
        valueTab[i] = (randVal10 < 8) ? 'x' : ' ';
    }
    displayBoard(8, valueTab);
}

void displayBoard(int size, char *valueTab)
{
    char firstRow[500] = "   ";
    char tableRow[500] = "  +";
    char tableVal[500] = "A |";

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
        sprintf(tableVal, "%c |", 'B' + j);
        off = 0;
    }
    printf("%s\n", tableRow);
}