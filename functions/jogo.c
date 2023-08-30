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



void Win(){ //tela verde vitória

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
    FILE *save;
    
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
    
    //Se errarem o save diminui em um a vida no save
    if (saida == 0){
        
        vidas -= 1;
        
        save = fopen("static/save.bin", "r+b");
        fseek(save, sizeof(int), SEEK_SET);
        fwrite(&vidas, sizeof(int), 1, save);
        
        fclose(save);
    }
        
    labirinto();
}



void ProximoNivel(int nivel, int vida){
    
    FILE *save;
    int um, ran1, ran2;
    
    um = 1;
    ran1 = GetRandomValue(10, 40);
    ran2 = GetRandomValue(10, 30);
    
    nivel++;
    
    save = fopen("static/save.bin", "r+b");
    
    fwrite(&nivel, sizeof(int), 1, save);
    fwrite(&vida, sizeof(int), 1, save);
    fwrite(&um, sizeof(int), 1, save);
    fwrite(&um, sizeof(int), 1, save);
    fwrite(&ran1, sizeof(int), 1, save);
    fwrite(&ran2, sizeof(int), 1, save);
    
    
    fclose(save);
    
    labirinto();
}



//controla o labirinto e as perguntas
int labirinto (){
    //Declaracao que salva o valor retornado de loadgame
    int saida;
    
    //Declaracoes dos valores do jogo
    char caminhos[10][25];
    int posAlx, posAly, posPfx, posPfy, vidas, nivel;
    
    //Declaracao arquivo save
    FILE *save;
    
    //Declaracao do vetor de perguntas
    PERGUNTA vetperguntas[100];
    
    //Abre o save e atualiza os valores
    save = fopen("static/save.bin", "rb");
    
    //Verifica se existe save
    if (save == NULL){
        
        game_over();
        return 404;
        
    }
    
    //Carrega os caminhos dos mapas
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
    
    
    //Le o save
    fread(&nivel, sizeof(int), 1, save);
    fread(&vidas, sizeof(int), 1, save);
    fread(&posAlx, sizeof(int), 1, save);
    fread(&posAly, sizeof(int), 1, save);
    fread(&posPfx, sizeof(int), 1, save);
    fread(&posPfy, sizeof(int), 1, save);
    
    fclose(save);
    
    if (vidas == 0)
        game_over();
    
    else if (nivel == 10)
        Win();
        
    else {
    
        //Roda o jogo e salva a saida 
        saida = loadgame(caminhos[nivel], posAlx, posAly, posPfx, posPfy, vidas, nivel);
    
        //Carrega a tela apropriada dependendo da saida
        switch (saida)
        {
        case 99:
            perguntas(vetperguntas, nivel, vidas);
            break;
        case 88:
            ProximoNivel(nivel, vidas);
            break;
        }
    }
    
    return 0;
}



//faz a chamado do labirinto no nivel certo;
void Novojogo (int nivel, int vidas){
    
    int zero, tres, um, ran1, ran2;
    FILE *save;
    
    zero = 0;
    tres = 3;
    um = 1;
    
    ran1 = GetRandomValue(10, 40);
    ran2 = GetRandomValue(10, 30);
    
    save = fopen("static/save.bin", "wb");
    
    /*Formatacao do save:
        int nivel
        int vida
        int PosAlx
        int PosAly
        int PosPfx
        int PosPfy
    */
    
    fwrite(&zero, sizeof(int), 1, save);
    fwrite(&tres, sizeof(int), 1, save);
    fwrite(&um, sizeof(int), 1, save);
    fwrite(&um, sizeof(int), 1, save);
    fwrite(&ran1, sizeof(int), 1, save);
    fwrite(&ran2, sizeof(int), 1, save);
    
    fclose(save);
    
    labirinto();
    
}
