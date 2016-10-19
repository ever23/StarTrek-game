/*
  Name: CLASE RECOMPENZAS PARA EL JUEGO STR TREK
  Author: ENYERBER FRANCO
  Date: 26/11/14 12:34
  Description: DEFINICION DE LA CLASE RECOMPENZAS PARA EL JUEGO
*/

#ifndef RECMPENZAS_H_INCLUDED
#define RECMPENZAS_H_INCLUDED
#include<allegro.h>


#define fin                              0        /* BMP  */
#define simbolo                          1        /* BMP  */
#define v_nive                           2        /* BMP  */
#include "data_grabber.h"
#include "buffer.h"
#include "fuente.h"
class RECOMPENZAS
{
    public:
    RECOMPENZAS(const char *file_dat,const char *file_n);
    ~RECOMPENZAS();
    void ini();
    void sets(int,int);
    void set_nivel(int n){nivel=n;}
    void set_pts(int n){puntos=n;}
    void print_recompenzas(BITMAP *BMP);
    int get_nivel(){return nivel;}
    int get_pts(){return puntos;}
    void pasar_niveles();
    bool fin_de_juego();
    private:
        FUENTE font1;
    int nivel;
    bool findejuego;
    bool pas_nivel;
    int puntos;
    int vida;
        DATA_GRABBER d_rec;
        DATA_GRABBER d_nivel;
        BUFFER buffer;
};
#endif // RECMPENZAS_H_INCLUDED
