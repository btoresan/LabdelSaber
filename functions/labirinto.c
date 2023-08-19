#include <raylib.h>
#include <stdio.h>
#include <math.h>


// Estrutura personagem
typedef struct personagem{
    int posx;
    int posy;
    Texture2D current;
    Texture2D frente;
    Texture2D tras;
    Texture2D direita;
    Texture2D esquerda;
} personagem;

// Estrutura professor
typedef struct {
    int posxp;
    int posyp;
    Texture2D currentp;
    Texture2D frentep;
    Texture2D trasp;
    Texture2D direitap;
    Texture2D esquerdap;
} PROFESSOR;






void drawGrid (char grid[41][30], Texture2D aluno, Texture2D professor){
    //para cada quadrado da grid
    for (int i = 0; i < 41; i++){
        for (int j = 0; j < 30; j++){
            
            //desenha o tipo do objeto no quadrado
            if (grid[i][j] == 'p')
                DrawTexture(aluno, i*20, j*20, WHITE);
            
            else if (grid[i][j] == 't')
                DrawTexture(professor, i*20, j*20, WHITE);
            
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


void moveprof (char grid[41][30], PROFESSOR *professor, int posxal, int posyal){
           
    int cont=0;
    int tem_parede = 0;
    
    // Calcula a distancia entre o professor e o aluno
    float distancia = sqrt(pow(posxal - professor->posxp, 2) + pow(posyal - professor->posyp, 2));
    
    
    // Perseguição professor
    
    if (distancia<=5) // Se o professor estiver próximo do aluno, inicia a perseguição
    {
        while (distancia!=0)
        {
            float dist_x = posxal - professor->posxp; // Calcula a distancia em relação ao x entre o aluno e o professor
            float dist_y = posyal - professor->posyp; // Calcula a distancia em relação ao y entre o aluno e o professor
            
            if (fabs(dist_x) >= fabs(dist_y)) // Se o valor absoluto da distancia em relação ao x for maior ou igual, o professor se move pelo eixo x
            {
                if (dist_x < 0) // Se a dist_x for negativa, o professor está à direita do aluno
                {
                    if(grid[professor->posxp-1][professor->posyp] != '1')
                    {
                        //Move o professor na grid           
                        grid[professor->posxp][professor->posyp] = '0';
                        professor->posxp -=1;
                        grid[professor->posxp][professor->posyp] = 't';
                        
                        //Atualiza o sprite do professor
                        professor->currentp = professor->esquerdap;
                    }    
                }
                
                else // Senão, o professor está à esquerda do aluno
                {
                    if(grid[professor->posxp+1][professor->posyp] != '1')
                    {
                        //Move o professor na grid           
                        grid[professor->posxp][professor->posyp] = '0';
                        professor->posxp +=1;
                        grid[professor->posxp][professor->posyp] = 't';
                        
                        //Atualiza o sprite do professor
                        professor->currentp = professor->direitap;
                    }  
                }  
            }
            
            else // Senão, o professor se move pelo eixo y
            {
                if (dist_y<0) // Se a dist_y for negativa, o professor está abaixo do aluno
                {
                    
                    if(grid[professor->posxp][professor->posyp - 1] != '1'){
            
                    //Move o professor na grid           
                    grid[professor->posxp][professor->posyp] = '0';
                    professor->posyp -=1;
                    grid[professor->posxp][professor->posyp] = 't';             
           
                    //Atualiza o sprite do professor
                    professor->currentp = professor->trasp;
                    }    
                }
                
                else  // Senão, etá acima do aluno
                {
                    if(grid[professor->posxp][professor->posyp + 1] != '1'){
            
                    //Move o professor na grid           
                    grid[professor->posxp][professor->posyp] = '0';
                    professor->posyp +=1;
                    grid[professor->posxp][professor->posyp] = 't';
            
                    //Atualiza o sprite do professor
                    professor->currentp = professor->frentep;
                    }   
                }    
            } 
            
            distancia = sqrt(pow(posxal - professor->posxp, 2) + pow(posyal - professor->posyp, 2));
        }  
    }
    
    
    // Movimentação aleatória do professor
    
    else
    {
        //Movimentação do professor de acordo com um valor aleatório de 0 a 3
    
        int random_direction = GetRandomValue(0,3); // 0 = tras; 1= frente; 2= direita; 3 = esquerda
    
        if (random_direction == 0) //tras
        {
        
            while (cont<1 && tem_parede ==0) //Movimenta 2 vezes se não encontrar nenhuma parede
            {
                if(grid[professor->posxp][professor->posyp - 1] != '1'){
            
                    //Move o professor na grid           
                    grid[professor->posxp][professor->posyp] = '0';
                    professor->posyp -=1;
                    grid[professor->posxp][professor->posyp] = 't';             
           
                    //Atualiza o sprite do professor
                    professor->currentp = professor->trasp;
                
                
                    if(grid[professor->posxp][professor->posyp - 1] == '1')
                        tem_parede=1; // flag parede
                    cont++;
                }
                else
                    tem_parede=1;
            
            }
        }
    
        else if (random_direction == 1) //frente
        {
        
            while (cont<1 && tem_parede ==0) 
            {
        
                if(grid[professor->posxp][professor->posyp + 1] != '1'){
            
                    //Move o professor na grid           
                    grid[professor->posxp][professor->posyp] = '0';
                    professor->posyp +=1;
                    grid[professor->posxp][professor->posyp] = 't';
            
                    //Atualiza o sprite do professor
                    professor->currentp = professor->frentep;
                
                    if(grid[professor->posxp][professor->posyp + 1] == '1')
                        tem_parede=1;
                    cont++;
                }
                else
                    tem_parede=1;
            }
        }
    
        else if (random_direction == 2) //direita
        {       
            while (cont<1 && tem_parede ==0) 
            {          
                if(grid[professor->posxp+1][professor->posyp] != '1'){
            
                    //Move o professor na grid           
                    grid[professor->posxp][professor->posyp] = '0';
                    professor->posxp +=1;
                    grid[professor->posxp][professor->posyp] = 't';
            
                    //Atualiza o sprite do professor
                    professor->currentp = professor->direitap;
                
                    if(grid[professor->posxp+1][professor->posyp] == '1')
                        tem_parede=1;
                    cont++;           
                }
            
                else
                    tem_parede=1;
            }
        }
    
        else if (random_direction == 3) //esquerda
        {
            while (cont<1 && tem_parede ==0) 
            {
        
                if(grid[professor->posxp-1][professor->posyp] != '1'){
            
                    //Move o professor na grid           
                    grid[professor->posxp][professor->posyp] = '0';
                    professor->posxp -=1;
                    grid[professor->posxp][professor->posyp] = 't';
            
                    //Atualiza o sprite do professor
                    professor->currentp = professor->esquerdap;
                
                    if(grid[professor->posxp-1][professor->posyp] == '1')
                        tem_parede=1;
                    cont++;            
                }
                else
                    tem_parede=1;
            }   

        }
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
    
    //Declaração professor
    PROFESSOR professor;
    
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
    
    
    //Inicializacao da textura e posição do professor
    
    professor.posxp = 10;
    professor.posyp = 10;
    professor.currentp = LoadTexture("static/sprites/professor-frente.png");
    
    professor.frentep = LoadTexture("static/sprites/professor-frente.png");
    professor.trasp = LoadTexture("static/sprites/professor-costas.png");
    professor.direitap = LoadTexture("static/sprites/professor-direita.png");
    professor.esquerdap = LoadTexture("static/sprites/professor-esquerda.png");
    
    
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
        
        //move o professor
        moveprof(grid, &professor, aluno.posx, aluno.posy);
        
        //Desenha o player e o profeesor
        drawGrid(grid, aluno.current,professor.currentp);
        
        
        ClearBackground(BLACK);
        
        //Cleanup
        EndDrawing();
    }
    CloseWindow();
    return 0;
}