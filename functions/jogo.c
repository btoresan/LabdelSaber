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
    
    //Volta para o Labirinto
    labirinto();
    
    return saida;
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