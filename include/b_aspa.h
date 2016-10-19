/*
  Header: b_aspa.h
  Name: CLASE B_ASPA
  Author: ENYERBER FRANCO
  Date: 22/01/15 15:00
  Description: ES UNA CLASE TOTALMENTE ASTRACTA PARA
  EL BOTON DE ASPA X
*/
#ifndef B_ASPA_H
#define B_ASPA_H

class B_ASPA
{
    public:
        void aspa_init();
        static void exit();
         bool game_over();
    protected:
        static bool salir;
    private:
};
#endif // B_ASPA_H
