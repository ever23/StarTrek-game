#include "../include/mouse.h"
#include <iostream>
using namespace std;
MOUSE::MOUSE()
{
    n_mouse=0;
}

MOUSE::MOUSE(BITMAP *BMP_MOUSE)
{
   init(BMP_MOUSE);
}

MOUSE::~MOUSE()
{
  for(std::vector<BITMAP*>::iterator ibmp=bmp_mouses.begin();
      ibmp!=bmp_mouses.end();ibmp++)
      {
          destroy_bitmap(*ibmp);
      }
      bmp_mouses.clear();

}

int MOUSE::init()
{
    bmp_mouses.clear();
    int ret;
    ret=install_mouse();

    bmp_mouses.push_back(mouse_sprite);
    n_mouse=0;
    cout<< "iniciando mouse "<<ret<<endl;

    return ret;
}

int MOUSE::init(BITMAP *BMP_MOUSE)
{
    bmp_mouses.clear();
    int ret;
    ret=install_mouse();
   // bmp_mouse=create_bitmap(BMP_MOUSE->w,BMP_MOUSE->h);
   // blit(BMP_MOUSE,bmp_mouseS[0],0,0,0,0,BMP_MOUSE->w,BMP_MOUSE->h);
    bmp_mouses.push_back(BMP_MOUSE);
     n_mouse=0;
     cout<< "iniciando mouse "<<ret<<endl;
    return ret;
}

void MOUSE::remove()
{
    remove_mouse();
    cout<< "removiendo mouse "<<endl;
}

int MOUSE::x()
{
    return mouse_x;
}

int MOUSE::y()
{
    return mouse_y;
}

int MOUSE::z()
{
    return mouse_z;
}

bool MOUSE::b_der()
{
    if(mouse_b & 2)
        return 1;
    else
    return 0;
}

bool MOUSE::b_izq()
{
    if(mouse_b & 1)
        return 1;
    else
   return 0;
}

bool MOUSE::chek(int x1,int y1,int x2,int y2)
{
    if(mouse_x > x1 && mouse_x < x2 && mouse_y >y1 && mouse_y < y2)
        return 1;
    else
        return 0;
}

void MOUSE::draw(BITMAP *BUFFER,int mouse_n)
{
    if(mouse_n<=n_mouse)
    {
         draw_sprite(BUFFER,bmp_mouses[mouse_n],mouse_x,mouse_y);
    }else
    {
        allegro_message("EL BITMAP MOUSE %i NO EXISTE",mouse_n);
        exit();
    }
}

void MOUSE::load_bmp(BITMAP *BMP_MOUSE)
{
    if(bmp_mouses[MOUSE_D]!=NULL)
    {
        destroy_bitmap(bmp_mouses[MOUSE_D]);
        bmp_mouses[MOUSE_D]=create_bitmap(BMP_MOUSE->w,BMP_MOUSE->h);
        draw_sprite(bmp_mouses[MOUSE_D],BMP_MOUSE,0,0);
    }
}
int MOUSE::add_newbmp(BITMAP *BMP_MOUSE)
{
    bmp_mouses.push_back(BMP_MOUSE);
    n_mouse++;
    return n_mouse;
}
void MOUSE::get_z(int Z)
{
    position_mouse_z(Z);
}

void MOUSE::rango(int x1,int y1,int x2,int y2)
{
    set_mouse_range(x1,  y1,  x2,  y2);
}

void MOUSE::velocidad(int xspeed, int yspeed)
{
    set_mouse_speed( xspeed,  yspeed);
}


void MOUSE::get_distancia(int &mickeyx, int &mickeyy)
{
    get_mouse_mickeys( &mickeyx, &mickeyy);
}

void MOUSE::scare(int x, int y, int w, int h)
{
    scare_mouse_area( x,  y,  w,  h);
}
void MOUSE::unscare()
{
    unscare_mouse();
}











