// geomod.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include <iostream>
#include <array>
#include <cmath>
#include "geomod.h"
#include "constantes.h"

using namespace std;


//Max et epsilon
namespace {
	double epsilon_zero;
	double max1(dim_max); 
}


//Fonctions de verification de valeurs de input
void set_max(double init_max){
	if(init_max >= 0){
		max1= init_max;
		epsilon_zero = max1* pow(10,-10);
	}
}
	
double get_max(){
	return max1;
	
}

double get_epsilon(){
	return epsilon_zero;
}

double calcul_norme_vecteur(double x1 , double y1 , double x2 , double y2 ) 
{
	double norme_vecteur; 
	norme_vecteur = sqrt ((pow(( x1-x2 ) , 2 )) + pow ((y1-y2) , 2) ); 
	return norme_vecteur;  
}

// Vérifie si une valeur peut être considéré comme nul  
bool equal_zero ( double verification ) 
{
	if (abs(verification) <= epsilon_zero)	return false;
	
	return true;
	
}

//Booléen d'egalite des points

bool Vecteur :: egalite(Point A, Point B){
	norme_vecteur ( A , B ); 
	
	if (get_norme () <= epsilon_zero) return true;
	
	return false ;
}

//Fonctions de la classe Point

//Defini le coordonnes du point
void Point::set_coordonnes(double x1 , double y1)
{
	x=x1;
	y=y1;
}

//Retourne y du point
double Point::get_x() {
	return x;
}

//Retourne y du point
double Point::get_y() {
	
	return y;
}
	
//Normalise les x et y dans le max donné
void Point::normalisation(double& x3, double& y3){

	if (x3 > max1)	x = x3 - 2*max1;
	else if (x3 <-max1)	x = x3 + 2*max1;
	
	if (y3 > max1)	y = y3 - 2*max1;
	else if (y3 < -max1)	y = y3 + 2*max1;
}


// Normalisation par surchage du point 
void Point::normalisation(Point D) {
	
	normalisation(D.x, D.y);
}

void Point::coordonnes_equivalentes (){
	equivalent = {
		get_x() + 2* max1  		, get_y(),
		get_x() - 2* max1  		, get_y(),
		get_x() 				, get_y() + 2* max1 ,
		get_x() 				, get_y() - 2* max1 ,
		get_x() - 2* max1 		, get_y() - 2* max1 ,
		get_x() + 2* max1 		, get_y() + 2* max1 ,
		get_x() + 2* max1 		, get_y() - 2* max1 ,
		get_x() - 2* max1 		, get_y() + 2* max1 ,
		get_x() 				, get_y() 
	};  
}

void Point::dessin(char C,int rayon=0){
	coordonnes_equivalentes();
	
	for(int i(0); i<10; i++){
		
		if (C =='P')dessin_robotP(get_equivalent(i,0),get_equivalent(i,1));		
		if (C =='F')dessin_robotF(get_equivalent(i,0),get_equivalent(i,1));
		if (C =='T')dessin_robotT(get_equivalent(i,0),get_equivalent(i,1));
		if (C =='C')dessin_robotC(get_equivalent(i,0),get_equivalent(i,1));
		if (C =='B')dessin_base(get_equivalent(i,0),get_equivalent(i,1));
		if (C =='R')dessin_rangeC(get_equivalent(i,0),get_equivalent(i,1), rayon);
		} 
}

void Point::set_coordonnes_equivalentes (  int i , int j , double& x) {
	equivalent[i][j]=x;
	std::cout << equivalent[i][j] << std::endl;
}

// Fonctions de la classe Vecteur

double Vecteur :: get_norme () const 
{
return norme;
}

double Vecteur :: get_vect_x () const 
{
return vecteur_x;
} 

double Vecteur :: get_vect_y () const 
{
return vecteur_y;
} 

double Point::get_equivalent(int a, int b){
	
	return equivalent[a][b];
}

void Vecteur::norme_vecteur(Point A, Point B)
{

	x_depart = A.get_x () ;
	y_depart = A.get_y () ;
	x_arrive = B.get_x () ;
	y_arrive = B.get_y () ;


	B.coordonnes_equivalentes ();
	x_equivalent_arrive = B.get_equivalent(0,0);
	y_equivalent_arrive = B.get_equivalent(0,1);
	norme = calcul_norme_vecteur(	x_depart , y_depart , x_equivalent_arrive ,
									y_equivalent_arrive);


	for ( int i(1); i < 9 ; i++ ) {
		if ( calcul_norme_vecteur(	x_depart, y_depart ,B.get_equivalent(i,0) , 
									B.get_equivalent(i,1)) < norme ){
										
			x_equivalent_arrive = B.get_equivalent(i,0);
			y_equivalent_arrive = B.get_equivalent(i,1);
			norme = calcul_norme_vecteur(x_depart , y_depart , B.get_equivalent(i,0), 
										B.get_equivalent(i,1));
			} 
		}
 	vecteur_x = x_equivalent_arrive - x_depart;
	vecteur_y = y_equivalent_arrive - y_depart;
}

void Vecteur::dessin(){
	dessin_liens(x_depart,y_depart,x_arrive,y_arrive);
	
	dessin_liens(	x_depart+2*dim_max,y_depart,
					x_arrive+2*dim_max,y_arrive);
}

//Fonctions de la classe Cercle

void Cercle::set_centre ( double x , double y){

	centre.set_coordonnes ( x , y ); 
} 

void Cercle::set_rayon ( double R) {

	Cercle::rayon = R; 
} 

double Cercle::get_rayon() {

return Cercle::rayon; 
}

Point Cercle::get_centre(){
	return centre;
}


bool Cercle::appartient_cercle ( Point& A) 
{
	Vecteur V;
	V.norme_vecteur(get_centre(),A); 
	if ( V.get_norme() < rayon - epsilon_zero) return true;	
	
return false;			
}  

double Cercle::get_x(){
	
	return get_centre().get_x();}
	
double Cercle::get_y(){
	
	return get_centre().get_y();}
	
void Cercle::dessin(char C,int rayon=0,double ressource=0){
	Point p = get_centre();	
	p.coordonnes_equivalentes();
	for(int i(0); i<10; i++){
		if (C =='G')dessin_gisement(p.get_equivalent(i,0),p.get_equivalent(i,1), rayon, ressource);
		} 
}

bool intersection_deux_cercles ( Cercle C1 , Cercle C2 )
{
	Vecteur W;
	W.norme_vecteur (C1.get_centre() , C2.get_centre()); 
	
	if ( W.get_norme() <= C1.get_rayon() + C2.get_rayon() - epsilon_zero) return true; 
	 
	return false; 
}

double randomNb ( int b )
{
	double r = rand() ;
	r = fmod ( r , b ) + 1 ; 
	return r; 
}

void normalisationGlobal(double& x3, double& y3){

	if (x3 > max1)	x3 = x3 - 2*max1;
	else if (x3 <-max1)	x3 = x3 + 2*max1;
	
	if (y3 > max1)	y3 = y3 - 2*max1;
	else if (y3 < -max1)	y3 = y3 + 2*max1;
}
