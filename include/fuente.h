/*
  Header:
  Name:
  Author: ENYERBER FRANCO
  Date: 00/00/14 00:00
  Description:
*/
#ifndef FUENTE_H
#define FUENTE_H
#include <allegro.h>
#include <allegttf.h>

typedef struct FONT ALLEGRO_FONT;

class FUENTE
{
    public:
        FUENTE();
        FUENTE(const char *);
        FUENTE(const char *,const int,const int );
        FUENTE(const char *, const int , const int , const int );
        virtual ~FUENTE();
        void load_pcx(const char *);
        void load_ttf(const char *,const int,const int );
        void load_ttf_ex(const char *, const int , const int , const int );
        int get_h();
        int text_length(const char *);
        operator ALLEGRO_FONT *();

    protected:
        ALLEGRO_FONT *fuente;
    private:
};

#endif // FUENTE_H
