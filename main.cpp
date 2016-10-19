/**
  Name: STAR TREK GAME
  Author: ENYERBER FRANCO
  Date: 22/01/15 16:40
  Description: IMPLEMENTACION DE LA FUNCION PRINCIPAL
  STAR TREK GEAME
**/

#include <allegro.h>
#include "include/star_trek_game.h"
#include "include/inicia.h"
/*---------------------------------------------------------------------------------*/
/*                              FUNCION PRINCIPAL                                  */
/*                                   MAIN()                                        */
/*---------------------------------------------------------------------------------*/

int main()
{
    INICIAR *GAME;
    STAR_TREK_GAME *star_trek;

    GAME = new INICIAR;

    GAME->init_gfx(GFX_AUTODETECT_WINDOWED,600,570);

    GAME->set_title("STAR TREK GAME");

    GAME->cargar_datafile("archivos/inicio");
    do
    {
        GAME->inicio();

        GAME->menu_principal();

        if(!GAME->game_over())
        {
            GAME->inicio();

            star_trek = new STAR_TREK_GAME;

            star_trek->init();

            star_trek->sets(GAME->get_pts(),GAME->get_nivel());

            star_trek->main();

            if(star_trek->chek_save())
            {
                GAME->savegame(star_trek->get_pts(),star_trek->get_nivel());
            }

            delete star_trek;
        }
    }
    while(!GAME->game_over());

    GAME->guardar_dtg();

    delete GAME;

    return 0;
}
END_OF_MAIN();

