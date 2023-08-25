#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define QCOLEGAS 4

// Estrutura personagem
typedef struct {
    int posx;
    int posy;
    Texture2D current;
    Texture2D frente;
    Texture2D tras;
    Texture2D direita;
    Texture2D esquerda;
} PERSONAGEM;



void drawGrid (char grid[101][100], PERSONAGEM *aluno, Texture2D professor, Texture2D colega){
    //variaveis para carregar o apenas o qudrante certo
    //de forma fluida
    int metadex = 0;
    int metadey = 0;
    
    if (aluno->posx > 50)
        metadex = 30;
    if (aluno->posy > 50)
        metadey = 30;
    
    //para cada quadrado da grid
    for (int i = metadex; i < metadex + 70; i++){
        for (int j = metadey; j < metadey + 70; j++){
            //desenha o tipo do objeto no quadrado
            //player
            if (grid[i][j] == 'p')
                DrawTexture(aluno->current, i*20, j*20, WHITE);
            
            //professor
            else if (grid[i][j] == 't')
                DrawTexture(professor, i*20, j*20, WHITE);
            
            else if (grid[i][j]=='c')
                DrawTexture(colega,i*20,j*20,WHITE);
            
           //parede
           else if (grid[i][j] == '1')
                DrawRectangle(20*i, 20*j, 20, 20, WHITE);
            
            //proximo nivel
            else if (grid[i][j] == 'E')
                DrawRectangle(20*i, 20*j, 20, 20, BLUE);
            
            //caminho para a vitoria
            else if (grid[i][j] == 'W')
                DrawRectangle(20*i, 20*j, 20, 20, GREEN);
            
            
            //nada
            else
                DrawRectangle(20*i, 20*j, 20, 20, BLACK);
        }
    }
}



void moveplayer (char grid[101][100], PERSONAGEM *aluno){

    if(IsKeyDown(KEY_UP) && grid[aluno->posx][aluno->posy - 1] != '1'){
        
        //Move o aluno na grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posy -= 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //atualiza o sprite 
        aluno->current = aluno->tras;
    }

    else if(IsKeyDown(KEY_LEFT) && grid[aluno->posx - 1][aluno->posy] != '1'){
        
        //Move o aluno na grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posx -= 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //atualiza o sprite
        aluno->current = aluno->esquerda;
    }

    else if(IsKeyDown(KEY_DOWN) && grid[aluno->posx][aluno->posy + 1] != '1'){
        
        //Move o Aluno na Grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posy += 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //Atualiza o sprite
        aluno->current = aluno->frente;
    }

    else if(IsKeyDown(KEY_RIGHT) && grid[aluno->posx + 1][aluno->posy] != '1'){
        
        //Move o Aluno na Grid
        grid[aluno->posx][aluno->posy] = '0';
        aluno->posx += 1;
        grid[aluno->posx][aluno->posy] = 'p';
        
        //Atualiza o sprite
        aluno->current = aluno->direita;
    }

}



void moveprof (char grid[101][100], PERSONAGEM *professor, int posxal, int posyal){
           
    int cont=0;
    int tem_parede = 0;
    
    // Calcula a distancia entre o professor e o aluno
    float distancia = sqrt(pow(posxal - professor->posx, 2) + pow(posyal - professor->posy, 2));
    
    
    // Perseguição professor
    
    if (distancia<=13) // Se o professor estiver próximo do aluno, inicia a perseguição
    {
        float dist_x = posxal - professor->posx; // Calcula a distancia em relação ao x entre o aluno e o professor
        float dist_y = posyal - professor->posy; // Calcula a distancia em relação ao y entre o aluno e o professor
            
        if (fabs(dist_x) >= fabs(dist_y)) // Se o valor absoluto da distancia em relação ao x for maior ou igual, o professor se move pelo eixo x
        {
            if (dist_x < 0) // Se a dist_x for negativa, o professor está à direita do aluno
            {
                if(grid[professor->posx-1][professor->posy] != '1' && grid[professor->posx-1][professor->posy] != 'p')
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
                if(grid[professor->posx+1][professor->posy] != '1'&& grid[professor->posx+1][professor->posy] != 'p')
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
                    
                if(grid[professor->posx][professor->posy - 1] != '1' && grid[professor->posx][professor->posy - 1] != 'p'){
            
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
                if(grid[professor->posx][professor->posy + 1] != '1' && grid[professor->posx][professor->posy + 1] != 'p'){
            
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


void colega(char grid[101][100],PERSONAGEM colegas[], int posxal, int posyal)
{
    int i;
    
    for(i=0;i<QCOLEGAS;i++)
    {       
        do //Enquanto a posição do colega for igual a outro objeto/personagem , sorteia uma nova posição
        {
            colegas[i]->posx = GetRandomValue(0,101);
            colegas[i]->posy = GetRandomValue(0,100);
        
        }while(grid[colegas[i]->posx][colegas[i]->posy]=='1' || grid[colegas[i]->posx][colegas[i]->posy]=='t'|| grid[colegas[i]->posx][colegas[i]->posy]=='E'|| grid[colegas[i]->posx][colegas[i]->posy]=='W');
    
        //Atualiza a grid com o char correspondente ao colega
        grid[colegas[i]->posx][colegas[i]->posy] = 'c';
        
        // Se ele estiver na mesma posição do aluno, inicia as perguntas
        if(posxal==colegas[i]->posx && posyal == colegas[i]->posy)
            perguntas();  
    }     
}









int profachou(PERSONAGEM *aluno, PERSONAGEM *professor){
    
    if (abs(aluno->posx - professor->posx) <= 1 && abs(aluno->posy - professor->posy) <= 1)
        return 1;
    else
        return 0;
}



int saida(PERSONAGEM *aluno, char grid[101][100]){
    
    //procura uma saida em todos os quadrados adjacentes ao aluno
    if (grid[aluno->posx + 1][aluno->posy + 1] == 'E')
        return 1;
    else if (grid[aluno->posx + 1][aluno->posy - 1] == 'E')
        return 1;
    else if (grid[aluno->posx - 1][aluno->posy + 1] == 'E')
        return 1;
    else if (grid[aluno->posx - 1][aluno->posy - 1] == 'E')
        return 1;
    
    
    else
        return 0;
}



 int loadgame(char *caminhoMapa, int posAlx, int posAly, int posPfx, int posPfy, int vidas){
    //Declaracao do Tamanho da tela 
    const int screenWidth = 800;
    const int screenHeight = 600;
    

    //Declaracao da Grid 20x menor que o tamanho da tela por sessao
    //1 quadradoda grid = 20x20
    char grid[101][100] = {};

    //Declaracoes do mapa
    FILE *mapaGrid;
    
    //Controle de Perguntas
    int achou = 0;
    
    //Declaração professor
    PERSONAGEM professor;
    
    //Declaracoes do player
    PERSONAGEM aluno;
    
    //Declarações do vetor de colegas
    PERSONAGEM colegas[QCOLEGAS];
    
    //Declaraqcoes de vida
    char displayVidas[15];
    
    //Inicializao do Display da Vida
    strcpy(displayVidas, "HP_ALUNO = N");
    displayVidas[11] = (char) (vidas + 48);
    
    
    //declaracoes da camera;
    Camera2D camera = { 0 };
    camera.target = (Vector2){400, 300};
    camera.offset = (Vector2){400, 300};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    //Inicializa a janela 
    InitWindow(screenWidth, screenHeight, "Labirinto Del Saber ALPHA");
    
    
    //Inicializacao da textura do player
    aluno.posx = posAlx;
    aluno.posy = posAly;
    aluno.current = LoadTexture("static/sprites/aluno_frente.png");
    
    aluno.frente = LoadTexture("static/sprites/aluno_frente.png");
    aluno.tras = LoadTexture("static/sprites/aluno_tras.png");
    aluno.esquerda = LoadTexture("static/sprites/aluno_esquerda.png");
    aluno.direita = LoadTexture("static/sprites/aluno_direita.png");
    
    
    //Inicializacao da textura e posição do professor
    
    professor.posx = posPfx;
    professor.posy = posPfy;
    professor.current = LoadTexture("static/sprites/professor-frente.png");
    
    professor.frente = LoadTexture("static/sprites/professor-frente.png");
    professor.tras = LoadTexture("static/sprites/professor-costas.png");
    professor.direita = LoadTexture("static/sprites/professor-direita.png");
    professor.esquerda = LoadTexture("static/sprites/professor-esquerda.png");
    
    // Inicialização da textura dos colegas  
    int i;
    
    for(i=0;i<QCOLEGAS;i++)
    {
        colegas[i].current = LoadTexture("static/sprites/colega.png");
    }
    
    
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
    
    while (!WindowShouldClose() && achou == 0){
        
        //Professor achou o aluno, e faz a pergunta?
        if (profachou(&aluno, &professor) == 1)
            achou = 1;
        
        else if (saida(&aluno, grid) == 1)
            achou = 2;
        
        else {
            //Atualiza o valor da camera
            camera.target = (Vector2){aluno.posx * 20, aluno.posy * 20};
        
        
            //Inicializa a Tela
            BeginDrawing();

        
            //Inicializa a camera 2D
            BeginMode2D(camera);


            //move o aluno
            moveplayer(grid, &aluno);

        
            //move o professor
            moveprof(grid, &professor, aluno.posx, aluno.posy);
            
            //posicionamento e lógica colega
            colega(grid,colegas,aluno.posx,aluno.posy);

        
            //Desenha o player e o profeesor e o colega
            drawGrid(grid, &aluno, professor.current,colegas[0].current);
            
            
            //Desenha vida do Aluno
            DrawText(displayVidas, aluno.posx*20 - 390, aluno.posy*20 - 290, 30, RED);
        
        
            //Fundo Preto
            ClearBackground(BLACK);
        
        
            //Cleanup
            EndMode2D();
            EndDrawing();
        }
    }
    CloseWindow();
    
    
    //Valores de Retorno
    if (achou == 1)
        //Caso o professor encontre o aluno
        return 99;
        
    else if (achou == 2)
        //Caso o aluno ache a saida
        return 88;
    
    else 
        //Caso alguem feche a janela
        return 0;
    
    return 0;
}
