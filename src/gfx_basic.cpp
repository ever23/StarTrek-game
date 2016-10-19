#include "../include/gfx_basic.h"
#include <winalleg.h>
#include <iostream>
using namespace std;
#include <iostream_alleg.h>
using namespace all;
//consola
void gotoxy(int x,int y)
{
    HANDLE hCon;
    COORD dwPos;
    dwPos.X= x;
    dwPos.Y= y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}
//consola
//GFX_BASIC
int GFX_BASIC::pantalla_h=0;
int GFX_BASIC::pantalla_w=0;
int GFX_BASIC::profundidad=0;
int  screen_w()
{
    return GFX_BASIC::pantalla_w;
}
int  screen_h()
{
    return GFX_BASIC::pantalla_w;
}

GFX_BASIC::GFX_BASIC()
{

}

bool GFX_BASIC::init_gfx(int _GFX_MODE_,int W,int H,int DIS_MODE)
{
    int RET;
    allegro_init();
    install_keyboard();
    profundidad=desktop_color_depth();
    if(profundidad!=0)
    {
        set_color_depth(profundidad);
    }
    else
    {
        profundidad=32;
        set_color_depth(profundidad);
    }
    //GFX_AUTODETECT_WINDOWED
    pantalla_h=H;
    pantalla_w=W;
    cout<<endl<< "iniciando allegro...."<<endl;
    RET=gfx_mod( _GFX_MODE_);

    set_display_switch_mode(DIS_MODE);
    aspa_init();
    return RET;
}

GFX_BASIC::~GFX_BASIC()
{
    allegro_exit();
    cout<< "cerrando allegro..."<<endl;
}

bool GFX_BASIC::gfx_mod(int _GFX_MODE_)
{
    if (set_gfx_mode(_GFX_MODE_, pantalla_w, pantalla_h, 0, 0)<0)
    {
        allegro_message("            No se pudo inicializar modo grafico       \n            %s\n    \n  ", allegro_error);
        allegro_exit();
        exit();
        return 0;
    }
    cout<<"GFX "<<_GFX_MODE_<< "  " << pantalla_w<<" X "<< pantalla_h<<" X "<<profundidad<< endl;
    return 1;
}

void GFX_BASIC::set_title(const char *titulo)
{
    set_window_title(titulo);
    cout<< "titulo "<<titulo<<endl;
    title_game=titulo;
}





