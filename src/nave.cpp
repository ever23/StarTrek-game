/*
  Name: CLASE NAVES PARA EL JUEGO STR TREK
  Author: ENYERBER FRANCO
  Date: 26/11/14 12:34
  Description: IMPLEMENTACION  DE LA CLASE NAVES PARA EL JUEGO
*/
#include "../include/nave.h"
NAVES::NAVES(const char *file_nav,int ancho,int alto,int ESCU)
{
    init(file_nav, ancho, alto, ESCU);
}

NAVES::~NAVES()
{
    balas.clear();
    torpedos.clear();
    estallido1.clear();
    estallido2.clear();
    estallido3.clear();
    delete mask0;
    delete mask1;
    delete mask2;
    delete d_mask;
    delete t_mask;
}
void NAVES::init(const char *file_nav,int ancho,int alto,int ESCU)
{
    dat_nav.tx = ancho;
    dat_nav.ty = alto;
    dat_nav.vidas = 3;
    d_nave.load(file_nav);

    dat_nav.y = BORDE_Y1+20;
    dat_nav.x = 250;
    dat_nav.escudo=ESCU;

    integridad_=56;
    tick1=0;
    tick2=0;
    tick3=0;
    retraso=15;
    tem_laser=0;
    b_warp=false;
    estallido=200;

    disparo_=false;
    disparo2_=false;
    torpedo_=false;
    laser_=false;
    laser_disparado=false;


    mask0 = new Mask;
    mask0->create(d_nave[nave_bmp],0,0, ancho,alto);
    mask1 = new Mask;
    mask1->create(d_nave[nave_bmp] ,ancho,0, ancho,alto);
    mask2 = new Mask;
    mask2->create(d_nave[nave_bmp],ancho*2,0, ancho,alto);
    d_mask = new Mask;
    d_mask->create(d_nave[bala_bmp]);
    t_mask = new Mask;
    t_mask->create(d_nave[torpedo_bmp]);
}
void NAVES::reinic()
{
    integridad_=56;
    dat_nav.escudo=20;
    dat_nav.vidas=3;
}

void NAVES::pintar(BITMAP *BUFFER)
{
    integridad(BUFFER);
    warp(BUFFER);
    escudo(BUFFER);
    disparar(BUFFER);
    pintar_laser(BUFFER);
    masked_blit(d_nave[nave_bmp],BUFFER,dat_nav.tx*dat_nav.dir, 0,dat_nav.x, dat_nav.y, dat_nav.tx,dat_nav.ty);
}
void NAVES::actualizar(bool disparo,bool disparo2,bool torpedo,bool laser)
{
    mover();
    warp_log();
    actualizar_dis( disparo, disparo2, torpedo, laser);
}


void NAVES::warp(BITMAP *BUFFER)
{
    if(b_warp)
    {
        d_nave.draw_bmp(BUFFER,warp_bmp ,dat_nav.x,dat_nav.y);
       // masked_blit(d_nave[warp_bmp],BMP,0,0,dat_nav.x,dat_nav.y,dat_nav.tx,dat_nav.ty*4);
    }
}
inline void NAVES::warp_log()
{

    if(b_warp==true)
    {
        dat_nav.y-=18;
        dat_nav.x=xaux;
        dat_nav.dir=1;
        integridad_=aux_vida;
        if(dat_nav.y<-400)
        {
            b_warp=false;
            dat_nav.y = BORDE_Y1+20;
            dat_nav.x = 250;
        }
    }else
    {
        aux_vida=integridad_;
         xaux= dat_nav.x;
    }

}


inline void NAVES::mover()
{
    if(key[KEY_UP])
    {
        dat_nav.dir = 1;
        if(dat_nav.y>BORDE_Y) dat_nav.y -= 2;
    }
     if(key[KEY_DOWN])
    {
        dat_nav.dir = 1;
        if(dat_nav.y+dat_nav.ty<BORDE_Y1) dat_nav.y += 3;
    }

    if(key[KEY_RIGHT])
    {
        dat_nav.dir = 2;
        if(dat_nav.x+dat_nav.tx<BORDE_X1) dat_nav.x += 3;
    }else
    if(key[KEY_LEFT])
    {
        dat_nav.dir = 0;
        if(dat_nav.x>BORDE_X) dat_nav.x -= 3;
    }
    else dat_nav.dir = 1;
    if(dat_nav.y+dat_nav.ty>BORDE_Y1)
        dat_nav.y --;


}
void NAVES::stac_cord(DAT_NAV NAV,int X)
{
    if(dat_nav.vidas>0)
    {
        if(X>0)
            dat_nav.x=(NAV.x+NAV.tx)+15;
        else
            dat_nav.x=(NAV.x-20)-15;

        if(NAV.y+40<dat_nav.y)
        {
            dat_nav.y--;
        }
        else
            dat_nav.y=NAV.y+40;
    }
    else
    {
        dat_nav.y=0;
        dat_nav.x=0;
    }


}

inline void NAVES::integridad(BITMAP *BUFFER)
{
    pintar_int(BUFFER,0x100000,0);
    pintar_int(BUFFER,0xff1200,integridad_);
    if(integridad_<0)
    {
        integridad_=56;
        dat_nav.vidas-=1;
    }
}

inline void NAVES::pintar_int(BITMAP *BUFFER,int color,int n)
{
    for(int j=514; j<=570-n; j++)
    {
        //hline(BUFFER,19,j,71,color);

        for(int i=19; i<=71; i++)
        {
            putpixel(BUFFER,i,j,color);
        }
    }

}

void NAVES::disparar(BITMAP *BUFFER)
{

    masked_blit(d_nave[FOND_bmp],BUFFER,0,0,263,530,140,40);
    if(disparo_)
    {
        d_nave.draw_bmp(BUFFER,bala_bmp,270,635);
    }
    if(disparo2_)
    {
         d_nave.draw_bmp(BUFFER,bala_bmp,280,535);
        d_nave.draw_bmp(BUFFER,bala_bmp,280,535);
    }

    if(torpedo_)
    {
           d_nave.draw_bmp(BUFFER,torpedo_bmp,300,535);
    }
    if(laser_)
    {
        vline(BUFFER,315,550,535,0x00f0ff);
        vline(BUFFER,315,551,535,0x00f0ff);
    }
    if(laser_disparado)
        disparo_laser();
    pintar_bala(BUFFER);
    pintar_torpedo(BUFFER);
}


void NAVES::actualizar_dis(bool disparo,bool disparo2,bool torpedo,bool laser)
{
    disparo_=disparo;
    disparo2_=disparo2;
    torpedo_=torpedo;
    laser_=laser;
    if(disparo)
    {
        if(key[KEY_SPACE])
            disparos_xy();
    }
    if(disparo2)
    {
        if(key[KEY_SPACE])
            disparos_2xy();
    }
    if(torpedo)
    {
        if(key[KEY_M])
            torpedo_xy();
    }
    if(laser)
    {
        if(key[KEY_N])
        {
            laser_disparado=true;
        }

    }
    pintar_bala_log();
    pintar_torpedo_log();
}

inline void NAVES::disparos_xy()
{
    if(tick1==0)
    {
        disp bala;
        bala.x=dat_nav.x+(dat_nav.tx/2);
        bala.y=dat_nav.y;
        bala.inp=1;
        balas.push_back(bala);
    }
    tick1++;
    if(tick1>retraso)tick1=0;
}

inline void NAVES::disparos_2xy()
{
    if(tick2==0)
    {
        disp bala;
        bala.x=dat_nav.x+((dat_nav.tx/10)*1);
        bala.y=dat_nav.y+26;
        bala.inp=1;
        balas.push_back(bala);
        bala.x=dat_nav.x+((dat_nav.tx/10)*8.3);
        bala.y=dat_nav.y+26;
        bala.inp=1;
        balas.push_back(bala);
    }
    tick2++;
    if(tick2>retraso)tick2=0;
}

void NAVES::pintar_bala(BITMAP *BUFFER)
{
    vector <disp>::iterator ibala;
    for( ibala = balas.begin() ; ibala != balas.end(); ibala++)
    {
          d_nave.draw_bmp(BUFFER,bala_bmp,ibala->x,ibala->y);
    }
}
inline void NAVES::pintar_bala_log()
{
    vector <disp>::iterator ibala;
    ibala=balas.begin();
    for(int i=0; i<int(balas.size()); i++,ibala++)
    {
        if(ibala->y>10)
        {
            ibala->y-=3;
        }
        else
        {
            ibala=balas.erase(ibala);

        }
    }
    ibala=balas.end();
}



void NAVES::pintar_torpedo(BITMAP *BUFFER)
{
    vector <disp>::iterator itorpedo;
    for( itorpedo = torpedos.begin() ; itorpedo != torpedos.end(); itorpedo++)
    {
           d_nave.draw_bmp(BUFFER,torpedo_bmp,itorpedo->x,itorpedo->y);
    }
    itorpedo = torpedos.end();

    for( itorpedo = estallido1.begin() ; itorpedo != estallido1.end(); itorpedo++)
    {
            d_nave.draw_bmp(BUFFER,bala_bmp,itorpedo->x,itorpedo->y);
    }
    itorpedo = estallido1.end();


    for( itorpedo = estallido2.begin() ; itorpedo != estallido2.end(); itorpedo++)
    {

 d_nave.draw_bmp(BUFFER,bala_bmp,itorpedo->x,itorpedo->y);

    }
    itorpedo = estallido2.end();

    for( itorpedo = estallido3.begin() ; itorpedo != estallido3.end(); itorpedo++)
    {

        d_nave.draw_bmp(BUFFER,bala_bmp,itorpedo->x,itorpedo->y);

    }
    itorpedo = estallido3.end();

}

void NAVES::pintar_torpedo_log()
{
    vector <disp>::iterator itorpedo;
    itorpedo=torpedos.begin();
    for(int i=0; i<int(torpedos.size()); i++,itorpedo++)
    {
        if(itorpedo->y>estallido)
        {
            itorpedo->y-=3;
        }
        else
        {
            estallar_torpedo(itorpedo->x,itorpedo->y);
            itorpedo=torpedos.erase(itorpedo);
        }
    }
    itorpedo=torpedos.end();

    vector <disp>::iterator iest;
    iest=estallido1.begin();
    for(int i=0; i<int(estallido1.size()); i++,iest++)
    {
        if( (iest->x<580 &&  iest->x>10) &&  iest->y>10)
        {
            iest->x+=2;
            iest->y-=2;
        }
        else
        {
            iest=estallido1.erase(iest);
        }
    }
    iest=estallido1.end();

    iest=estallido2.begin();
    for(int i=0; i<int(estallido2.size()); i++,iest++)
    {
        if( iest->y>10)
        {
            iest->y-=2;
        }
        else
        {
            iest=estallido2.erase(iest);
        }
    }
    iest=estallido2.end();

    iest=estallido3.begin();
    for(int i=0; i<int(estallido3.size()); i++,iest++)
    {
        if( (iest->x<580 &&  iest->x>10) &&  iest->y>10)
        {
            iest->x-=2;
            iest->y-=2;
        }
        else
        {
            iest=estallido3.erase(iest);
        }
    }
    iest=estallido3.end();


}
void NAVES::torpedo_xy()
{
    if(tick3==0)
    {
        disp bala;
        bala.x=dat_nav.x+((dat_nav.tx/10)*1);
        bala.y=dat_nav.y+26;
        bala.inp=3;
        torpedos.push_back(bala);
        bala.x=dat_nav.x+((dat_nav.tx/10)*8.3);
        bala.y=dat_nav.y+26;
        bala.inp=3;
        torpedos.push_back(bala);
    }
    tick3++;
    if(tick3>70)tick3=0;
}

void NAVES::estallar_torpedo(int &x_s,int &y_s)
{
    if(y_s<estallido)
    {
        disp bala;
        bala.x=x_s;
        bala.y=y_s;
        bala.inp=1;
        estallido1.push_back(bala);
        estallido2.push_back(bala);
        estallido3.push_back(bala);
    }
}
void NAVES::pintar_laser(BITMAP *BUFFER)
{
    vline(BUFFER,laser.x,laser.y,laser.inp,0x08ceff);
}


void NAVES::disparo_laser()
{
    if(tem_laser<30)
    {
        laser.x=dat_nav.x+(dat_nav.tx/2);
        laser.y=dat_nav.y;
        laser.inp=0;
    }
    else
    {
         laser.x=0;
        laser.y=0;
    }
    tem_laser++;
    if(tem_laser>100)
    {
        tem_laser=0;
        laser_disparado=false;
    }

}


void NAVES::escudo(BITMAP *BUFFER)
{
    for(int j=25; j<=30; j++)
    {
        vline(BUFFER,j,512,513-dat_nav.escudo,0x08ceff);
    }

}
void NAVES::dec_integridad(int n)
{
    integridad_-=n;
}
void NAVES::dec_iescudo(int n)
{
    dat_nav.escudo-=n;
}

vector<disp> *NAVES::get_balas()
{
    return &balas;
}
vector<disp> *NAVES::get_torpedos()
{
    return &torpedos;
}
vector<disp> *NAVES::get_estallido1()
{
    return &estallido1;
}
vector<disp> *NAVES::get_estallido2()
{
    return &estallido2;
}
vector<disp> *NAVES::get_estallido3()
{
    return &estallido3;
}
DAT_NAV NAVES::get_nav()
{
    return dat_nav;
}

Mask *NAVES::get_mask()
{
    switch (dat_nav.dir)
    {
    case 0:
        return mask0;
    case 1:
        return mask1;
    case 2:
        return mask2;
    }
    return mask1;
}

Mask *NAVES::get_dmask()
{
    return d_mask;
}
Mask *NAVES::get_tmask()
{
    return t_mask;
}
