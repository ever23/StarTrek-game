/*
  Name: CLASE INICIAR PARA EL JUEGO STR TREK
  Author: ENYERBER FRANCO
  Date: 26/11/14 12:34
  Description: IMPLEMENTACION  DE LA CLASE INICIAR PARA EL JUEGO
*/
#include "../include/inicia.h"
#include <iostream_alleg.h>
#include <allegttf.h>
#include <iostream>
using namespace all;
using namespace std;
INICIAR::INICIAR()
{
    filename="data.dtg";
    read_dtg();
}
INICIAR::~INICIAR()
{
    iosall.~ALLE_STREAM();
}

void INICIAR::cargar_datafile(const char *NAME_DATAFILE)
{
    grab.load(NAME_DATAFILE);
    font1.load_ttf("archivos/fuente.ttf", 8, ALLEGTTF_NOSMOOTH);
    font2.load_ttf("archivos/RCorp.ttf", 20, ALLEGTTF_REALSMOOTH);
    mouse.init(grab[cursor_]);
    buffer.create();


}

void INICIAR::inicio()
{
    int i=0;
    grab.draw_bmp(buffer,inicio_);
    while(i<435 && !game_over())
    {
        buffer.blitbmp(grab[barra_],0,0,85+i,432,10,10);
        buffer.mask_udapte();
        i++;
    }
    ini_game=0;

}

void INICIAR::menu_principal()
{
    iosall<<BMP(buffer);
    while(!ini_game && !game_over())
    {
        grab.draw_bmp(buffer,menu_);

        if(mouse.chek(135,192,440,253))
        {
            grab.draw_bmp(buffer,JUEGAR_L_HOVER,135,192);
            if(mouse.b_izq())
            {
                rest(200);
                jugador();
            }
        }
        else
            grab.draw_bmp(buffer,JUGAR_L,135,191);


        if(mouse.chek(135,275,440,330))
        {
            grab.draw_bmp(buffer,AYUDA_HOVER,135,275);
            if(mouse.b_izq())
            {
                if(!ini_game)
                    ayuda_();
            }
        }
        else
            grab.draw_bmp(buffer,AYUDA_,135,274);

        if(mouse.chek(135,360,415,408))
        {
            grab.draw_bmp(buffer,SALIR_HOVER,135,360);
            if(mouse.b_izq())
            {
                exit();
            }
        }
        else
            grab.draw_bmp(buffer,SALIR_,135,359);

        mouse.draw(buffer);
        if(!game_over() && !ini_game)
        {
            buffer.mask_udapte();
            rest(3);
        }
    }
}

void INICIAR::ayuda_()
{
    while(!game_over())
    {
        if(mouse.chek(135,169,440,212))
        {
            buffer.blitbmp(grab[info_ayuda],600,0,0,0,screen_w(),screen_h());
            if(mouse.b_izq())
            {
                break;
            }
        }
        else
            buffer.blitbmp(grab[info_ayuda],0,0,0,0,screen_w(),screen_h());

        mouse.draw(buffer);
        buffer.mask_udapte();
        rest(3);
    }
    for(int i=0; i<15; i++)
        rest(5);
}
void INICIAR::jugador()
{
    while(!game_over() && !ini_game)
    {
        iosall.cargar_fuente(font2);
        grab.draw_bmp(buffer,menu_jugadores_);
        if(mouse.chek(54,415,118,441))
        {
            iosall.setcolor(0xd8f322);
            if(mouse.b_izq())
            {
                break;
            }
        }
        else
            iosall.setcolor(0x226aac);
        iosall<<XY(54,414)<< "ATRAS";

        if(mouse.chek(480,415,544,441))
        {
            iosall.setcolor(0xd8f322);
            if(mouse.b_izq())
            {
                read_key_();
            }
        }
        else
            iosall.setcolor(0x226aac);
        iosall<<XY(480,414)<< "NUEVO";

        pintar_dtg(buffer);

        mouse.draw(buffer);
        if(!game_over())
        {
            buffer.mask_udapte();
            rest(3);
        }
    }
}

void INICIAR::read_key_()
{
    iosall.puntero_tex(0xf9290e);
    iosall.set_stringbuff("JUGADOR");
    iosall<<LMT(240);
    clear_keybuf();
    while(!game_over() && !ini_game && !key[KEY_ENTER])
    {
        grab.draw_bmp(buffer,get_gamer);
        iosall.cargar_fuente(font2);
        if(mouse.chek(130,265,194,292))
        {
            iosall.setcolor(0xd8f322);
            if(mouse.b_izq())
                break;
        }
        else
            iosall.setcolor(0x226aac);
        iosall<<XY(130,264)<< "ATRAS";
        if(mouse.chek(375,265,439,295)  )
        {
            iosall.setcolor(0xd8f322);
            if(mouse.b_izq())
                ini_game=1;
        }
        else
            iosall.setcolor(0x226aac);
        iosall<<XY(375,265)<< "JUGAR";

        iosall.setcolor(0xfafafb);
        iosall.cargar_fuente(font1);
        iosall<<XY(165,195)<<GETKEY;
        mouse.draw(buffer);
        buffer.mask_udapte();
        rest(1);
    }
    iosall.get_var(gamer.name);
    gamer.puntos=0;
    gamer.nivel=0;
    iosall<<CLEARBUF;

}
void INICIAR::pintar_dtg(BITMAP *BUFFER)
{

    vector<data_game>::iterator igame=datos.begin();
    iosall.iostream_alleg_init(168,218,0xfafafb,-1);
    iosall.cargar_fuente(font1);
    int y=0;
    iosall<<" NOMBRE "<<XY(340,218)<< "NIVEL "<<XY(400,218)<< "PUNTOS " ;
    if(!datos.empty())
        for(int i=0; i<int(datos.size()); i++,igame++)
        {
            y=230+(i*(iosall.get_ht()+2));
            if(mouse.chek(168, y ,448,y+iosall.get_ht() +2 ))
            {
                iosall.setcolor(0xd2e93a);
                if(mouse.b_izq())
                {
                    gamer=*igame;
                    igame=datos.erase(igame);
                    igame=datos.end();
                    ini_game=1;
                    break;
                }
            }
            else
                iosall.setcolor(0xfafafb);
            iosall<<XY(168,y)<<igame->name<<XY(342,y);

            if(igame->nivel<10)
                iosall<<igame->nivel;
            else
                iosall<<"GANADOR";

            iosall<<XY(402,y)<<igame->puntos;
            iosall<<ENDL2;
        }

}

void INICIAR::read_dtg()
{
    cout<< "cargando "<<filename<< "...."<<endl<<endl;
    fentrada.open(filename,ios::in | ios::binary);
    data_game game;
    datos.clear();
    if(!fentrada.fail())
    {
        cout<< "cargando..."<<endl<<endl;
        while(!fentrada.fail())
        {
            fentrada.read(reinterpret_cast<char *> (&game),sizeof(data_game));
            if(!fentrada.fail())
            {
                datos.push_back(game);
                cout<<game.name<< " " <<game.puntos<< " "<<game.nivel<<endl;;
            }
        }
    }
    fentrada.close();
}

void INICIAR::savegame(int p,int n)
{
    gamer.puntos=p;
    gamer.nivel=n;
    datos.push_back(gamer);
}

void INICIAR::guardar_dtg()
{
    data_game game;
    vector<data_game>::iterator igame=datos.begin();
    fsalida.open(filename,ios::out | ios::binary |ios::trunc);
    cout<< "guardando "<<filename<< "..."<<endl<<endl;
    for(int i=0; i<int(datos.size()); i++,igame++)
    {
        game=*igame;
        fsalida.write(reinterpret_cast<char *> (&game),sizeof(data_game));
        cout<<game.name<< " " <<game.puntos<< " "<<game.nivel<<endl;;
    }
    fsalida.close();
}

int INICIAR::get_nivel()
{
    return gamer.nivel;
}
int INICIAR::get_pts()
{
    return gamer.puntos;
}
