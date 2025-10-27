#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "geomod.h"
#include "constantes.h"
#include "graphic_gui.h"
#include <cairomm/context.h>

using namespace std;

void dessin_base(int x,int y);
					
void dessin_gisement(int x,int y,int rayon,double ressource);

void dessin_robot();
void dessin_cadre(int height, int width);
void dessin_liens(int xa, int ya, int xb, int yb);

void dessin_robotP(int x,int y);
void dessin_robotC(int x,int y);
void dessin_robotT(int x,int y);
void dessin_robotF(int x,int y);
void dessin_rangeC(int x,int y,int rayon);
void dessin_point(int x, int y);

void set_couleur_base(int i);


#endif // GTKMM_EXAMPLE_MYAREA_H
