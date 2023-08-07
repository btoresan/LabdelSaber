#include <raylib.h>

int menu()
{
    //valor que o menu retornara
    int saida = -1;
    
    
    // Declaração de texturas
    Texture2D fundo_menu;    
    
    InitWindow(800, 450, "menu");
    
    
    //Atribuição de Texturas
    fundo_menu = LoadTexture("static/fundo_menu.png"); 
    
    
    // Posições Y dos botões
    
    const int pos_y_nj = 100; //NOVO JOGO
    const int pos_y_cj = 170; // CARREGAR JOGO
    const int pos_y_eg = 240; // EXIBIR GANHADORES
    const int pos_y_inf = 310; // INFORMAÇÕES
    const int pos_y_sair = 380; // SAIR
    
    
    
    //Retangulo que está em cima do botao (representa a escolha)
    Rectangle Escolha;

    Escolha.x = 200;
    Escolha.y = 100; //Posição inicial do retangulo (em cima da primeira opção)
    Escolha.width = 398;
    Escolha.height = 49;    
    
    
    
    
    
    
    while (saida == -1)
    {                   
        //LOGICA
        
     
        
        //Posição do retangulo de escolha para KEY_DOWN
        if(IsKeyPressed(KEY_DOWN))
        {
            if(Escolha.y==380)
            {
                Escolha.y = 100;   
            }
            
            else
            {
                Escolha.y = Escolha.y +70;   
            }
        }
        
        //Posição do retangulo de escolha para KEY_UP
        else if(IsKeyPressed(KEY_UP))
        {
            if(Escolha.y==100)
            {
                Escolha.y = 380;  
            }
            
            else
            {
                Escolha.y = Escolha.y -70;   
            }
        }
        
        if(Escolha.y==pos_y_nj)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                saida =  0; //Se escolher NOVO JOGO, retorna 0
            }                          
        }
        
        else if (Escolha.y==pos_y_cj)
        {
            if (IsKeyPressed(KEY_ENTER))
                saida = 1; //Se escolher CARREGAR JOGO, retorna 1
        }
        
        
        else if (Escolha.y==pos_y_eg)
        {
            if (IsKeyPressed(KEY_ENTER))
                saida = 2; //Se escolher EXIBIR GANHADORES, retorna 2
        }
        
        else if (Escolha.y==pos_y_inf)
        {
            if (IsKeyPressed(KEY_ENTER))
                saida = 3; //Se escolher INFORMAÇÕES, retorna 3
        }
        
        else if (Escolha.y==pos_y_sair)
        {
            if (IsKeyPressed(KEY_ENTER))
                saida = 4; //Se escolher SAIR, retorna 4
        }

        //DESENHO
        
        BeginDrawing();
        
            DrawTexture(fundo_menu,0,0,WHITE);
            DrawText("Os Labirintos do INF", 150, 30, 50, BLACK);
            
            
                
            //Desenha o botão NOVO JOGO
            DrawRectangle(200, pos_y_nj, 398, 49, WHITE);
            DrawRectangleLines(200, pos_y_nj, 400, 50, BLACK);
            DrawText("NOVO JOGO", 320, 110, 30, BLACK);
                
            //Desenha o botão CARREGAR JOGO
            DrawRectangle(200, pos_y_cj, 398, 49, WHITE);
            DrawRectangleLines(200, pos_y_cj, 400, 50, BLACK);
            DrawText("CARREGAR JOGO", 280, 180, 30, BLACK);
            
            //Desenha o botão EXIBIR GANHADORES
            DrawRectangle(200, pos_y_eg, 398, 49, WHITE);
            DrawRectangleLines(200, pos_y_eg, 400, 50, BLACK);
            DrawText("EXIBIR GANHADORES", 250, 250, 30, BLACK);
            
            //Desenha o botão INFORMAÇÕES
            DrawRectangle(200, pos_y_inf, 398, 49, WHITE);
            DrawRectangleLines(200, pos_y_inf, 400, 50, BLACK);
            DrawText("INFORMAÇÕES", 300, 320, 30, BLACK);
            
            //Desenha o botão SAIR
            DrawRectangle(200, 380, 398, 49, WHITE);
            DrawRectangleLines(200, 380, 400, 50, BLACK);
            DrawText("SAIR", 360, 390, 30, BLACK);
            
            //Desenha o botão em cima da escolha
             DrawRectangleLinesEx(Escolha,3.4,RED);
               
        EndDrawing();
    }
    CloseWindow();

    return saida;
}