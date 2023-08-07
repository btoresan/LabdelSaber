#include <raylib.h>

int scoreboard(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Congratulations, Gabriel!");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        // TODO: Add any update code here
        
        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congratulations, Gabriel!", 10, screenHeight/2 - 20, 30, DARKGRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
