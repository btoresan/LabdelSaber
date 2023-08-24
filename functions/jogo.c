#include "labirinto.c"
#include <raylib.h>
#include <string.h>

//Declaracao de funcoes para nao serem implicitas
int labirinto();
void jogo();
int run();


//Estrutura perguntas
typedef struct
{
    char enunciado[200];
    int nalternativas;
    int altcorreta;
    char alternativas [4][200];
}PERGUNTA;



void Win(){

    // Inicializacao
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    int escape = 0;

    InitWindow(screenWidth, screenHeight, "Vitoria");

    while (!WindowShouldClose() && escape == 0) {

        //Inicializacao do desenho
        BeginDrawing();
        
        ClearBackground(GREEN);

        // Texto do Gaem Over
        DrawText("Voce escapou do INF!!! :)", screenWidth/2 - MeasureText("Voce escapou do INF!!! :)", 40)/2, screenHeight/2 - 40, 40, WHITE);
        DrawText("Aperte R para reiniciar", screenWidth/2 - MeasureText("Aperte R para reiniciar", 20)/2, screenHeight/2 + 20, 20, GRAY);
            
        //Volta para o menu
        if (IsKeyPressed(KEY_R)) {
            escape = 1;
        }

        EndDrawing();
    }
    
    // Cleanup
    CloseWindow();
    
    run();
    
}



void game_over(){
    // Inicializacao
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    int escape = 0;

    InitWindow(screenWidth, screenHeight, "Game Over Screen");

    while (!WindowShouldClose() && escape == 0) {

        //Inicializacao do desenho
        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        // Texto do Gaem Over
        DrawText("Game Over", screenWidth/2 - MeasureText("Game Over", 40)/2, screenHeight/2 - 40, 40, RED);
        DrawText("Aperte R para reiniciar", screenWidth/2 - MeasureText("Aperte R para reiniciar", 20)/2, screenHeight/2 + 20, 20, GRAY);
            
        //Volta para o menu
        if (IsKeyPressed(KEY_R)) {
            escape = 1;
        }

        EndDrawing();
    }
    
    // Cleanup
    CloseWindow();
    
    run();
    
}



//Faz uma pergunta
void perguntas (PERGUNTA *vetperguntas, int nivel, int vidas){
    
    //Declaração de textura
    Texture2D fundo_perguntas;
    
    
    //valor que a função retornará
    int saida = -1;
    
    
    //Posição inicial da escolha
    int pos_escolha=200;
    
    int pos_alt = 0;
    
    int i,n,k;
    
    FILE *arqp;
    
    //Pega um valor aleatório que será a posição da pergunta escolhida
    int nump = GetRandomValue(0,99);
    
    arqp = fopen("static/perguntas.txt","r");
    
    if (arqp==NULL)
        printf("Falha na abertura do arquivo!");
    
    else
    {
        for(i=0;i<100;i++)
        {
            // Lê a estrutura de 100 perguntas (minimo)
            fgets(vetperguntas[i].enunciado,sizeof(vetperguntas[i].enunciado),arqp);
            fscanf(arqp,"%d",&vetperguntas[i].nalternativas);
            fscanf(arqp,"%d",&vetperguntas[i].altcorreta);
            
            getc(arqp);
            
            for(n=0;n<4;n++)
            {
                fgets(vetperguntas[i].alternativas[n],sizeof(vetperguntas[i].alternativas[n]),arqp); 
            }    
        }
        
        //Inicializacao da saida
        InitWindow(1000, 500, "PERGUNTAS");
        
        fundo_perguntas = LoadTexture("static/fundo_perguntas.png");
    
        while (!WindowShouldClose() && saida==-1)
        {
           
            
            BeginDrawing();
            
            
            DrawTexture(fundo_perguntas,0,0,WHITE);
            
            // Desenha o enunciado
            DrawText(vetperguntas[nump].enunciado, 0, 100, 20, BLUE);
            
            // Loop que desenha cada alternativa
            for(k=0;k<4;k++)
            {
                DrawText(vetperguntas[nump].alternativas[k], 0, 200+k*70, 18, WHITE);        
            }
            
            //Posição inicial da escolha (começa na primeira alternativa)
            DrawText(vetperguntas[nump].alternativas[pos_alt], 0, pos_escolha, 18, RED);
            
            if(IsKeyPressed(KEY_DOWN))
            {
                //Se a escolha estiver na ultima alternativa, volta para a primeira
                if (pos_escolha == 410)
                {
                    pos_escolha = 200;
                    pos_alt = 0;
                }
                
                //Senão, desce para a proxima alternativa
                else
                {
                    pos_escolha = pos_escolha + 70;  
                    pos_alt = pos_alt +1;
                }                    
            }
            
            else if (IsKeyPressed(KEY_UP))
            {
                //Se a escolha estiver na primeira alternativa, vai para a ultima
                if (pos_escolha == 200)
                {
                    pos_escolha = 410;
                    pos_alt = 3;
                }
                
                //Senão, sobe para a proxima alternativa
                else
                {
                    pos_escolha = pos_escolha - 70;      
                    pos_alt = pos_alt -1;
                }                    
            }
            
            // Se a escolha for correta, devolve 1
            if(pos_alt+1==vetperguntas[nump].altcorreta)
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    saida = 1;
                }
            }
            
            //Senão devolve 0
            else if (IsKeyPressed(KEY_ENTER))
            {
                saida = 0;
            }

            EndDrawing();
        }
    }
    
    //Cleanup
    CloseWindow();
    fclose(arqp);
    
    //volta pro jogo e subtrai a vida caso algeum erre
    if (saida == 1)
        jogo(nivel, vidas);
    else
        jogo(nivel, vidas -1);
    
}



//controla o labirinto e as perguntas
int labirinto (char *caminhoMapa, int posAlx, int posAly, int posPfx, int posPfy, int nivel, int vidas){
    //Declaracao que salva o valor retornado de loadgame
    int saida;
    
    //Declaracao do vetor de perguntas
    PERGUNTA vetperguntas[100];
    
    //Roda o jogo e salva a saida 
    saida = loadgame(caminhoMapa, posAlx, posAly, posPfx, posPfy, vidas);
    
    //Carrega a tela apropriada dependendo da saida
    switch (saida)
    {
        case 99:
            perguntas(vetperguntas, nivel, vidas);
            break;
        case 88:
            jogo(nivel + 1,vidas);
            break;
    }
    
    
    return 0;
}



//faz a chamado do labirinto no nivel certo;
void jogo (int nivel, int vidas){
    char caminhos[10][25];
    
    if (vidas == 0){
        game_over();
    }
    
    else if (nivel == 10){
        Win();
    }
    
    else {
        strcpy(caminhos[0], "static/mapas/mapa1.txt");
        strcpy(caminhos[1], "static/mapas/mapa2.txt");
        strcpy(caminhos[2], "static/mapas/mapa3.txt");
        strcpy(caminhos[3], "static/mapas/mapa4.txt");
        strcpy(caminhos[4], "static/mapas/mapa5.txt");
        strcpy(caminhos[5], "static/mapas/mapa6.txt");
        strcpy(caminhos[6], "static/mapas/mapa7.txt");
        strcpy(caminhos[7], "static/mapas/mapa8.txt");
        strcpy(caminhos[8], "static/mapas/mapa9.txt");
        strcpy(caminhos[9], "static/mapas/mapa10.txt");
    
        labirinto(caminhos[nivel], 1, 1, GetRandomValue(1, 40), GetRandomValue(1, 30), nivel, vidas);
    }
}