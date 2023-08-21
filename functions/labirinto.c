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





void drawGrid (char grid[101][100], personagem *aluno, Texture2D professor){
    int metade = 0;
    
    if (aluno->posx > 50)
        metade = 30;
    
    //para cada quadrado da grid
    for (int i = metade; i < metade + 70; i++){
        for (int j = 0; j < 100; j++){
            //desenha o tipo do objeto no quadrado
            if (grid[i][j] == 'p')
                DrawTexture(aluno->current, i*20, j*20, WHITE);
            
            else if (grid[i][j] == 't')
                DrawTexture(professor, i*20, j*20, WHITE);
            
            else if (grid[i][j] == '1')
                DrawRectangle(20*i, 20*j, 20, 20, WHITE);
            else
                DrawRectangle(20*i, 20*j, 20, 20, BLACK);
        }
    }
}





void moveplayer (char grid[101][100], personagem *aluno){

    if(IsKeyDown(KEY_UP) && grid[aluno->posx][aluno->posy - 1] != '1'){
        
        //Move o aluno na grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posy -= 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //atualiza o sprite 
        aluno->current = aluno->tras;
    }

    if(IsKeyDown(KEY_LEFT) && grid[aluno->posx - 1][aluno->posy] != '1'){
        
        //Move o aluno na grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posx -= 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //atualiza o sprite
        aluno->current = aluno->esquerda;
    }

    if(IsKeyDown(KEY_DOWN) && grid[aluno->posx][aluno->posy + 1] != '1'){
        
        //Move o Aluno na Grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posy += 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //Atualiza o sprite
        aluno->current = aluno->frente;
    }

    if(IsKeyDown(KEY_RIGHT) && grid[aluno->posx + 1][aluno->posy] != '1'){
        
        //Move o Aluno na Grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posx += 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //Atualiza o sprite
        aluno->current = aluno->direita;
    }

}





void moveprof (char grid[101][100], personagem *professor, int posxal, int posyal){
           
    int cont=0;
    int tem_parede = 0;
    
    // Calcula a distancia entre o professor e o aluno
    float distancia = sqrt(pow(posxal - professor->posx, 2) + pow(posyal - professor->posy, 2));
    
    
    // Perseguição professor
    
    if (distancia<=8) // Se o professor estiver próximo do aluno, inicia a perseguição
    {
        float dist_x = posxal - professor->posx; // Calcula a distancia em relação ao x entre o aluno e o professor
        float dist_y = posyal - professor->posy; // Calcula a distancia em relação ao y entre o aluno e o professor
            
        if (fabs(dist_x) >= fabs(dist_y)) // Se o valor absoluto da distancia em relação ao x for maior ou igual, o professor se move pelo eixo x
        {
            if (dist_x < 0) // Se a dist_x for negativa, o professor está à direita do aluno
            {
                if(grid[professor->posx-1][professor->posy] != '1')
                {
                    //Move o professor na grid           
                    grid[professor->posx][professor->posy] = '0';
                    professor->posx -=1;
                    grid[professor->posx][professor->posy] = 't';
                        
                    //Atualiza o sprite do professor
                    professor->current = professor->esquerda;
                }    
            }
                
            else // Senão, o professor está à esquerda do aluno
            {
                if(grid[professor->posx+1][professor->posy] != '1')
                {
                    //Move o professor na grid           
                    grid[professor->posx][professor->posy] = '0';
                    professor->posx +=1;
                    grid[professor->posx][professor->posy] = 't';
                        
                    //Atualiza o sprite do professor
                    professor->current = professor->direita;
                }  
            }  
        }
            
        else // Senão, o professor se move pelo eixo y
        {
            if (dist_y<0) // Se a dist_y for negativa, o professor está abaixo do aluno
            {
                    
                if(grid[professor->posx][professor->posy - 1] != '1'){
            
                //Move o professor na grid           
                grid[professor->posx][professor->posy] = '0';
                professor->posy -=1;
                grid[professor->posx][professor->posy] = 't';             
           
                //Atualiza o sprite do professor
                professor->current = professor->tras;
                }    
            }
                
            else  // Senão, etá acima do aluno
            {
                if(grid[professor->posx][professor->posy + 1] != '1'){
            
                //Move o professor na grid           
                grid[professor->posx][professor->posy] = '0';
                professor->posy +=1;
                grid[professor->posx][professor->posy] = 't';
            
                //Atualiza o sprite do professor
                professor->current = professor->frente;
                }   
            }    
        } 
    }
   
    
    
    
    // Movimentação aleatória do professor
    
    else if (GetRandomValue(0, 2) == 1)
    {
        //Movimentação do professor de acordo com um valor aleatório de 0 a 3
    
        int random_direction = GetRandomValue(0,3); // 0 = tras; 1= frente; 2= direita; 3 = esquerda
    
        if (random_direction == 0) //tras
        {
        
            while (cont<1 && tem_parede ==0) //Movimenta 2 vezes se não encontrar nenhuma parede
            {
                if(grid[professor->posx][professor->posy - 1] != '1'){
            
                    //Move o professor na grid           
                    grid[professor->posx][professor->posy] = '0';
                    professor->posy -=1;
                    grid[professor->posx][professor->posy] = 't';             
           
                    //Atualiza o sprite do professor
                    professor->current = professor->tras;
                
                
                    if(grid[professor->posx][professor->posy - 1] == '1')
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
        
                if(grid[professor->posx][professor->posy + 1] != '1'){
            
                    //Move o professor na grid           
                    grid[professor->posx][professor->posy] = '0';
                    professor->posy +=1;
                    grid[professor->posx][professor->posy] = 't';
            
                    //Atualiza o sprite do professor
                    professor->current = professor->frente;
                
                    if(grid[professor->posx][professor->posy + 1] == '1')
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
                if(grid[professor->posx+1][professor->posy] != '1'){
            
                    //Move o professor na grid           
                    grid[professor->posx][professor->posy] = '0';
                    professor->posx +=1;
                    grid[professor->posx][professor->posy] = 't';
            
                    //Atualiza o sprite do professor
                    professor->current = professor->direita;
                
                    if(grid[professor->posx+1][professor->posy] == '1')
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
        
                if(grid[professor->posx-1][professor->posy] != '1'){
            
                    //Move o professor na grid           
                    grid[professor->posx][professor->posy] = '0';
                    professor->posx -=1;
                    grid[professor->posx][professor->posy] = 't';
            
                    //Atualiza o sprite do professor
                    professor->current = professor->esquerda;
                
                    if(grid[professor->posx-1][professor->posy] == '1')
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
    char grid[101][100] = {};

    //Declaracoes do mapa
    FILE *mapaGrid;
    
    //Declaração professor
    personagem professor;
    
    //Declaracoes do player
    personagem aluno;
    
    //declaracoes da camera;
    Camera2D camera = { 0 };
    camera.target = (Vector2){400, 300};
    camera.offset = (Vector2){400, 300};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
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
    
    professor.posx = 10;
    professor.posy = 10;
    professor.current = LoadTexture("static/sprites/professor-frente.png");
    
    professor.frente = LoadTexture("static/sprites/professor-frente.png");
    professor.tras = LoadTexture("static/sprites/professor-costas.png");
    professor.direita = LoadTexture("static/sprites/professor-direita.png");
    professor.esquerda = LoadTexture("static/sprites/professor-esquerda.png");
    
    
    //Inicializacao da do mapa
    mapaGrid = fopen(caminhoMapa, "r");
    
    
    //Inicializa cada coluna da grid com o mapa
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 101; j++){
            fread(&grid[j][i], sizeof(char), 1, mapaGrid);      
        }
    }
    
    SetTargetFPS(10);
    
   //Cleanup
   fclose(mapaGrid);
    
    while (!WindowShouldClose()){
        
        //atualiza o valor da camera
        camera.target = (Vector2){aluno.posx * 20, aluno.posy * 20};
        
        
        //Inicializa a Tela
        BeginDrawing();

        
        BeginMode2D(camera);


       //move o aluno
        moveplayer(grid, &aluno);

        
        //move o professor
        moveprof(grid, &professor, aluno.posx, aluno.posy);

        
        //Desenha o player e o profeesor
        drawGrid(grid, &aluno, professor.current);
        
        
        //Fundo Preto
        ClearBackground(BLACK);
        
        
        
        //Cleanup
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
