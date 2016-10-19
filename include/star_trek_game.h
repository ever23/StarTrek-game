#ifndef STAR_TREK_GAME_H
#define STAR_TREK_GAME_H
#include "escenario.h"
#include "nave.h"
#include "enemigos.h"
#include "disparos.h"
#include "recompenzas.h"
#include "impactos.h"
#include "data_grabber.h"
#include "time.h"
#include "mouse.h"
#include "buffer.h"
#include "b_aspa.h"
#include "fuente.h"
#include <vector>
class STAR_TREK_GAME: private B_ASPA
{
public:
    STAR_TREK_GAME();
    virtual ~STAR_TREK_GAME();
    void init();
    void main();
    int get_pts();
    bool chek_save();
    int get_nivel();
    void sets(int,int);
private:


    void graphic();
    void logical();
    void pausa();
    void actualizar_enemis();
    void pintar_enemis(BITMAP *BUFFER);
      bool save_game();

    void nivel0();
    void nivel1();
    void nivel2();
    void nivel3();
    void nivel4();
    void nivel5();
    void nivel6();
    void nivel7();
    void nivel8();
    void nivel9();
    void nivel10();

    void reto1();
    void reto2();
    void reto3();

    void creditos();
    FUENTE font1;
    ESCENARIO *fondo;
    RECOMPENZAS *recompenza;
    IMPACTOS *impacto;
    TIME *time;
    vector<ENEMIGOS*> enemigos;
    vector<NAVES*> naves;
    bool savegame;
    bool jugado;
    int nivel;
    bool menu_p;
    DATA_GRABBER BMPS;
    BUFFER buffer;
    MOUSE mouse;

};

#endif // STAR_TREK_GAME_H
