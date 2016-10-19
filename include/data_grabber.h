#ifndef DATA_GRABBER_H
#define DATA_GRABBER_H
#include <allegro.h>
#include <string>
#include "b_aspa.h"

class DATA_GRABBER:private B_ASPA
{
public:
    DATA_GRABBER();
    DATA_GRABBER(const char *,const char *ext=".dat");
    virtual ~DATA_GRABBER();
    bool load(const char *,const char *ext=".dat");
    BITMAP *operator[](int i);
    template <typename T>
    void operator()(T *&TYPE,int i)
    {
        TYPE= ((T *)data[i].dat);
    }

    void draw_bmp(BITMAP *,int,int x=0,int y=0);
    void draw_rle(BITMAP *,int,int x=0,int y=0);
    void blit_bmp(BITMAP *,int ,int,int,int,int,int,int);
protected:
    DATAFILE *data;
private:
    std::string filename;
    const char *ext_file;
};

#endif // DATA_GRABBER_H
/*
_CRTIMP char* __cdecl __MINGW_NOTHROW	itoa (int, char*, int);
_CRTIMP char* __cdecl __MINGW_NOTHROW	ltoa (long, char*, int);*/
