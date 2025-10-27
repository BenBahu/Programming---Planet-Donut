// geomod.h
// Auteurs : Georg Schwabedal et Daniel Silva


#ifndef GEOMOD_H
#define GEOMOD_H
#include <array>
#include <cstdlib>
#include <ctime>
#include "graphic.h"
	

bool equal_zero (double verification);

void set_max(double init_max);

double get_max();

double get_epsilon();

double calcul_norme_vecteur(double x1 , double y1 , double x2 , double y2 ) ;

	
class Point{
	public:
		
	void set_coordonnes(double x1 , double y1);
	double get_x() ;
	double get_y() ;
	void set_coordonnes_equivalentes ( int a , int b , double& c) ;
	void normalisation(double& x3,double& y3);
	void normalisation(Point D);
	void coordonnes_equivalentes();
	double get_equivalent(int a, int b); 
	void dessin(char C, int rayon);
		
	private:
	std::array<std::array<double , 2 > , 9 > equivalent;
	double x; 
	double y;	
};


class Vecteur{ 
	public: 
	double get_norme () const;
	double get_vect_x () const;
	double get_vect_y () const;
	void norme_vecteur(Point depart, Point arrive);
	bool egalite(Point A, Point B);
	void dessin();
		
	private: 
	double x_depart;
	double y_depart;
	double x_arrive; 
	double y_arrive;
	double x_equivalent_arrive;	
	double y_equivalent_arrive; 
	double norme;
	double vecteur_x;
	double vecteur_y;
};

class Cercle{
	public:
	void set_centre(double x1, double x2);
	void set_rayon(double R);
	Point get_centre();
	double get_rayon();
	bool appartient_cercle(Point& verificcation);
	double get_x();
	double get_y();
	void dessin(char C,int rayon,double ressource);
		
		
	private:
	Point centre; 
	double rayon;
};


	bool intersection_deux_cercles(Cercle C_1, Cercle C_2);
	double randomNb ( int b );
	void normalisationGlobal(double& x3,double& y3);

#endif
