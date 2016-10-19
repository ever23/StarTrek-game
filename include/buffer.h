/*
  Header:
  Name:
  Author: ENYERBER FRANCO
  Date: 00/00/14 00:00
  Description:
*/
#ifndef BUFFER_H
#define BUFFER_H

#include <allegro.h>
#include "gfx_basic.h"

class BUFFER
{
    public:
        BUFFER();
        BUFFER(const char *);
        BUFFER(int ,int);
        virtual ~BUFFER();
        bool load(const char*);
        void create(int w=screen->w, int h=screen->h);
        void create_vdo(int w=screen->w, int h=screen->h);
        void clear(int);
        void clear();
        operator BITMAP *();
        int get_w();
        int get_h();
        void blitbmp(BITMAP *,int,int,int,int,int,int);
        void stretchblit(BITMAP *,int , int, int, int, int ,int, int, int);
        void mask_stretchblit(BITMAP *,int , int, int, int, int ,int, int, int);
        void mask_blitbmp(BITMAP *,int,int,int,int,int,int);
        void drawbmp(BITMAP *,int x=0,int y=0);
        void stretch_drawbmp( BITMAP *, int , int , int , int );
        void update();
        void mask_udapte();
        void delete_bmp();
        void save(const char *);
    protected:
        BITMAP *mi_bmp;
    private:
        void act_wh();
        int h,w;
};

#endif // BUFFER_H









