#include "raylib/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displint(int value, int x, int y, int fSize);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Minesweeper");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // SetWindowMinSize(screenWidth / 2, screenHeight / 2);
    // SetWindowMaxSize(screenWidth * 2, screenHeight * 2);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        displint(GetMouseX(), 0, 0, 20);
        displint(GetMouseY(), 0, 20, 20);

        // SetWindowSize(GetMouseX() + 200, GetMouseY() + 200);

        DrawRectangle(GetMouseX() + 10, GetMouseY() + 10, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();
    return 0;
}

void displint(int value, int x, int y, int fSize)
{
    char val_s[10] = {0};
    snprintf(val_s, 10, "%d", value);
    DrawText(val_s, x, y, fSize, LIGHTGRAY);
}