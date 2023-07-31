









#include <raylib.h>

int main()
{
    InitWindow(800, 600, "My Raylib Program");
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Wel come be", 10, 10, 20, BLACK);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
