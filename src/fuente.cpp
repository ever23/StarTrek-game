/*
  Source:
  Name:
  Author: ENYERBER FRANCO
  Date: 00/00/14 00:00
  Description:
*/#include "fuente.h"
#include <iostream>
using namespace std;
FUENTE::FUENTE()
{
    //ctor
}
FUENTE::FUENTE(const char *FILE_NAME_PCX)
{
    load_pcx(FILE_NAME_PCX);
}
FUENTE::FUENTE(const char *FILE_NAME_TTF, int puntos, int flags)
{
    load_ttf(FILE_NAME_TTF,  puntos,  flags);
}
FUENTE::FUENTE(const char *FILE_NAME_TTF, const int w, const int h, const int flags)
{
    load_ttf_ex(FILE_NAME_TTF,  w,h,   flags);
}
FUENTE::~FUENTE()
{
    if(fuente)
   destroy_font(fuente);
   delete fuente;
}


void FUENTE::load_pcx(const char *FILE_NAME_PCX)
{
    cout<< "cargando "<<FILE_NAME_PCX<<endl;
    if((fuente=load_font(FILE_NAME_PCX,NULL,NULL))==NULL)
    {
        cout<< "ERROR AL CARGAR LA FUENTE COMPRUEVE QUE EL ARCHIVO "<<FILE_NAME_PCX<<" EXISTE "<<endl;
        allegro_message(" ERROR AL CARGAR LA FUENTE COMPRUEVE QUE EL ARCHIVO %s EXISTE",FILE_NAME_PCX);
        fuente=font;
    }
}
void FUENTE::load_ttf(const char *FILE_NAME_TTF, int puntos, int flags)
{
    cout<< "cargando "<<FILE_NAME_TTF<<endl;
    if((fuente=load_ttf_font(FILE_NAME_TTF,puntos,flags))==NULL)
    {
        cout<< "ERROR AL CARGAR LA FUENTE COMPRUEVE QUE EL ARCHIVO "<<FILE_NAME_TTF<<" EXISTE "<<endl;
        allegro_message(" ERROR AL CARGAR LA FUENTE COMPRUEVE QUE EL ARCHIVO %s EXISTE",FILE_NAME_TTF);
        fuente=font;
    }
}
void FUENTE::load_ttf_ex(const char *FILE_NAME_TTF, const int w, const int h, const int flags)
{
     cout<< "cargando "<<FILE_NAME_TTF<<endl;

    if((fuente=load_ttf_font_ex( FILE_NAME_TTF,  w,  h,  flags))==NULL)
    {
        cout<< "ERROR AL CARGAR LA FUENTE COMPRUEVE QUE EL ARCHIVO "<<FILE_NAME_TTF<<" EXISTE "<<endl;
        allegro_message(" ERROR AL CARGAR LA FUENTE COMPRUEVE QUE EL ARCHIVO %s EXISTE",FILE_NAME_TTF);
        fuente=font;
    }
}

int FUENTE::get_h()
{
    return fuente->height;
}
int FUENTE::text_length(const char *CADENA__)
{
  return  ::text_length(fuente, CADENA__);
}

FUENTE::operator ALLEGRO_FONT *()
{
    return fuente;
}
