#ifndef GISEMENT_H
#define GISEMENT_H
#include <iostream>
#include <vector>
#include <cmath>
#include "geomod.h"

class Gisement{
	public: 
	Gisement( double x , double y , double r , double qt) ;
	~Gisement();
	
	void set_qt_ressources (double& qt_r) ;
	double get_rayon (); 
	Cercle getCercleG () const;
	
	double get_qt_resources () const ;
	double get_x();
	double get_y();
	double get_ressources_init();
	double get_vie() const;
	
	private: 
	Cercle taille_ressources;
	double ressourceInit;
	double quantitee_ressources; 
};

#endif
