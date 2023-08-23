#include <raylib.h>
#include "functions/menu.c" //funções dos arquivos menu
#include "functions/scoreboard.c" //funções do scoreboard
#include "functions/jogo.c"


int run()
{
    switch (menu()) //roda o menu até que devolva qual funcao rodar
    {
        //opções do menu

        case 0:
            jogo(0);
            break;

        //case 1: carrega jogo

        case 2: 
            scoreboard(); //carrega o scorboard
            break;
        
        //case 3: inofrmacoes

        //case 4: sair
    }

    return 0;
}


int main()
{
    run();
    return 0;
}
