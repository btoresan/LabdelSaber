#include <raylib.h>
#include "functions/menu.h" //puxa as funções dos arquivos menu

int run(){

    InitWindow(800, 600, "Labirento Del Saber"); //Inicializa a Tela

    //variaveis para a mensagem de erro
    int Xmeio = GetScreenWidth() / 2 - MeasureText("SORRY THERE WAS AN ERROR", 40) / 2;
    int Ymeio = GetScreenHeight() / 2 - 40 / 2;
    
    SetTargetFPS(60); //define o jogo rodando em 60 FPS

    while (!WindowShouldClose())
    {
        if (menu()){ //Se o menu devolver um erro carrega uma tela de erro
            BeginDrawing();
            ClearBackground(RED);

            DrawText("SORRY THERE WAS AN ERROR", Xmeio, Ymeio, 40, WHITE);
            
            EndDrawing();
        }

    }
    
    CloseWindow(); //encerra o programa

    return 0;
}


int main()
{
    run();
    
    return 0;
}
