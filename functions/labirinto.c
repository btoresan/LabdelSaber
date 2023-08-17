#include <raylib.h>
#include <stdio.h>

typedef struct personagem{
    int posx;
    int posy;
    Texture2D current;
} personagem;






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
        for (int i = 0; i < 30; i++){
            for (int j = 0; j < 41; j++){
                if(fgetc(mapa) == '1'){
                    DrawRectangle(j*20, i*20, 20, 20, WHITE);
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






void moveplayer (char grid[41][30], personagem *aluno){

    if(IsKeyDown(KEY_W) && grid[aluno->posx][aluno->posy - 1] != '1'){
        grid[aluno->posy][aluno->posx] = '0';
        aluno->posy -= 1;
        grid[aluno->posx][aluno->posy] = 'p';
    }

    if(IsKeyDown(KEY_A) && grid[aluno->posx - 1][aluno->posy] != '1'){
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posx -= 1;
        grid[aluno->posx][aluno->posy] = 'p';
    }

    if(IsKeyDown(KEY_S) && grid[aluno->posx][aluno->posy + 1] != '1'){
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posy += 1;
        grid[aluno->posx][aluno->posy] = 'p';
    }

    if(IsKeyDown(KEY_D) && grid[aluno->posx + 1][aluno->posy] != '1'){
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posx += 1;
        grid[aluno->posx][aluno->posy] = 'p';
    }

}






 int loadgame(){
    //Declaracao do Tamanho da tela 
    const int screenWidth = 800;
    const int screenHeight = 600;

    //Declaracao da Grid 20x menor que o tamanho da tela por sessao
    //1 quadradoda grid = 20x20
    char grid[41][30] = {};

    //Declaracoes do mapa
    Texture2D mapa;
    FILE *mapaGrid;
    
    //Declaracoes do player
    personagem aluno;
    
    //Inicializa a janela 
    InitWindow(screenWidth, screenHeight, "Labirinto Del Saber ALPHA");
    
    
    //Inicializacao da textura do player
    aluno.posx = 1;
    aluno.posy = 1;
    aluno.current = LoadTexture("static/sprites/aluno_frente.png");
    
    
    //Inicializacao da do mapa
    mapa = LoadTexture("static/mapas/mapa1.png");
    mapaGrid = fopen("static/mapas/mapa1.txt", "r");
    
    
    //Inicializa cada coluna da grid com o mapa
    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 41; j++){
            fread(&grid[j][i], sizeof(char), 1, mapaGrid);      
        }
    }
    
    TraceLog(LOG_ERROR, "%s", grid);
    
    SetTargetFPS(10);
    
   //Cleanup
   fclose(mapaGrid);
    
    while (!WindowShouldClose()){
        //Inicializa a Tela
        BeginDrawing();

        //desenha o mapa
        DrawTexture(mapa, 0, 0, WHITE);

        //move o aluno
        moveplayer(grid, &aluno);
        
        //Desenha o player
        DrawTexture(aluno.current, aluno.posx*20, aluno.posy*20, WHITE);
        
        ClearBackground(BLACK);
        
        //Cleanup
        EndDrawing();
    }
    CloseWindow();
    return 0;
}