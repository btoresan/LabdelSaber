#include <raylib.h>
#include "functions/menu.h" //puxa as funções dos arquivos menu
#include "functions/scoreboard.h" //

int run()
{
    switch (menu()) //roda o menu até que devolva qual funcao rodar
    {
        //opções do menu
        case 1: 
            scoreboard(); //carrega o scorboard
            break;
        
    }

    return 0;
}


int main()
{
    run();
    return 0;
}
