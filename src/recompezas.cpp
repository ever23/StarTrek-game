/*
  Name: CLASE RECOMPENZAS PARA EL JUEGO STR TREK
  Author: ENYERBER FRANCO
  Date: 26/11/14 12:34
  Description: IMPLEMENTACION  DE LA CLASE RECOMPENZAS PARA EL JUEGO
*/

#include "../include/recompenzas.h"
#include <iostream_alleg.h>
using namespace all;
#include <allegttf.h>

RECOMPENZAS::RECOMPENZAS(const char *file_dat,const char *file_n)
{
    puntos=0;
    nivel=0;
    d_rec.load(file_dat);
    d_nivel.load(file_n);
    font1.load_ttf("archivos/fuente.ttf", 10, ALLEGTTF_NOSMOOTH);

    pas_nivel=false;
    vida=3;
    buffer.create();
}
RECOMPENZAS::~RECOMPENZAS()
{
 //DTR
}
void RECOMPENZAS::print_recompenzas(BITMAP *BUFFER_)
{
    iosall.cargar_fuente(font1);
    iosall<<BMP(BUFFER_,0x3574c1)<<XY(370, 535)<< "PTS "<<puntos<<XY(474, 535) <<"NIVEL "<<nivel;
    masked_blit(d_rec[simbolo],BUFFER_,0,0,100,530,vida*30,35);
}
void RECOMPENZAS::pasar_niveles()
{
    buffer.clear(0xff00ff);
    nivel++;
        for(int j=0;j<80;j++)
        {
            buffer.blitbmp(d_rec[v_nive],0,0,138,142,300,300);
            buffer.blitbmp(d_nivel[nivel-1],0,0,238,288,76,82);
            buffer.mask_udapte();
            rest(3);
        }
}
bool RECOMPENZAS::fin_de_juego()
{

    if(vida<=0)
    {
         buffer.clear(0xff00ff);
        for(int j=0;j<80;j++)
        {
            buffer.blitbmp(d_rec[fin],0,0,138,142,300,300);
            buffer.mask_udapte();
            rest(5);

        }
        return true;

    }
return false;
}


void RECOMPENZAS::sets(int VIDA,int PUNTOS)
{
    vida=VIDA;
    puntos=PUNTOS;
}
