#include "../include/data_grabber.h"
#include <iostream>
using namespace std;
DATA_GRABBER::DATA_GRABBER()
{

}

DATA_GRABBER::DATA_GRABBER(const char *FILENAME,const char *ext)
{

    load(FILENAME,ext);
}

DATA_GRABBER::~DATA_GRABBER()
{
   //unload_datafile(data);
   cout<< "destroy "<<filename<<endl;
   delete data;
}

bool DATA_GRABBER::load(const char *FILENAME,const char *ext)
{
    filename=FILENAME;
    ext_file=ext;
    filename+=ext_file;
    cout<< "cargando "<<filename<< "....."<<endl;
    if((data=load_datafile(filename.c_str()))==NULL)
    {
        allegro_message("EL ARCHIVO %s NO EXISTE",filename.c_str());
        return 1;
    }

    return 0;
}
BITMAP *DATA_GRABBER::operator[](int i)
{
    if(((BITMAP*)data[i].dat)==NULL)
    {
         allegro_message("EL OBJETO %i NO EXISTE EN EL ARCHIVO %s",i,filename.c_str());
         return NULL;
    }else
   return ((BITMAP*)data[i].dat);
}


void DATA_GRABBER::draw_bmp(BITMAP *BUFFER,int bitmap,int x,int y)
{
     if(((BITMAP*)data[bitmap].dat)==NULL)
    {
         allegro_message("EL OBJETO %i NO EXISTE EN EL ARCHIVO %s",bitmap,filename.c_str());
          exit();
    }

    draw_sprite(BUFFER,(BITMAP*)data[bitmap].dat, x,y);
}

void DATA_GRABBER::draw_rle(BITMAP *BUFFER,int sprite,int x,int y)
{
     if(((BITMAP*)data[sprite].dat)==NULL)
    {
         allegro_message("EL OBJETO %i NO EXISTE EN EL ARCHIVO %s",sprite,filename.c_str());
         exit();
    }
    draw_rle_sprite(BUFFER,(RLE_SPRITE*)data[sprite].dat,  x,  y);
}

void DATA_GRABBER::blit_bmp(BITMAP *BUFFER,int bitmap, int source_x, int source_y, int dest_x, int dest_y, int width, int height)
 {

if(((BITMAP*)data[bitmap].dat)==NULL)
    {
         allegro_message("EL OBJETO %i NO EXISTE EN EL ARCHIVO %s",bitmap,filename.c_str());
          exit();
    }
    blit((BITMAP*)data[bitmap].dat,BUFFER,  source_x,  source_y,  dest_x,  dest_y,  width,  height);

}
