#include <raylib.h>
#include "functions/menu.c" //funções dos arquivos menu
#include "functions/scoreboard.c" //funções do scoreboard
#include "functions/jogo.c"
#include "functions/informacoes.c"


int run()
{
    switch (menu()) //roda o menu até que devolva qual funcao rodar
    {
        //opções do menu

        case 0:
            Novojogo(0, 3);
            break;

        case 1: //carrega jogo
            labirinto();
            break;

        case 2: 
            scoreboard(); //carrega o scorboard
            break;
  
        case 3:
            informacoes(); //mostra como jogar o jogo
            break;

        case 4: //saida, fecha o jogo
            break;
    }

    return 0;
}


int main()
{
    run();
    return 0;
}
