/*
  Name: CLASE ENEMIGOS PARA EL JUEGO STAR TREK
  Author: ENYERBER FRANCO
  Date: 26/11/14 12:34
  Description: IMPLEMENTACION  DE LA CLASE ENEMIGOS PARA EL JUEGO
*/
#include "../include/enemigos.h"


ENEMIGOS::ENEMIGOS(const char *FILE_ENEMI,int N_ENEMIGOS,int TIPO,int PODER,int RESISTENCIA,int ANCHO,int ALTO)
{
   init(FILE_ENEMI, N_ENEMIGOS, TIPO, PODER, RESISTENCIA, ANCHO, ALTO);
}

ENEMIGOS::~ENEMIGOS()
{
    destroy();
}
void ENEMIGOS::destroy()
{
    delete mask;
    delete d_mask;
    enemigos.clear();
}
void ENEMIGOS::init(const char *FILE_ENEMI,int N_ENEMIGOS,int TIPO,int PODER,int RESISTENCIA,int ANCHO,int ALTO)
{
    d_enemi.load(FILE_ENEMI);
    tipo=TIPO;
    poder=PODER;
    vida=RESISTENCIA;
    min_vcd=2;
    tx=ANCHO;
    ty=ALTO;
    cantidad(N_ENEMIGOS);
    mask = new Mask;
    mask->create(d_enemi[enemi_bmp],0,0,ANCHO,ALTO);
    d_mask = new Mask;
    d_mask->create(d_enemi[balae_bmp]);
}
void ENEMIGOS::cantidad(int n)
{
    enemigos.clear();
    for(int i=0; i<n; i++)
    {
        ene enemi;
        enemi.x=(rand()%500)+25;
        enemi.y=(rand()%400)-900;
        enemi.img_x=0;
        enemi.vida=vida;
        enemi.dir=1;
        enemi.vcd=(rand()%min_vcd)+2;
        enemi.tx=tx;
        enemi.ty=ty;
        enemi.imp=0;
        enemigos.push_back(enemi);
    }
    disparos.clear();
    laser.clear();
}

void ENEMIGOS::pinta_enemigo(BITMAP *BUFF)
{
    vector<ene>::iterator iene;
    for(iene=enemigos.begin() ; iene != enemigos.end(); iene++)
    {
        masked_blit(d_enemi[enemi_bmp],BUFF,iene->img_x*iene->tx,0,iene->x,iene->y,iene->tx,iene->ty);
    }
    disparo(BUFF);
}
void ENEMIGOS::actualizar(bool dispara)
{
    vector<ene>::iterator iene;
    iene=enemigos.begin();
    for(int i=0; i<int(enemigos.size()); i++,iene++ )
    {
        if(iene->y>600)
        {
            reiniciar(&(*iene));
        }
        if(iene->vida<0)
        {
            iene->imp++;
            iene->img_x=1;
            if(iene->imp >10)
            reiniciar(&(*iene));
        }
        iene->y+=iene->vcd;
        iene->x1=iene->x+iene->tx;
        iene->y1=iene->y+iene->ty;

    }
    if(dispara==1)disparo_log();
}

void ENEMIGOS::reiniciar(ene *enei)
{
    enei->vida=vida;
    if(tipo==1)
    {
        enei->x=(rand()%500)+25;
        enei->y=-50;
        enei->vcd=(rand()%min_vcd)+2;
        enei->imp=0;
        enei->img_x=0;
        enei->vida=vida;
    }
    else if(tipo==2)
    {
        enei->x=(rand()%515)+25;
        enei->y=-50;
        enei->dir=1;
        enei->vcd=(rand()%min_vcd)+2;
        enei->imp=0;
        enei->img_x=0;
        enei->vida=vida;
    }
}
void  ENEMIGOS::set_min_vcd(int v)
{
    min_vcd=v;
}
void ENEMIGOS::actualizar_big()
{
    vector<ene>::iterator iene;
    iene=enemigos.begin();
    for(int i=0; i<int(enemigos.size()); i++,iene++ )
    {
        if( iene->vida<=0)
        {
            iene->vida=0;
             iene->imp++;
            if(iene->img_x==0)
             iene->img_x=1;
            if(iene->img_x==2)
             iene->img_x=3;
            if(iene->imp >10)
            reiniciar(&(*iene));
        }
        mov_aleatorio(&(*iene));
    }
    iene=enemigos.end();
    big_disparo_log();

}

void ENEMIGOS::mov_aleatorio(ene *iene)
{
    int casos=8,borde_y1=200;
    switch(iene->dir)
    {
    case 1:
    {
        iene->y+=iene->vcd;
        if( iene->y>borde_y1)
            iene->dir=(rand()%casos)+1;
    }

    break;

    case 2:
    {
        iene->y-=iene->vcd;
        if(iene->y<BORDE_Y)
            iene->dir=(rand()%casos)+1;
    }
    break;

    case 3:
    {
        iene->x-=iene->vcd;
        if(iene->x+50<BORDE_X)
        {
            iene->dir=(rand()%casos)+1;
            while(iene->dir==1 || iene->dir==2)
            {
                iene->dir=(rand()%casos)+1;
            }
        }
        iene->img_x=2;
    }
    break;

    case 4:
    {
        iene->x+=iene->vcd;
        if(iene->x+20>BORDE_X1)
        {
            iene->dir=(rand()%casos)+1;
            while(iene->dir==1 || iene->dir==2)
            {
                iene->dir=(rand()%casos)+1;
            }

        }
        iene->img_x=0;
    }
    break;

    case 5:
    {
        iene->x+=iene->vcd;
        iene->y+=iene->vcd;
        if( iene->x>BORDE_X1 || iene->y>borde_y1)
            iene->dir=(rand()%casos)+1;
        iene->img_x=0;

    }
    break;

    case 6:
    {
        iene->x-=iene->vcd;
        iene->y-=iene->vcd;
        if( iene->x<BORDE_X || iene->y>BORDE_Y)
            iene->dir=(rand()%casos)+1;
        iene->img_x=2;
    }
    break;
    case 7:
    {
        iene->x+=iene->vcd;
        iene->y-=iene->vcd;
        if(iene->x>BORDE_X1 || iene->y<BORDE_Y)
            iene->dir=(rand()%casos)+1;
        iene->img_x=0;
    }
    break;
    case 8:
    {
        iene->x-=iene->vcd;
        iene->y+=iene->vcd;
        if(iene->x<BORDE_X || iene->y>borde_y1)
            iene->dir=(rand()%casos)+1;
        iene->img_x=2;
    }
    break;
    }
}

void ENEMIGOS::set_vcd(int n)
{
    vector<ene>::iterator iene;
    for(iene=enemigos.begin() ; iene != enemigos.end(); iene++)
    {
        iene->vcd=n;
    }
}

void ENEMIGOS::disparo(BITMAP *BUFF)
{
    vector<disp>::iterator idisp=disparos.begin();
    for(int i=0; i< int(disparos.size());i++, idisp++)
    {
         d_enemi.draw_bmp(BUFF,balae_bmp,idisp->x,idisp->y);
    }
}



void ENEMIGOS::disparo_log()
{

    vector<ene>::iterator iene;
    disp dispar;
    int i=0;

    for( iene = enemigos.begin() ; iene != enemigos.end() ; iene++,i++)
    {
        if(((rand()%int(enemigos.size()))==i)  && (iene->dis>80+(rand()%40)) )
        {
                dispar.x=iene->x+(iene->tx/2);
                dispar.y=iene->y+iene->ty;
                dispar.vcd=iene->vcd*2;
                disparos.push_back(dispar);
                iene->dis=0;
        }
        iene->dis++;
    }


    vector<disp>::iterator idisp;
    idisp=disparos.begin();
    for(int i=0;i<int(disparos.size());i++,idisp++)
    {
        idisp->y+=idisp->vcd;
        if(idisp->y>600)
        {
            idisp=disparos.erase(idisp);
        }
    }


}

void ENEMIGOS::big_disparo_log()
{


     vector<ene>::iterator iene;
    disp dispar;
    int i=0;
    for( iene = enemigos.begin() ; iene != enemigos.end() ; iene++,i++)
    {
        if((rand()%(int(enemigos.size())*50) )==i)
        {
            dispar.x=iene->x+50;
            dispar.y=iene->y+iene->ty;
            dispar.vcd=iene->vcd+3;
            disparos.push_back(dispar);
            dispar.x=iene->x+150;
            dispar.y=iene->y+iene->ty;
            dispar.vcd=iene->vcd+3;
            disparos.push_back(dispar);
            dispar.x=iene->x+100;
            dispar.y=iene->y+iene->ty;
            dispar.vcd=iene->vcd+3;
            disparos.push_back(dispar);

        }

    }
    vector<disp>::iterator idisp;
    idisp=disparos.begin();
    for(int i=0;i<int(disparos.size());i++,idisp++)
    {
        idisp->y+=idisp->vcd;
        if(idisp->y>600)
        {
            idisp=disparos.erase(idisp);
        }
    }
}

void ENEMIGOS::disparo_laser(BITMAP *BUFF)
{
    int i=0;
    disp laser_tem;
    for(vector<ene>::iterator iene = enemigos.begin() ; iene != enemigos.end() ; iene++,i++)
    {
        if((rand()%(int(enemigos.size())*100) )==i)
        {
           laser_tem.x=iene->x+(iene->tx/2);
           laser_tem.y=iene->y+iene->ty-20;
           laser_tem.inp=600;
           laser_tem.vcd=0;
           laser.push_back(laser_tem);
        }

    }
     vector<disp>::iterator idisp = laser.begin();
     i=0;
     for(int i=0 ; i<int(laser.size()) ; idisp++,i++)
     {
         for(int j=0;j<4;j++)
         vline(BUFF,idisp->x+j,idisp->y,idisp->inp,0x08ceff);
         idisp->vcd++;
         if(idisp->vcd>5)
         {
             idisp=laser.erase(idisp);
         }
     }
     idisp = laser.end();


}
void ENEMIGOS::dec_vida(ene *enemi,int n)
{
    enemi->vida-=n;
}
vector <ene> *ENEMIGOS::get_enemigos()
{
    return &enemigos;
}

vector <disp> *ENEMIGOS::get_disp()
{
    return &disparos;
}
vector <disp> *ENEMIGOS::get_laser()
{
    return &laser;
}
int ENEMIGOS::power()
{
    return poder;
}

