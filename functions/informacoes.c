

#include "raylib.h"

void informacoes()
{
    // Declaração de texturas
    Texture2D fundo_menu; 
    Texture2D tecla_cima; 
    Texture2D tecla_baixo; 
    Texture2D tecla_direita;
    Texture2D tecla_esquerda;
    
    InitWindow(800, 450, "Informações");
    
    //Atribuição de Texturas
    fundo_menu = LoadTexture("static/fundo_menu.png");
    tecla_cima = LoadTexture("static/tecla_cima.png");
    tecla_baixo = LoadTexture("static/tecla_baixo.png");
    tecla_direita = LoadTexture("static/tecla_direita.png");
    tecla_esquerda = LoadTexture("static/tecla_esquerda.png");
    
    while (!WindowShouldClose()&& !IsKeyPressed(KEY_R))    
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            DrawTexture(fundo_menu,0,0,WHITE);
            
            DrawTexture(tecla_cima,40,80,WHITE);
            DrawText("CIMA",120,90,35,BLACK);
            
            DrawTexture(tecla_baixo,40,160,WHITE);
            DrawText("BAIXO",120,170,35,BLACK);
            
            DrawTexture(tecla_direita,40,240,WHITE);
            DrawText("DIREITA",120,250,35,BLACK);
            
            DrawTexture(tecla_esquerda,40,320,WHITE);
            DrawText("ESQUERDA",120,330,35,BLACK);
            
            
            DrawText("PROXIMO NIVEL",400,90,35,BLACK);
            DrawRectangle(700,90 , 30, 30, BLUE);
            
            

            DrawText("Controles", 300, 20, 40, BLACK);
            DrawText("Aperte R para voltar", 20, 20, 20, RED);
            

        EndDrawing();
        
    }
    
    CloseWindow();    
    run();
}
