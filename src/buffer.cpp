/*
  Source:
  Name:
  Author: ENYERBER FRANCO
  Date: 00/00/14 00:00
  Description:
*/
#include "../include/buffer.h"
#include "../include/gfx_basic.h"
#include <iostream>
using namespace std;
BUFFER::BUFFER()
{
    mi_bmp=NULL;
}
BUFFER::BUFFER(const char *filename)
{
    load(filename);
}
BUFFER::BUFFER(int w,int h)
{
    create(w,h);
}
BUFFER::~BUFFER()
{
    delete_bmp();
}
void BUFFER::act_wh()
{
   h=mi_bmp->h;
   w=mi_bmp->w;
}
bool BUFFER::load(const char *filename)
{
    cout<< "cargando "<<filename<< "....."<<endl;
   if((mi_bmp=load_bitmap(filename,NULL))==NULL)
   {
       allegro_message("EL ARCHIVO %s NO EXISTE",filename);
       cout<< "EL ARCHIVO  "<<filename<< " NO EXISTE"<<endl;
       return 0;
   }
   act_wh();
   return 1;
}
void BUFFER::create(int w, int h)
{
    mi_bmp=create_bitmap(w,h);
    clear();
    act_wh();
}

void BUFFER::create_vdo(int w, int h)
{
    mi_bmp=create_video_bitmap( w,  h);
    clear_bitmap(mi_bmp);
    clear();
    act_wh();
}
void BUFFER::delete_bmp()
{
     if(mi_bmp!=NULL)
    {
       clear_to_color(mi_bmp,0x1);
       destroy_bitmap(mi_bmp);
    }
    mi_bmp=NULL;
}

void BUFFER::clear()
{
    clear_bitmap(mi_bmp);
}

void BUFFER::clear(int COLOR)
{
    clear_to_color(mi_bmp,COLOR);
}
BUFFER::operator BITMAP*()
{
    return mi_bmp;
}
int BUFFER::get_h()
{
    return h;
}
int BUFFER::get_w()
{
    return w;
}
void BUFFER::blitbmp(BITMAP *bmp_imp, int source_x, int source_y, int dest_x, int dest_y, int width, int height)
{

    if(is_memory_bitmap(mi_bmp))
    {
       blit(bmp_imp,mi_bmp,  source_x,  source_y,  dest_x,  dest_y,  width,  height);
    }else if(is_video_bitmap(mi_bmp))
    {
        acquire_bitmap(mi_bmp);
        blit(bmp_imp,mi_bmp,  source_x,  source_y,  dest_x,  dest_y,  width,  height);
        release_bitmap(mi_bmp);
    }
}
void BUFFER::mask_blitbmp(BITMAP *bmp_imp, int source_x, int source_y, int dest_x, int dest_y, int width, int height)
{

    if(is_memory_bitmap(mi_bmp))
    {
       masked_blit(bmp_imp,mi_bmp,  source_x,  source_y,  dest_x,  dest_y,  width,  height);
    }else if(is_video_bitmap(mi_bmp))
    {
        acquire_bitmap(mi_bmp);
        masked_blit(bmp_imp,mi_bmp,  source_x,  source_y,  dest_x,  dest_y,  width,  height);
        release_bitmap(mi_bmp);
    }
}

void BUFFER::drawbmp(BITMAP *bmp_imp,int dest_x,int dest_y)
{
    draw_sprite(mi_bmp,bmp_imp, dest_x,dest_y);
}
void BUFFER::update()
{
    if(is_memory_bitmap(mi_bmp))
    {
        blit(mi_bmp, screen,  0,  0,  0,  0, screen_w(),  screen_h());
    }else if(is_video_bitmap(mi_bmp))
    {
        show_video_bitmap(mi_bmp);
    }

}

void BUFFER::mask_udapte()
{
    if(is_memory_bitmap(mi_bmp))
    {
        masked_blit(mi_bmp, screen,  0,  0,  0,  0,  screen_w(),  screen_h());
    }else if(is_video_bitmap(mi_bmp))
    {
        show_video_bitmap(mi_bmp);
    }

}

void BUFFER::save(const char *FILENAME)
{
    save_bitmap(FILENAME, mi_bmp,NULL);
}

void BUFFER::stretchblit(BITMAP *source, int source_x,int source_y,int source_width,
                        int source_height, int dest_x,int dest_y,int dest_width,int dest_height)
{
    stretch_blit(source,  mi_bmp,  source_x, source_y, source_width, source_height,  dest_x, dest_y, dest_width, dest_height);
}


void BUFFER::mask_stretchblit(BITMAP *source, int source_x,int source_y,int source_width,
                        int source_height, int dest_x,int dest_y,int dest_width,int dest_height)
{
    masked_stretch_blit(source,  mi_bmp,  source_x, source_y, source_width, source_height,  dest_x, dest_y, dest_width, dest_height);
}

void BUFFER::stretch_drawbmp(BITMAP *sprite, int x, int y, int w, int h)
{
    stretch_sprite(mi_bmp,  sprite,  x,  y,  w,  h);
}
