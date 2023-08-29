#include <raylib.h>

int scoreboard(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Scoreboard");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        // TODO: Add any update code here
        
        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("1. Bernardo - 9999999 points", 10, screenHeight/2 - 50, 30, DARKGRAY);
        DrawText("2. Dante - 1 points", 10, screenHeight/2 - 20, 30, DARKGRAY);
        DrawText("3. Gabriel - 0 points", 10, screenHeight/2 + 10, 30, DARKGRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
