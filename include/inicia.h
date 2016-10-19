/*
  Name: CLASE INICIAR PARA EL JUEGO STAR TREK
  Author: ENYERBER FRANCO
  Date: 20/01/15 12:34
  Description: DEFINICION DE LA CLASE INICIAR PARA EL JUEGO
  INICIA EL ENTORNO DE ALLEGRO
*/
#ifndef INICIA_H_INCLUDED
#define INICIA_H_INCLUDED
#define inicio_                          0        /* BMP  */
#define barra_                           1        /* BMP  */
#define menu_                            2        /* BMP  */
#define menu_jugadores_                  3        /* BMP  */
#define info_ayuda                       4        /* BMP  */
#define cursor_                          5        /* BMP  */
#define get_gamer                        6        /* BMP  */

#define JUGAR_L                          7       /* BMP  */
#define JUEGAR_L_HOVER                   8       /* BMP  */
#define AYUDA_                           9       /* BMP  */
#define AYUDA_HOVER                      10       /* BMP  */
#define SALIR_                           11       /* BMP  */
#define SALIR_HOVER                      12       /* BMP  */


#include<allegro.h>
#include <fstream>
#include <vector>

#include "gfx_basic.h"
#include "data_grabber.h"
#include "mouse.h"
#include "buffer.h"
#include "fuente.h"
using namespace std;
class INICIAR: public GFX_BASIC
{
public:
    //CONSTRUCTOR
    INICIAR();
    //DESTRUCTOR
    ~INICIAR();
    void cargar_datafile(const char *);
    void inicio();
    void menu_principal();
    void savegame(int ,int);
    void guardar_dtg();
    int get_nivel();
    int get_pts();
private:
    void jugador();
    void pintar_dtg(BITMAP *);
    void read_key_();
    void read_dtg();
    void ayuda_();
    DATA_GRABBER grab;
    BUFFER buffer;
    MOUSE mouse;
    FUENTE font1;
    FUENTE font2;
    struct data_game
    {
        int puntos;
        int nivel;
        char name[100];
    };
    data_game gamer;
    ifstream fentrada;
    ofstream fsalida;
    vector<data_game> datos;
    int ini_game;
    const char *filename;

};


#endif // INICIA_H_INCLUDED
