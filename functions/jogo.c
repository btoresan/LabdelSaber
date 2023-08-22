#include "labirinto.c"
#include <raylib.h>


int perguntas (){
    
    //Inicializacao da saida
    InitWindow(800, 600, "Labirinto Del Saber ALPHA");
    
    while (!WindowShouldClose() && !IsKeyPressed(KEY_Q)){
        BeginDrawing();
        
        DrawText("INSIRA AS PERGUNTAS AQUI, APERTE Q PARA VOLTAR", 0, 300, 20, BLUE);
        
        EndDrawing();
    }
    
    //Cleanup
    CloseWindow();
    
    //Volta para o Labirinto
    labirinto();
    
    return 0;
}




int labirinto (){
    //Declaracao que salva o valor retornado de loadgame
    int saida;
    
    //Roda o jogo e salva a saida 
    saida = loadgame("static/mapas/mapa1.txt", 1, 1, 1, 30);
    
    //Carrega a tela apropriada dependendo da saida
    switch (saida)
    {
        case 99:
            perguntas();
            break;
    }
    
    
    return 0;
}




int jogo (){
    labirinto();
    
    return 0;
}