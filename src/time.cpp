#include "../include/time.h"
#include "../include/gfx_basic.h"
#include <iostream>
using namespace std;
int TIME::ticks =0;

TIME::TIME(int tps)
{
    init(tps);
}
TIME::~TIME()
{
    endt();
}
void TIME::init(int tps)
{
    LOCK_VARIABLE(ticks); // protege la variable
    LOCK_FUNCTION(TIME_ticks); // protege procedimiento
    install_int(&TIME_ticks, tps); // instala interrupción
    cout<< "iniciando  time "<<tps<<endl;

}
void TIME::endt()
{
    remove_int(&TIME_ticks);
    cout<< "removiendo  time "<<endl;
}
void  TIME::TIME_ticks()
{
    TIME::ticks++;
}
void TIME::init_ciclo()
{
   grafic_c=0;
    max_grafic_c=15;
    log_tick=ticks;
    grafic_tick=0;
    actick=0;
    old_tick=ticks;
    stick=0;
    cps=0;
    segundos=0;
}

bool TIME::logical()
{
    if (ticks-old_tick >=70) // se cumplió un segundo
    {
        stick=actick;
        actick=0;
        cps=grafic_tick;
        grafic_tick=0;
        old_tick=ticks;
        segundos++;
    }
    if (log_tick<=ticks)
    {
        actick++;
        log_tick++;
        return true;
    }
    return false;
}

bool TIME::graphic()
{
    if ((log_tick>=ticks) || (grafic_c>max_grafic_c))
    {
        if (grafic_c>max_grafic_c) log_tick=ticks;
        grafic_tick++;
        grafic_c=0;
        return true;
    }
    else
    {
        grafic_c++;
    }
    return false;
}
int TIME::get_seg()
{
    return segundos;
}

int TIME::get_clps()
{
    return stick;
}

int TIME::get_fps()
{
    return cps;
}
