#ifndef TIME_H
#define TIME_H
#include <allegro.h>
class TIME
{
    public:
        TIME(){}
        TIME(int );
        virtual ~TIME();
        void init(int );
        void endt();
        void init_ciclo();
        bool logical();
        bool graphic();
        int get_fps();
        int get_clps();
        int get_seg();
    protected:
        static int ticks;
        static void TIME_ticks();
    private:
        int grafic_c;
        int max_grafic_c;
        int log_tick;
        int grafic_tick;
        int actick;
        int old_tick;
        int stick;
        int cps;
        int segundos;
};
#endif // TIME_H
