/*
  Name: CLASE IMPACTOS PARA EL JUEGO STR TREK
  Author: ENYERBER FRANCO
  Date: 26/11/14 12:34
  Description: IMPLEMENTACION  DE LA CLASE IMPACTOS PARA EL JUEGO
*/
#include "../include/impactos.h"
#include <stdarg.h>
#include <iostream>
using namespace std;
///generaliza la deteccion de choques
IMPACTOS::IMPACTOS()
{
    puntos=0;
}
IMPACTOS::~IMPACTOS()
{

}
void IMPACTOS::impactos(NAVES *nave,int n,...)
{
    va_list _enemigos_;
    va_start(_enemigos_, n);
    for(int i=0; i<n; i++)
    {
        ENEMIGOS *enemi= va_arg(_enemigos_, ENEMIGOS*);
        enemigo_nave(nave,enemi);
        p_enemi_nave(nave,enemi);
        bala_enemi(enemi,nave->get_balas(),nave->get_dmask());
        bala_enemi(enemi,nave->get_torpedos(),nave->get_tmask());
        bala_enemi(enemi,nave->get_estallido1(),nave->get_dmask());
        bala_enemi(enemi,nave->get_estallido2(),nave->get_dmask());
        bala_enemi(enemi,nave->get_estallido3(),nave->get_dmask());
        b_laser_enemi(nave,enemi->get_laser());
        b_laser_nav(enemi,nave->get_laser());

    }
    va_end(_enemigos_);
}
//detectar impactos de enemigos contra la nave

inline void IMPACTOS::enemigo_nave(NAVES *nave,ENEMIGOS *enemigo)
{
    DAT_NAV nav=nave->get_nav();
    vector<ene> *enemi=enemigo->get_enemigos();
    vector<ene>::iterator iene;

    for(iene=enemi->begin(); iene!=enemi->end(); ++iene )
    {
        if(Mask::check_ppcollision(nave->get_mask(),enemigo->get_mask(),nav.x,nav.y,iene->x,iene->y))
        {
            if(iene->imp<1)
            {
                nave->dec_integridad(enemigo->power()+3);
                enemigo->dec_vida(&(*iene),nav.escudo+30);
            }
        }
    }
}

//detectar impactos de proyectil enemigos contra la nave
inline void IMPACTOS::p_enemi_nave(NAVES *nave,ENEMIGOS *enemigo)
{
    //detecta choques de proyectiles contra la nave
    DAT_NAV nav=nave->get_nav();
    vector<disp> *dis=enemigo->get_disp();
    vector<disp>::iterator idisp;

    //detecta los choques de disparos contra el escudo
    if(nav.escudo>0)
    {
       int d_escudo=10;
        for( idisp=dis->begin();  idisp!=dis->end(); idisp++)
        {
            if((idisp->x>=nav.x-d_escudo &&  idisp->x <= (nav.x+nav.tx+d_escudo) ) &&
                    (idisp->y>=nav.y-d_escudo && idisp->y<=nav.y+nav.ty+d_escudo) )
            {
                nave->dec_iescudo(enemigo->power()+1);
                idisp->y=600;
                idisp->x=0;
            }
        }
    }else
    for(idisp=dis->begin(); idisp!=dis->end(); idisp++)
    {
        if(Mask::check_ppcollision(nave->get_mask(),enemigo->get_dmask(),nav.x,nav.y,idisp->x,idisp->y))
        {
            nave->dec_integridad(enemigo->power()+2);
            idisp->y=600;
            idisp->x=0;
        }
    }
}

// detecta el choque de todos los proyectiles

void IMPACTOS::bala_enemi(ENEMIGOS *enemigo,vector<disp> *proyectil,Mask *p_mask)
{

    vector<ene> *enemi=enemigo->get_enemigos();
    for(vector<ene>::iterator iene=enemi->begin(); iene!=enemi->end(); iene++)
    {
        for(vector<disp>::iterator idisp=proyectil->begin(); idisp != proyectil->end(); idisp++)
        {
            if(Mask::check_ppcollision(enemigo->get_mask(),p_mask,iene->x,iene->y,idisp->x,idisp->y ))
            {
                enemigo->dec_vida(&(*iene),idisp->inp*2);
                if(iene->vida<0)
                    puntos+=idisp->inp*(enemigo->power()+enemigo->resistencia());
                idisp->y=0;
            }
        }
    }
}
void IMPACTOS::b_laser_enemi(NAVES *nave,vector<disp> *laser)
{
    DAT_NAV nav=nave->get_nav();
    vector<disp>::iterator idisp;

    for(idisp=laser->begin(); idisp!=laser->end(); ++idisp )
    {
        if((idisp->x>=nav.x &&  idisp->x <= (nav.x+nav.tx) ) &&
                (idisp->inp>(nav.y+(nav.ty/2)) ) )
        {
            idisp->inp=(nav.y+(nav.ty/2));
            if(idisp->inp<(nav.y+(nav.ty/2)))
                idisp->inp=(nav.y+(nav.ty/2));
            nave->dec_integridad(10);
        }
    }
}
void IMPACTOS::b_laser_nav(ENEMIGOS *enemigo,disp *disp)
{
    vector<ene> *enemi=enemigo->get_enemigos();
    vector<ene>::iterator iene=enemi->begin();
    for(int i=0; i<int(enemi->size()); i++,iene++)
    {
        if((disp->x>=iene->x &&  disp->x <= (iene->x+iene->tx) ) &&
                (disp->inp<(iene->y+(iene->ty/2)) ) )
        {
            disp->inp=(iene->y+(iene->ty/2));
            enemigo->dec_vida(&(*iene),15);
        }
    }
    iene=enemi->end();
}










