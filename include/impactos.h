/*
  Name: CLASE IMPACTOS PARA EL JUEGO STR TREK
  Author: ENYERBER FRANCO
  Date: 19/01/01 16:34
  Description: DEFINICION DE LA CLASE IMPACTOS PARA EL JUEGO
*/
#ifndef IMPACTOS_H_INCLUDED
#define IMPACTOS_H_INCLUDED
#include <allegro.h>
#include "enemigos.h"
#include "nave.h"
#include "mask.h"
#include <vector>

class IMPACTOS
{
    public:
        IMPACTOS();
        ~IMPACTOS();
        void impactos(NAVES *,int n,...);
        int get_puntos()
        {
            return puntos;
        }
        void set_pts(int P)
        {
            puntos=P;
        }
    private:
      int puntos;
      void enemigo_nave(NAVES *,ENEMIGOS *);
      void p_enemi_nave(NAVES *,ENEMIGOS *);
      void bala_enemi(ENEMIGOS *, vector<disp> *,Mask *);
      void b_laser_enemi(NAVES *,vector<disp> *);
      void b_laser_nav(ENEMIGOS *,disp *);


};

#endif // IMPACTOS_H_INCLUDED
