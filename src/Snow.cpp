#include "../include/Snow.h"
#include <stdlib.h>

// Constructor
Snow::Snow(int num)
{
  copo_t copo;

  for(int i=0; i < num; i++)
  {
    crear_copo(&copo);
    copos.push_back(copo);
  }
}

// Destructor
Snow::~Snow()
{
}

// Crea un nuevo copo
void Snow::crear_copo(copo_t *copo)
{
  copo->pos.x=rand()%SCREEN_W;
  copo->pos.y=rand()%SCREEN_H;
  copo->speed.x=rand()%2;
  copo->speed.y=rand()%2+1;
  if(copo->speed.x==0) copo->speed.x=-1;
}

// Dibuja los copos de nieve
void Snow::draw(BITMAP *buffer)
{
  list <copo_t>::iterator tmp;



  for(tmp=copos.begin(); tmp!=copos.end(); tmp++)
  {
     putpixel(buffer, tmp->pos.x, tmp->pos.y, 0Xffffff);
  }

}
void Snow::draw(BITMAP *buffer,BITMAP *elemento)
{
  list <copo_t>::iterator tmp;

  for(tmp=copos.begin(); tmp!=copos.end(); tmp++)
  {
      // putpixel(buffer, tmp->pos.x, tmp->pos.y, 0Xffffff);
       draw_sprite(buffer,elemento,tmp->pos.x, tmp->pos.y);
  }



}

// Mueve STRELLAS
/*
void Snow::update()
{
  list <copo_t>::iterator tmp;

  for(tmp=copos.begin(); tmp!=copos.end(); tmp++)
  {
    tmp->pos.y+=tmp->speed.y;
    crear_copo(&(*tmp));
  }
}
*/
//MUEVE COPOS DE NIEVE
void Snow::update()
{
  list <copo_t>::iterator tmp;

  for(tmp=copos.begin(); tmp!=copos.end(); tmp++)
  {
    tmp->pos.y+=tmp->speed.y;
    if(rand()%2) tmp->pos.x+=tmp->speed.x;

    if((tmp->pos.x <= 0) || (tmp->pos.x >= SCREEN_W) || (tmp->pos.y >= SCREEN_H))
    {
      crear_copo(&(*tmp));
      tmp->pos.y=0;
    }
  }
}

