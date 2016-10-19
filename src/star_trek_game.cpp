#include "../include/star_trek_game.h"
//ENEMIGOS
#define enemigo1    0
#define enemigo2    1
#define enemigo3    2
#define big_enemi1  3
#define big_enemi2  4
//NAVES
#define nave1       0
#define nave2       1
#define nave3       2
#define satelite1   3
#define satelite2   4
#include <iostream>
#include <allegttf.h>
#include <iostream_alleg.h>
using namespace all;
STAR_TREK_GAME::STAR_TREK_GAME()
{

}
STAR_TREK_GAME::~STAR_TREK_GAME()
{
    delete fondo;
    delete recompenza;
    delete impacto;
    vector<ENEMIGOS*>::iterator inte=enemigos.begin();
    for( int i=0; i<int(enemigos.size()) ; i++, inte++)
        delete *inte;
    inte=enemigos.end();
    vector<NAVES*>::iterator intn=naves.begin();
    for(int i=0; i<int(naves.size()); i++, intn++)
        delete *intn;
    intn=naves.end();

    delete time;
    enemigos.clear();
    naves.clear();
}
void STAR_TREK_GAME::init()
{
    font1.load_ttf("archivos/RCorp.ttf", 20, ALLEGTTF_REALSMOOTH);
    ENEMIGOS *enem1;
    NAVES *nav;

    fondo = new ESCENARIO("archivos/escenario");
    recompenza = new RECOMPENZAS("archivos/recompenza","archivos/nivel");

    enem1 = new ENEMIGOS("archivos/enemigo_1",4,1,1,0,50,88);
    enemigos.push_back(enem1);
    enem1 = new ENEMIGOS("archivos/enemigo_2",4,1,1,0,50,88);
    enemigos.push_back(enem1);
    enem1 = new ENEMIGOS("archivos/enemigo_3",4,1,1,0,50,88);
    enemigos.push_back(enem1);
    enem1 = new ENEMIGOS("archivos/big_enenemi1",1,2,3,100,150,50);
    enemigos.push_back(enem1);
    enem1 = new ENEMIGOS("archivos/big_enenemi2",1,2,3,200,200,60);
    enemigos.push_back(enem1);

    nav = new NAVES("archivos/nave_1",50,60,20);
    naves.push_back(nav);
    nav = new NAVES("archivos/nave_2",63,86,50);
    naves.push_back(nav);
    nav = new NAVES("archivos/nave_3",64,107,200);
    naves.push_back(nav);
    nav = new NAVES("archivos/satelite",22,28,0);
    naves.push_back(nav);
    nav = new NAVES("archivos/satelite",22,28,0);
    naves.push_back(nav);

    time = new TIME(7);
    impacto = new IMPACTOS;

    BMPS.load("archivos/star_trek_game");

    nivel=0;
    savegame=false;
    jugado=0;
    buffer.create();
    mouse.init(BMPS[1]);
    menu_p=false;
}


void STAR_TREK_GAME::main()
{
    jugado=false;
    menu_p=false;
    nivel0();
    nivel1();
    nivel2();
    nivel3();
    reto1();
    nivel4();
    nivel5();
    nivel6();
    reto2();
    nivel7();
    nivel8();
    nivel9();
    nivel10();
    if(recompenza->get_nivel()>10)
        creditos();
    savegame=save_game();
    if(recompenza->fin_de_juego())
    {
        savegame=true;
    }
}
int STAR_TREK_GAME::get_pts()
{
    return recompenza->get_pts();
}
int STAR_TREK_GAME::get_nivel()
{
    return recompenza->get_nivel();
}
void STAR_TREK_GAME::sets(int P,int N)
{
    recompenza->set_nivel(N);
    recompenza->set_pts(P);
    impacto->set_pts(P);
}
bool STAR_TREK_GAME::chek_save()
{
    return savegame;
}


void STAR_TREK_GAME::pausa()
{
    if(key[KEY_ESC])
    {
        BUFFER bmpaux;
        bmpaux.create();
        bmpaux.blitbmp(screen,0,0,0,0,screen_w(),screen_h());
        int x=138,y=142;
        while( !game_over() && !menu_p)
        {
            buffer.drawbmp(bmpaux);
            if(!mouse.chek(138,142,438,442))
            {
                if(mouse.b_izq())
                    break;
            }

            if(mouse.chek(188,218,383,278))
            {
                buffer.blitbmp(BMPS[0],300,0,x,y,300,300);
                if(mouse.b_izq())
                {
                    break;
                }
            }
            else if(mouse.chek(160,280,419,335))
            {
                buffer.blitbmp(BMPS[0],600,0,x,y,300,300);
                if(mouse.b_izq())
                {
                    menu_p=true;
                }
            }
            else if(mouse.chek(190,350,363,390))
            {
                buffer.blitbmp(BMPS[0],900,0,x,y,300,300);
                if(mouse_b & 1)
                {
                    exit();
                }
            }
            else buffer.blitbmp(BMPS[0],0,0,x,y,300,300);
            mouse.draw(buffer);

            buffer.mask_udapte();
            rest(3);
        }
    }
}

bool STAR_TREK_GAME::save_game()
{

    if((game_over() || menu_p) && jugado )
    {
        BUFFER BUFFER1;
        BUFFER1.create();
        BUFFER1.blitbmp(screen,0,0,0,0,screen_w(),screen_h());
        clear_to_color(buffer ,0xff00ff);
        iosall.cargar_fuente(font1);
        iosall<<BMP(buffer);
        while(1)
        {
            buffer.drawbmp(BMPS[2] ,138,142);
            if(mouse.chek(205,322,252,350))
            {
                iosall.setcolor(0xd8f322);
                if(mouse.b_izq())
                {
                    return false;
                }
            }
            else
                iosall.setcolor(0x226aac);
            iosall<<XY(205,322)<< "NO";
            if(mouse.chek(350,323,387,350))
            {
                iosall.setcolor(0xd8f322);
                if(mouse.b_izq())
                {
                    return true;
                }
            }
            else
                iosall.setcolor(0x226aac);
            iosall<<XY(350,323)<< "SI";



            mouse.draw(buffer);
            buffer.mask_udapte();
            buffer.drawbmp(BUFFER1);
            rest(5);
        }

    }
    return false;
}


void STAR_TREK_GAME::nivel0()
{
    if(recompenza->get_nivel()==0)
    {


        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo1]->cantidad(12);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==0 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave1]->actualizar();

                enemigos[enemigo1]->actualizar(false);

                impacto->impactos(naves[nave1],1,enemigos[enemigo1]);

                recompenza->sets(naves[nave1]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[enemigo1]->pinta_enemigo(buffer);

                naves[nave1]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                buffer.update();
                pausa();
                rest(1);
            }
            if(time->get_seg()>=25)
            {
                n++;
                if(n==1)
                    naves[nave1]->warp_act();
                if(!naves[nave1]->chek_warp())
                    recompenza->pasar_niveles();
            }
        }
    }
}

void STAR_TREK_GAME::nivel1()
{
    if(recompenza->get_nivel()==1)
    {
        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo1]->cantidad(7);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==1 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave1]->actualizar(1);

                enemigos[enemigo1]->actualizar(1);

                impacto->impactos(naves[nave1],1,enemigos[enemigo1]);

                recompenza->sets(naves[nave1]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[enemigo1]->pinta_enemigo(buffer);
                naves[nave1]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);
                buffer.update();

                pausa();
                rest(1);
            }
            if(time->get_seg()>=70)
            {
                n++;
                if(n==1)
                    naves[nave1]->warp_act();
                if(!naves[nave1]->chek_warp())
                    recompenza->pasar_niveles();
            }
        }
    }

}

void STAR_TREK_GAME::nivel2()
{
    if(recompenza->get_nivel()==2)
    {
        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo1]->cantidad(10);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==2 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave1]->actualizar(1);

                enemigos[enemigo1]->actualizar();

                impacto->impactos(naves[nave1],1,enemigos[enemigo1]);

                recompenza->sets(naves[nave1]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[enemigo1]->pinta_enemigo(buffer);
                naves[nave1]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                buffer.update();
                pausa();
                rest(1);
            }
            if(time->get_seg()>=70)
            {
                n++;
                if(n==1)
                    naves[nave1]->warp_act();
                if(!naves[nave1]->chek_warp())
                    recompenza->pasar_niveles();
            }
        }
    }

}

void STAR_TREK_GAME::nivel3()
{
    if(recompenza->get_nivel()==3)
    {
        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo1]->cantidad(4);
        enemigos[enemigo2]->cantidad(3);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==3 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave1]->actualizar(0,1);

                enemigos[enemigo1]->actualizar(1);
                enemigos[enemigo2]->actualizar(1);

                impacto->impactos(naves[nave1],2,enemigos[enemigo1],enemigos[enemigo2]);

                recompenza->sets(naves[nave1]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[enemigo1]->pinta_enemigo(buffer);
                enemigos[enemigo2]->pinta_enemigo(buffer);

                naves[nave1]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                buffer.update();
                pausa();
                rest(1);
            }
            if(time->get_seg()>=75)
            {
                n++;
                if(n==1)
                    naves[nave1]->warp_act();
                if(!naves[nave1]->chek_warp())
                    break;
            }
        }
    }

}

void STAR_TREK_GAME::reto1()
{
    if(recompenza->get_nivel()==3)
    {
        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        bool  enemi_deat=false;
        enemigos[big_enemi1]->cantidad(1);

        while(!game_over()  && !menu_p && recompenza->get_nivel()==3 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {

                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave1]->actualizar(0,1);

                if(enemi_deat==false)
                    enemigos[big_enemi1]->actualizar_big();
                enemigos[big_enemi1]->set_vcd(1);

                impacto->impactos(naves[nave1],1,enemigos[big_enemi1]);

                recompenza->sets(naves[nave1]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {

                fondo->pintar_nuve(buffer);

                if(enemi_deat==false)
                {
                    enemigos[big_enemi1]->disparo_laser(buffer);
                    enemigos[big_enemi1]->pinta_enemigo(buffer);
                }

                naves[nave1]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                for(int i=0; i<4; i++)
                    hline(buffer,115,510+i,114+enemigos[big_enemi1]->get_vida(1),0xf9290e);

                buffer.update();
                pausa();
                rest(1);

            }
            if(enemigos[big_enemi1]->get_vida(1)<=0 || enemi_deat==true)
            {
                enemi_deat=true;
                n++;
                if(n>20)
                {
                    if(n==21)
                        naves[nave1]->warp_act();
                    if(!naves[nave1]->chek_warp())
                    {
                        recompenza->pasar_niveles();
                        naves[nave1]->reinic();
                    }
                }
            }
        }
    }

}

void STAR_TREK_GAME::nivel4()
{
    if(recompenza->get_nivel()==4)
    {
        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo1]->cantidad(4);
        enemigos[enemigo2]->cantidad(4);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==4 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave2]->actualizar(0,1);

                enemigos[enemigo1]->actualizar();
                enemigos[enemigo2]->actualizar();

                impacto->impactos(naves[nave2],2,enemigos[enemigo1],enemigos[enemigo2]);

                recompenza->sets(naves[nave2]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[enemigo1]->pinta_enemigo(buffer);
                enemigos[enemigo2]->pinta_enemigo(buffer);

                naves[nave2]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                buffer.update();

                pausa();
                rest(1);
            }
            if(time->get_seg()>=80)
            {
                n++;
                if(n==1)
                    naves[nave2]->warp_act();
                if(!naves[nave2]->chek_warp())
                    recompenza->pasar_niveles();
            }
        }
    }
}

void STAR_TREK_GAME::nivel5()
{
    if(recompenza->get_nivel()==5)
    {
        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo1]->cantidad(2);
        enemigos[enemigo2]->cantidad(6);
        enemigos[enemigo2]->cantidad(6);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==5 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave2]->actualizar(0,1);

                enemigos[enemigo1]->actualizar();
                enemigos[enemigo2]->actualizar();

                impacto->impactos(naves[nave2],2,enemigos[enemigo1],enemigos[enemigo2]);

                recompenza->sets(naves[nave2]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[enemigo1]->pinta_enemigo(buffer);
                enemigos[enemigo2]->pinta_enemigo(buffer);

                naves[nave2]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                buffer.update();

                pausa();
                rest(1);
            }
            if(time->get_seg()>=80)
            {
                n++;
                if(n==1)
                    naves[nave2]->warp_act();
                if(!naves[nave2]->chek_warp())
                    recompenza->pasar_niveles();
            }
        }
    }

}

void STAR_TREK_GAME::nivel6()
{
    if(recompenza->get_nivel()==6)
    {

        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo2]->cantidad(4);
        enemigos[enemigo3]->cantidad(3);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==6 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave2]->actualizar(0,1,1);

                enemigos[enemigo2]->actualizar();
                enemigos[enemigo3]->actualizar();

                impacto->impactos(naves[nave2],2,enemigos[enemigo2],enemigos[enemigo3]);

                recompenza->sets(naves[nave2]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[enemigo2]->pinta_enemigo(buffer);
                enemigos[enemigo3]->pinta_enemigo(buffer);

                naves[nave2]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                buffer.update();

                pausa();
                rest(1);
            }
            break;
            if(time->get_seg()>=80)
            {
                n++;
                if(n==1)
                    naves[nave2]->warp_act();
                if(!naves[nave2]->chek_warp())
                    break;
            }
        }
    }
}

void STAR_TREK_GAME::reto2()
{
    if(recompenza->get_nivel()==6)
    {
        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        bool  enemi_deat=false;
        enemigos[big_enemi2]->cantidad(1);

        while(!game_over()  && !menu_p && recompenza->get_nivel()==6 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {

                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave2]->actualizar(0,1,1);

                if(!enemi_deat)
                    enemigos[big_enemi2]->actualizar_big();
                enemigos[big_enemi2]->set_vcd(1);

                impacto->impactos(naves[nave2],1,enemigos[big_enemi2]);

                recompenza->sets(naves[nave2]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {

                fondo->pintar_nuve(buffer);

                if(!enemi_deat)
                {
                    enemigos[big_enemi2]->disparo_laser(buffer);
                    enemigos[big_enemi2]->pinta_enemigo(buffer);
                }

                naves[nave2]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                for(int i=0; i<4; i++)
                    hline(buffer,115,510+i,114+enemigos[big_enemi2]->get_vida(1),0xf9290e);

                buffer.update();
                pausa();
                rest(1);

            }
            if(enemigos[big_enemi2]->get_vida(1)<0 || enemi_deat)
            {
                enemi_deat=true;
                n++;
                if(n>20)
                {
                    if(n==21)
                        naves[nave2]->warp_act();
                    if(!naves[nave2]->chek_warp())
                    {
                        recompenza->pasar_niveles();
                        naves[nave1]->reinic();
                    }
                }
            }
        }
    }
}

void STAR_TREK_GAME::nivel7()
{
    if(recompenza->get_nivel()==7)
    {

        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo2]->cantidad(2);
        enemigos[enemigo3]->cantidad(4);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==7 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave3]->actualizar(0,1,1,1);

                enemigos[enemigo2]->actualizar();
                enemigos[enemigo3]->actualizar();

                impacto->impactos(naves[nave3],2,enemigos[enemigo2],enemigos[enemigo3]);

                recompenza->sets(naves[nave3]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[enemigo2]->pinta_enemigo(buffer);
                enemigos[enemigo3]->pinta_enemigo(buffer);

                naves[nave3]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                buffer.update();

                pausa();
                rest(1);
            }
            if(time->get_seg()>=90)
            {
                n++;
                if(n==1)
                    naves[nave3]->warp_act();
                if(!naves[nave3]->chek_warp())
                    recompenza->pasar_niveles();
            }
        }
    }
}

void STAR_TREK_GAME::nivel8()
{
    if(recompenza->get_nivel()==8)
    {
        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo3]->cantidad(5);
        enemigos[big_enemi1]->cantidad(1);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==8 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave3]->actualizar(0,1,1,1);

                enemigos[big_enemi1]->actualizar_big();
                enemigos[enemigo3]->actualizar();

                impacto->impactos(naves[nave3],2,enemigos[big_enemi1],enemigos[enemigo3]);

                recompenza->sets(naves[nave3]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[big_enemi1]->pinta_enemigo(buffer);
                enemigos[enemigo3]->pinta_enemigo(buffer);

                naves[nave3]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                buffer.update();

                pausa();
                rest(1);
            }
            if(time->get_seg()>=70)
            {
                n++;
                if(n==1)
                    naves[nave3]->warp_act();
                if(!naves[nave3]->chek_warp())
                    recompenza->pasar_niveles();
            }
        }
    }

}
void STAR_TREK_GAME::nivel9()
{
    if(recompenza->get_nivel()==9)
    {
        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo3]->cantidad(4);
        enemigos[big_enemi1]->cantidad(1);
        enemigos[big_enemi1]->cantidad(1);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==9 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave3]->actualizar(0,1,1,1);
                naves[satelite1]->actualizar(1,0,1,1);
                naves[satelite1]->stac_cord(naves[nave3]->get_nav(),1);
                naves[satelite2]->actualizar(1,0,1,1);
                naves[satelite2]->stac_cord(naves[nave3]->get_nav(),-1);

                enemigos[big_enemi1]->actualizar_big();
                enemigos[big_enemi2]->actualizar_big();
                enemigos[enemigo3]->actualizar();

                impacto->impactos(naves[nave3],3,enemigos[big_enemi1],enemigos[big_enemi2],enemigos[enemigo3]);
                impacto->impactos(naves[satelite1],3,enemigos[big_enemi1],enemigos[big_enemi2],enemigos[enemigo3]);
                impacto->impactos(naves[satelite2],3,enemigos[big_enemi1],enemigos[big_enemi2],enemigos[enemigo3]);
                recompenza->sets(naves[nave3]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[big_enemi1]->pinta_enemigo(buffer);
                enemigos[big_enemi2]->pinta_enemigo(buffer);
                enemigos[enemigo3]->pinta_enemigo(buffer);

                naves[nave3]->pintar(buffer);
                naves[satelite1]->pintar(buffer);
                naves[satelite2]->pintar(buffer);

                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                buffer.update();

                pausa();
                rest(1);
            }
            if(time->get_seg()>=100)
            {
                n++;
                if(n==1)
                    naves[nave3]->warp_act();
                if(!naves[nave3]->chek_warp())
                    recompenza->pasar_niveles();
            }
        }
    }
}


void STAR_TREK_GAME::nivel10()
{
    if(recompenza->get_nivel()==10)
    {
        time->init_ciclo();
        int r_nuve=0;
        int v_nuve=1;
        int y_nuve=1920;
        int n=0;
        enemigos[enemigo3]->cantidad(4);
        enemigos[big_enemi1]->cantidad(1);
        enemigos[big_enemi1]->cantidad(1);
        while(!game_over()  && !menu_p && recompenza->get_nivel()==10 && !recompenza->fin_de_juego())
        {
            jugado=1;
            if(time->logical())
            {
                fondo->actualizar_nuve(y_nuve,r_nuve,v_nuve);

                naves[nave3]->actualizar(0,1,1,1);
                naves[satelite1]->actualizar(1,0,1,1);
                naves[satelite1]->stac_cord(naves[nave3]->get_nav(),1);
                naves[satelite2]->actualizar(1,0,1,1);
                naves[satelite2]->stac_cord(naves[nave3]->get_nav(),-1);

                enemigos[big_enemi1]->actualizar_big();
                enemigos[big_enemi2]->actualizar_big();
                enemigos[enemigo3]->actualizar();

                impacto->impactos(naves[nave3],3,enemigos[big_enemi1],enemigos[big_enemi2],enemigos[enemigo3]);
                impacto->impactos(naves[satelite1],3,enemigos[big_enemi1],enemigos[big_enemi2],enemigos[enemigo3]);
                impacto->impactos(naves[satelite2],3,enemigos[big_enemi1],enemigos[big_enemi2],enemigos[enemigo3]);
                recompenza->sets(naves[nave3]->get_vida(),impacto->get_puntos());
            }
            if(time->graphic())
            {
                fondo->pintar_nuve(buffer);

                enemigos[big_enemi1]->pinta_enemigo(buffer);
                enemigos[big_enemi2]->pinta_enemigo(buffer);
                enemigos[enemigo3]->pinta_enemigo(buffer);

                naves[nave3]->pintar(buffer);
                naves[satelite1]->pintar(buffer);
                naves[satelite2]->pintar(buffer);


                fondo->pintar_escenario(buffer);

                recompenza->print_recompenzas(buffer);

                mouse.draw(buffer);

                buffer.update();

                pausa();
                rest(1);
            }
            if(time->get_seg()>=60)
            {
                n++;
                if(n==1)
                    naves[nave3]->warp_act();
                if(!naves[nave3]->chek_warp())
                {
                    creditos();
                    break;
                }
            }
        }
    }
}


void STAR_TREK_GAME::creditos()
{
    BUFFER credit("archivos/titulos.bmp");
    time->init_ciclo();
    int v_nuve=0;
    while(!game_over() && !menu_p)
    {
        if(time->logical())
        {
            v_nuve++;
        }
        if(time->graphic())
        {
            buffer.blitbmp(credit,0,v_nuve,21,14,550,500);
            fondo->pintar_escenario(buffer);

            fondo->pintar_escenario(buffer);

            recompenza->print_recompenzas(buffer);

            mouse.draw(buffer);

            buffer.update();
            rest(1);
        }
        if(v_nuve>1920)
        {
            menu_p=true;
            jugado=true;
            recompenza->set_nivel(11);
        }
    }
}




