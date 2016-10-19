#ifndef SNOW_H
#define SNOW_H

#include <allegro.h>
#include <list>

using namespace std;

class Snow
{
public:
  Snow(int num=500);
  ~Snow();
  void draw(BITMAP *buffer);
  void draw(BITMAP *buffer,BITMAP *elemento);
  void update();

private:

  struct copo_t
  {
      struct
      {
          int x,y;
      }pos, speed;
  };

  list <copo_t> copos;

  void crear_copo(copo_t *copo);
};

#endif
