/*
  Name: CLASE NAVES PARA EL JUEGO STR TREK
  Author: ENYERBER FRANCO
  Date: 26/11/14 12:34
  Description: DEFINICION DE LA CLASE NAVES PARA EL JUEGO
*/
#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED
#include <allegro.h>
#include <vector>
#include "mask.h"
#include "disparos.h"
#include "data_grabber.h"
#define nave_bmp 0
#define bala_bmp 1
#define torpedo_bmp 2
#define warp_bmp 3
#define FOND_bmp 4
using namespace std;

struct DAT_NAV
{
    int x,y;
    int dir;
    int tx,ty;
    int vidas;
    int escudo;
};
class NAVES
{
public:
    NAVES() {}
    NAVES(const char *,int ,int ,int );
    ~NAVES();
    void init(const char *,int ,int ,int );
    void pintar(BITMAP *);
    void actualizar(bool disparo=false,bool disparo2=false,bool torpedo=false,bool laser=false);
    void warp_act()
    {
        b_warp=true;
    }
    bool chek_warp()
    {
        return b_warp;
    }
    vector<disp> *get_balas();
    vector<disp> *get_torpedos();
    vector<disp> *get_estallido1();
    vector<disp> *get_estallido2();
    vector<disp> *get_estallido3();
    disp *get_laser()
    {
        return &laser;
    }
    int get_vida()
    {
        return dat_nav.vidas;
    }
    DAT_NAV get_nav();
    int get_escudo();
    void dec_integridad(int);
    void dec_iescudo(int);
    void reinic();
    Mask *get_mask();
    Mask *get_dmask();
    Mask *get_tmask();
    void stac_cord(DAT_NAV ,int );
private:
    void disparar(BITMAP *);
    void actualizar_dis(bool ,bool ,bool ,bool );
    void integridad(BITMAP *);
    void escudo(BITMAP *);
    void warp(BITMAP *);
    void warp_log();
    void disparo_laser();
    void pintar_laser(BITMAP *);
    void disparos_xy();
    void disparos_2xy();
    void torpedo_xy();
    void pintar_bala(BITMAP *);
    void pintar_bala_log();
    void pintar_torpedo(BITMAP *);
    void  pintar_torpedo_log();
    void estallar_torpedo(int &,int &);
    DATA_GRABBER d_nave;
    void mover();
    void pintar_int(BITMAP *, int , int );
    int integridad_;
    int laser_disparado;
    int tick1,tick2,tick3,retraso;
    int tem_laser;
    int estallido;
    int xaux;
    int aux_vida;
    bool b_warp;
    bool disparo_;
    bool disparo2_;
    bool torpedo_;
    bool laser_;
    DAT_NAV dat_nav;
    disp laser;
    vector<disp> balas;
    vector<disp> torpedos;
    vector<disp> estallido1;
    vector<disp> estallido2;
    vector<disp> estallido3;
    Mask *mask0;
    Mask *mask1;
    Mask *mask2;
    Mask *d_mask;
    Mask *t_mask;
};
#endif // NAVE_H_INCLUDED
