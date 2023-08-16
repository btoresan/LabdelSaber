#include <raylib.h>
#include <stdio.h>

void drawmap (){
     // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    FILE *mapa;
    
    mapa = fopen("../static/mapas/mapa1.txt", "r");
    
    //int grid [80][60] = {};
    
    InitWindow(screenWidth, screenHeight, "Image Display Example");
    
    SetTargetFPS(20);
    
    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        for (int i = 0; i < 60; i++){
            for (int j = 0; j < 81; j++){
                if(fgetc(mapa) == '1'){
                    DrawRectangle(j*10, i*10, 8, 8, WHITE);
                }
            }
        }
        rewind(mapa);
        
        ClearBackground(BLACK);
        
        EndDrawing();
    }
    // Cleanup
    CloseWindow();
}

void moveplayer (char grid[40][30], int *posx, int *posy){

    if(IsKeyDown(KEY_W)){
        grid[*posx][*posy] = 'o';
        *posy -= 1;
        grid[*posx][*posy] = 'p';
    }

    if(IsKeyDown(KEY_A)){
        grid[*posx][*posy] = 'o';
        *posx -= 1;
        grid[*posx][*posy] = 'p';
    }

    if(IsKeyDown(KEY_S)){
        grid[*posx][*posy] = 'o';
        *posy += 1;
        grid[*posx][*posy] = 'p';
    }

    if(IsKeyDown(KEY_D)){
        grid[*posx][*posy] = 'o';
        *posx += 1;
        grid[*posx][*posy] = 'p';
    }

}

 int loadgame(){
    //Declaracao do Tamanho da tela 
    const int screenWidth = 800;
    const int screenHeight = 600;

    //Declaracao da Grid 20x menor que o tamanho da tela por sessao
    char grid[40][30] = {};
    //1 quadradoda grid = 20x20

    //Declaracoes do mapa
    Texture2D mapa;
    
    //Declaracoes do player
    int posx = 1;
    int posy = 1;
    Texture2D player;
    
    //Inicializa a janela 
    InitWindow(screenWidth, screenHeight, "Labirinto Del Saber ALPHA");
    
    
    //Inicializacao da textura do player
    player = LoadTexture("../static/sprites/aluno_frente.png");
    //Inicializacao da textura do mapa
    mapa = LoadTexture("../static/mapas/mapa1.png");
    

    SetTargetFPS(20);
    
   
    
    while (!WindowShouldClose()){
        //Inicializa a Tela
        BeginDrawing();

        //desenha o mapa
        DrawTexture(mapa, 0, 0, WHITE);

        moveplayer(grid, &posx, &posy);
        
        //Desenha o player
        DrawTexture(player, posx*20, posy*20, WHITE);
        
        ClearBackground(BLACK);
        
        //Cleanup
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

int main (){
    loadgame();
    return 0;
}