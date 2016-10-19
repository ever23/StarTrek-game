/*
  Name: CLASE ESCENARIO PARA EL JUEGO STR TREK
  Author: ENYERBER FRANCO
  Date: 26/11/14 12:34
  Description: DEFINICION DE LA CLASE ESCENARIO PARA EL JUEGO
*/
#ifndef ESCENARIO_H_INCLUDED
#define ESCENARIO_H_INCLUDED
#include <allegro.h>
#include "data_grabber.h"
class ESCENARIO
{
    public:
    ESCENARIO(const char *FILE_ESC);
    ~ESCENARIO();
    void pintar_escenario(BITMAP *);
    void pintar_nuve(BITMAP *BMP );
    void actualizar_nuve(int ,int ,int );
    private:
    int retraso;
    DATA_GRABBER ensc;
    int y_nuve;
    int v_nuve;

};


#endif // ESCENARIO_H_INCLUDED
