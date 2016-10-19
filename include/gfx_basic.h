#include <allegro.h>
#include <iostream>
#ifndef GFX_BASIC_H
#define GFX_BASIC_H
#include "b_aspa.h"
#include "buffer.h"
#include "data_grabber.h"
#include "mouse.h"
#include "time.h"
#include "mask.h"
extern int  screen_w();
extern int  screen_h();
class GFX_BASIC: public B_ASPA
{
public:
    GFX_BASIC();
    virtual ~GFX_BASIC();
    bool init_gfx(int ,int ,int ,int DIS_MODE=SWITCH_PAUSE);
    static bool gfx_mod(int );
    void set_title(const char *);
    friend int  screen_w();
    friend int  screen_h();

private:
    const char *title_game;
    static int profundidad;
    static int pantalla_h;
    static int pantalla_w;
};
void gotoxy(int x,int y);


#endif // GFX_BASIC_H
