/*
  Name: CLASE ENEMIGOS PARA EL JUEGO STR TREK
  Author: ENYERBER FRANCO
  Date: 26/11/14 12:34
  Description: DEFINICION DE LA CLASE ENEMIGOS PARA EL JUEGO
*/
#ifndef ENEMIGOS_H_INCLUDED
#define ENEMIGOS_H_INCLUDED
#include <allegro.h>
#include <vector>
using namespace std;
#include "disparos.h"
#include "mask.h"
#include "data_grabber.h"
#include "buffer.h"

#define balae_bmp 0
#define enemi_bmp 1
#define torpedo_bmp 2
struct ene
{
    int x,y;
    int dir;
    int vida;
    int img_x;
    int vcd;
    int tx,ty;
    int x1,y1;
    int imp;
    int dis;
};

class ENEMIGOS
{
public:
    ENEMIGOS(){}
    ENEMIGOS(const char *FILE_ENEMI,int N_ENEMIGOS,int TIPO,int PODER,int RESISTENCIA,int ANCHO,int ALTO);
    ~ENEMIGOS();
    void init(const char *FILE_ENEMI,int N_ENEMIGOS,int TIPO,int PODER,int RESISTENCIA,int ANCHO,int ALTO);
    void destroy();
    void cantidad(int );
    void pinta_enemigo(BITMAP *);
    void actualizar(bool dispara=1);
    void actualizar_big();
    void disparo_laser(BITMAP *);
    void set_vcd(int);
    void set_min_vcd(int n);
    vector <ene>  *get_enemigos();
    vector <disp> *get_disp();
    vector <disp> *get_laser();
    int get_vida(int n)
    {
        n--;
        return enemigos[n].vida;
    }
    void dec_vida(ene *enemi,int n);
     int power();
     int resistencia(){return vida;}
     Mask *get_mask()
     {
         return mask;
     }
     Mask *get_dmask()
     {
         return d_mask;
     }
private:
    void reiniciar(ene *);
    void big_disparo_log();
    void disparo(BITMAP *);
    void disparo_log();
    void mov_aleatorio(ene *);
    int tipo,poder;
    int tick;
    int tickaux;
    int vida;
    int min_vcd;
    int tx,ty;
    vector <ene> enemigos;
    vector <disp> disparos;
    vector <disp> laser;
    DATA_GRABBER d_enemi;
    Mask *mask;
    Mask *d_mask;
};
#endif // ENEMIGOS_H_INCLUDED
