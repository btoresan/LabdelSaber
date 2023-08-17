#include <raylib.h>
#include <stdio.h>

typedef struct personagem{
    int posx;
    int posy;
    Texture2D current;
    Texture2D frente;
    Texture2D tras;
    Texture2D direita;
    Texture2D esquerda;
} personagem;




void drawGrid (char grid[41][30], Texture2D aluno){
    //para cada quadrado da grid
    for (int i = 0; i < 41; i++){
        for (int j = 0; j < 30; j++){
            
            //desenha o tipo do objeto no quadrado
            if (grid[i][j] == 'p')
                DrawTexture(aluno, i*20, j*20, WHITE);
            
            else if (grid[i][j] == '1')
                DrawRectangle(20*i, 20*j, 20, 20, WHITE);
            else
                DrawRectangle(20*i, 20*j, 20, 20, BLACK);
        }
    }
}





void moveplayer (char grid[41][30], personagem *aluno){

    if(IsKeyDown(KEY_W) && grid[aluno->posx][aluno->posy - 1] != '1'){
        
        //Move o aluno na grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posy -= 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //atualiza o sprite 
        aluno->current = aluno->tras;
    }

    if(IsKeyDown(KEY_A) && grid[aluno->posx - 1][aluno->posy] != '1'){
        
        //Move o aluno na grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posx -= 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //atualiza o sprite
        aluno->current = aluno->esquerda;
    }

    if(IsKeyDown(KEY_S) && grid[aluno->posx][aluno->posy + 1] != '1'){
        
        //Move o Aluno na Grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posy += 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //Atualiza o sprite
        aluno->current = aluno->frente;
    }

    if(IsKeyDown(KEY_D) && grid[aluno->posx + 1][aluno->posy] != '1'){
        
        //Move o Aluno na Grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posx += 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //Atualiza o sprite
        aluno->current = aluno->direita;
    }

}





 int loadgame(char *caminhoMapa){
    //Declaracao do Tamanho da tela 
    const int screenWidth = 800;
    const int screenHeight = 600;

    //Declaracao da Grid 20x menor que o tamanho da tela por sessao
    //1 quadradoda grid = 20x20
    char grid[41][30] = {};

    //Declaracoes do mapa
    FILE *mapaGrid;
    
    //Declaracoes do player
    personagem aluno;
    
    //Inicializa a janela 
    InitWindow(screenWidth, screenHeight, "Labirinto Del Saber ALPHA");
    
    
    //Inicializacao da textura do player
    aluno.posx = 1;
    aluno.posy = 1;
    aluno.current = LoadTexture("static/sprites/aluno_frente.png");
    
    aluno.frente = LoadTexture("static/sprites/aluno_frente.png");
    aluno.tras = LoadTexture("static/sprites/aluno_tras.png");
    aluno.esquerda = LoadTexture("static/sprites/aluno_esquerda.png");
    aluno.direita = LoadTexture("static/sprites/aluno_direita.png");
    
    
    //Inicializacao da do mapa
    mapaGrid = fopen(caminhoMapa, "r");
    
    
    //Inicializa cada coluna da grid com o mapa
    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 41; j++){
            fread(&grid[j][i], sizeof(char), 1, mapaGrid);      
        }
    }
    
    SetTargetFPS(10);
    
   //Cleanup
   fclose(mapaGrid);
    
    while (!WindowShouldClose()){
        //Inicializa a Tela
        BeginDrawing();

        //move o aluno
        moveplayer(grid, &aluno);
        
        //Desenha o player
        drawGrid(grid, aluno.current);
        //DrawTexture(aluno.current, aluno.posx*20, aluno.posy*20, WHITE);
        
        ClearBackground(BLACK);
        
        //Cleanup
        EndDrawing();
    }
    CloseWindow();
    return 0;
}