/*
  Source:
  Name:
  Author: ENYERBER FRANCO
  Date: 00/00/14 00:00
  Description:
*/
#include "../include/b_aspa.h"
#include <allegro.h>
bool B_ASPA::salir = false;
void B_ASPA::aspa_init()
{
    set_close_button_callback(exit);
}

void B_ASPA::exit()
{
    salir = true;
}
END_OF_FUNCTION(exit);
bool B_ASPA::game_over()
{
    return salir;
}
