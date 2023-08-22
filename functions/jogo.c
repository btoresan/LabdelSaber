#include "labirinto.c"
#include <raylib.h>


//Estrutura perguntas

typedef struct
{
    char enunciado[200];
    int nalternativas;
    int altcorreta;
    char alternativas [4][200];
}PERGUNTA;


int perguntas (PERGUNTA *vetperguntas){
    
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
        InitWindow(800, 600, "Labirinto Del Saber ALPHA");
    
        while (!WindowShouldClose() && !IsKeyPressed(KEY_Q))
        {
           
            
            BeginDrawing();
            
            // Desenha o enunciado
            DrawText(vetperguntas[nump].enunciado, 0, 100, 20, BLUE);
            
            // Loop que desenha cada alternativa
            for(k=0;k<4;k++)
            {
                DrawText(vetperguntas[nump].alternativas[k], 0, 200+k*80, 18, WHITE);        
            }
            
            
                
            EndDrawing();
        }
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
    
    //Declaracao do vetor de perguntas
    PERGUNTA vetperguntas[100];
    
    //Roda o jogo e salva a saida 
    saida = loadgame("static/mapas/mapa1.txt", 1, 1, 1, 30);
    
    //Carrega a tela apropriada dependendo da saida
    switch (saida)
    {
        case 99:
            perguntas(vetperguntas);
            break;
    }
    
    
    return 0;
}




int jogo (){
    labirinto();
    
    return 0;
}