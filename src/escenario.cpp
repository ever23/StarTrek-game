/*
  Name: CLASE ESCENARIO PARA EL JUEGO STR TREK
  Author: ENYERBER FRANCO
  Date: 26/11/14 12:34
  Description: IMPLEMENTACION  DE LA CLASE ESCENARIO PARA EL JUEGO
*/

#include "../include/escenario.h"
ESCENARIO::ESCENARIO(const char *FILE_ESC)
{
    ensc.load(FILE_ESC);
    retraso=0;
    v_nuve=0;
}
ESCENARIO::~ESCENARIO()
{

}
void ESCENARIO::pintar_escenario(BITMAP *BUFFER)
{
    ensc.draw_bmp(BUFFER,0);
}
void ESCENARIO::pintar_nuve(BITMAP *BUFFER)
{
     blit(ensc[1],BUFFER,0,v_nuve,21,14,550,500);
}
void ESCENARIO::actualizar_nuve(int INICIALIZACION,int RETRASO,int decremento)
{
     if(v_nuve<= 0)v_nuve=INICIALIZACION;
     if(retraso==0)v_nuve-=decremento;
     retraso++;
     if(retraso>=RETRASO)retraso=0;
}
