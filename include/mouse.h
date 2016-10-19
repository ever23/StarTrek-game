#ifndef MOUSE_H
#define MOUSE_H
#include <allegro.h>
#include <vector>
#include "b_aspa.h"
#define MOUSE_D 0
class MOUSE:private B_ASPA
{
    public:
        MOUSE();
        MOUSE(BITMAP *);
        virtual ~MOUSE();
        int init();
        int init(BITMAP *);
        void remove();
        int x();
        int y();
        int z();
        void get_z(int);
        void draw(BITMAP *,int mouse_n=MOUSE_D);
        void load_bmp(BITMAP *);
        int add_newbmp(BITMAP *);
        static bool chek(int, int, int, int);
        bool b_der();
        bool b_izq();
        void rango(int,int,int,int);
        void velocidad(int ,int);
        void get_distancia(int &,int &);
        void scare(int,int,int,int);
        void unscare();
    protected:
       std::vector<BITMAP*> bmp_mouses;
    private:
        int n_mouse;

};

#endif // MOUSE_H
