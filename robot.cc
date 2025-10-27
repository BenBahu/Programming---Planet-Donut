// robot.cc
// Auteurs : Georg Schwabedal et Daniel Silva
#include "robot.h"

using namespace std;

//=========================================================Robot-biblio get set========


Robot::Robot ( 	int id , double p , double x , double y , double x1 , double y1, 
					std::string at) {
	pos.set_coordonnes(x,y);
	uid=id;
	but.set_coordonnes(x1 ,y1 ); 
	compteur_de_distance=0;
	if (at == "true" ) atteint= true;
	else atteint = false;
	
}

bool Robot :: get_atteint () 
{
	return atteint; 
}

double Robot::get_x() const{
	return get_centre().get_x();
}

double Robot::get_y() const {
	return get_centre().get_y();
}

void Robot :: set_jus ( bool b ){
jus = b ; 	
}

bool Robot ::  get_jus () {
return jus; 	 
}

void Robot :: set_base ( double xb , double yb )
{
	x_base = xb; 
	y_base = yb;
}

void Robot :: rentrer_base ()
{
	but.set_coordonnes ( x_base , y_base ); 
	retour = true; 
	atteint = false;
}

int Robot :: get_uid () const	{
	return uid;
}
	
void Robot :: set_Connect( bool a )
{
	Connect = a; 	
}

bool Robot :: get_Comm_Base ()  const 
{
	return robot_base; 
}

bool Robot :: get_Connect ()
{
	return Connect; 
}

bool Robot :: transformationStringBool ( std::string A ){
	
	if ( A == "true" or A == " true " or A == "true " or A == " true" ) {
		return true; 
	}
	else{
		return false; 
	}
}
	
Point Robot :: get_But() const{
	return but; 
}
	
void Robot :: set_but ( double x3 , double y3){
	but.set_coordonnes ( x3 , y3 );  
}

void Robot :: set_but ( Point A )
{
	but.set_coordonnes ( A.get_x() , A.get_y() ); 
}
	
	
void Robot ::  set_compteur_de_distance ( double dp ) {
	compteur_de_distance = dp ; 
}
	
double Robot :: get_compteur_de_distance () const{
	return compteur_de_distance; 
}


void Robot :: set_robot_base ( bool f )
{
	robot_base = f; 
}
	
Point Robot :: get_centre() const{
	return pos; 
}


char Robot :: get_type() {
return type; 
}

bool Robot :: get_retour() {
return retour; 
}

void Robot :: set_retour( bool a ) {
retour = a ; 	
}
Robot :: ~Robot() {}

shared_ptr<Robot> Robot::robot_voisins(int i ) const{
	return robots_voisins[i];
}

void Robot::set_voisin(shared_ptr<Robot> voisin){
	robots_voisins.push_back(voisin);
}

size_t Robot::size_voisin() const{
	return robots_voisins.size();
}

double Robot::voisin_uid(int i) const {
	return robots_voisins[i]->get_uid();
}

void Robot::clear_voisins(){
	robots_voisins.clear();
}
//=========================================================Prospecteur=================

Prospecteur :: Prospecteur (int id,double par,double x_1,double y_1,double x3,
							double y3,string a,string r,string f,double x4,
							double y4,double t,double c)
							: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a){
	retour = transformationStringBool(r);
	found = transformationStringBool(f);
	xg = x4;
	yg = y4;
	taille = t;
	capacite = c;
	type = 'P';
}

Prospecteur :: Prospecteur (int id,double par,double x_1,double y_1,double x3,
							double y3,string a,string r,string f)
							: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a){
	retour = transformationStringBool(r);
	found = transformationStringBool(f);
	type = 'P';
}


 shared_ptr <Robot> Prospecteur ::  copie()  {
	return shared_ptr<Prospecteur>(new Prospecteur(*this));
}
	
Prospecteur :: ~ Prospecteur() {}



void Prospecteur :: mode_remote (  	vector < shared_ptr<Robot> >& rob ,
									vector < shared_ptr <Gisement> > tabg  )									
{																						
	Vecteur V;				
	if ( found == false ) {																		
		for ( size_t i (0); i < tabg.size() ; i++ ) {																									
			V.norme_vecteur( tabg[i] -> getCercleG().get_centre() , pos ); 	 												
			if( tabg[i] -> getCercleG().get_rayon() > V.get_norme() and 
				tabg[i] -> get_qt_resources() > deltaR ){ 
				bool connu ( false ); 
				for ( size_t j(0) ; j < rob.size() ; j++ ){ 
					if (rob[j]->get_type()== 'F' and rob[j]->get_Connect()==true){ 
					
						if(	rob[j]->get_But().get_x()==tabg[i]->
							getCercleG().get_x() and  rob[j] -> get_But().
							get_y() ==  tabg[i] -> getCercleG().get_y()){
							connu = true;
						}
					}	
				}
				if ( connu == false ){
					found = true;																														
					xg = tabg[i] -> getCercleG().get_x();																				
					yg = tabg[i] -> getCercleG().get_y();
					taille = tabg[i] -> getCercleG().get_rayon();
					capacite = tabg[i] -> get_qt_resources();	
				}																								
			} 
		}	
	}
	Point P ;
	P.set_coordonnes(x_base ,y_base); 
	V.norme_vecteur(pos,P);  																				
	if ( (maxD_prosp - compteur_de_distance -  deltaD) <= V.get_norme()){
		retour = true;  																									
		rentrer_base(); 																										 		
	}
	
	if (atteint == true and (maxD_prosp-compteur_de_distance-deltaD) > V.get_norme()){																										// on crée de nouvelles coordonnes au piff si jamais on est arrivé à notre destination
		int signe = randomNb ( 4 ); 																								// on crée une variable qui vas decider de la combinaison de notre but, ++ , -+ , +- ou -- 
		double alleX = randomNb ( 1000 );																							 // les deux variables qui vont prendre des coordonnées dans le monde au hasard 
		double alleY = randomNb ( 1000 );  
				
		switch (signe){
			case (1):	
			but.set_coordonnes( alleX , alleY );
			break;
				
			case 2:
			but.set_coordonnes(  alleX , - alleY );
			break;
				
			case 3:
			but.set_coordonnes(  - alleX , alleY );
			break;
				
			case 4:
			but.set_coordonnes( - alleX , - alleY );
			break;
		}
		
		atteint = false; 
	}
	//found = false;
	deplacement_vers_but();
}

void Prospecteur :: mode_autonome( 	vector < shared_ptr<Robot> >& rob ,
									vector < shared_ptr <Gisement> > tabg ){ 												
																											
	Vecteur V; 
	if ((maxD_prosp - compteur_de_distance - 2* deltaD) < V.get_norme()) {									
			retour = true;  																				
			rentrer_base(); 																				
	}
	if ( atteint == true ) {																			
		for ( size_t i (0); i < tabg.size() ; i++ )	{	
				V.norme_vecteur( tabg[i] -> getCercleG().get_centre() , pos );		
				if( tabg[i] -> getCercleG().get_rayon() < V.get_norme() and 
					tabg[i] -> get_qt_resources() > deltaR ) 		
					{ 
					found = true;																						
					xg = tabg[i]  -> getCercleG().get_x();															
					yg =  tabg[i] -> getCercleG().get_y();	
					taille = tabg[i]  -> getCercleG().get_rayon();
					capacite = tabg[i]  -> get_qt_resources();
					rentrer_base();																		
			} 
		}	
	} else deplacement_vers_but (); 									
}


// getter et setter pour bouriner 
void Prospecteur :: P_set_found ( bool a ) { found = a; }; 

void Prospecteur :: set_found ( bool i ){ found = i ; }
void Prospecteur :: set_xg ( double x1 ){ xg = x1 ; }
void Prospecteur :: set_yg ( double y1 ){ yg = y1 ; }
void Prospecteur :: set_taille( double t ){ taille = t ; } 
void Prospecteur :: set_capacite ( double c ){ capacite = c ; }
	
bool Prospecteur :: get_found () const { return found; } 
	
double Prospecteur :: P_get_xg () { return xg; }
double Prospecteur :: P_get_yg () { return yg; }
double Prospecteur :: P_get_taille () { return taille ; }
double Prospecteur :: P_get_capacite () { return capacite ; }
bool Prospecteur :: P_get_found() { return found; }

void Prospecteur :: deplacement_vers_but () 
{
	if ( compteur_de_distance < maxD_prosp ) {
		double D, r, m; 
		Vecteur V; 
		V.norme_vecteur( pos , but );  
		D = V.get_norme();
		r = fmod( D , deltaD ); 
		m = ( D - r) / deltaD; 
		if ( D < deltaD ) {
			pos.set_coordonnes( but.get_x() , but.get_y() ); 
			atteint = true; 
			compteur_de_distance= compteur_de_distance + D ; 
		}else { 
			pos.set_coordonnes ( pos.get_x() + ((V.get_vect_x()-r)/m) , 
								 pos.get_y() + ((V.get_vect_y()-r)/m));
			compteur_de_distance = compteur_de_distance + 5. ; 
		}	
		pos.normalisation(pos); 
	}
}

//=========================================================Forage======================

Forage :: Forage (	int id,double par,double x_1,double y_1,double x3,double y3,
						string a): Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a) {
	type = 'F';
	jus = true; 
}


void Forage :: GisementPlein ( shared_ptr <Gisement> C ) 
{
	if( C-> get_qt_resources() < deltaR ) plein = false;
	else plein = true; 
	
}


 shared_ptr <Robot>  Forage::  copie() {
	return shared_ptr<Forage>(new Forage(*this));
}

Forage :: ~ Forage() {}

void Forage :: forage ( shared_ptr  <Gisement> A )
{ 
	double d = A -> get_qt_resources() - deltaR ;  
	A -> set_qt_ressources ( d );  				   												
} 

void Forage :: mode_autonome (  vector < shared_ptr<Robot> >& rob ,
								vector < shared_ptr <Gisement> > tabg ) {	
	Vecteur V; 
	if ( atteint == false  ) deplacement_vers_but();
	else if ( atteint == true ){ 	
		for ( size_t j (0) ; j < tabg.size() ; j++ ){
			V.norme_vecteur (tabg[j] -> getCercleG().get_centre() , pos);
			if( V.get_norme() <= tabg[j] -> getCercleG().get_rayon() ){														
				GisementPlein( tabg[j] );																						 
				if ( plein == true ){																					
					for ( size_t i (0) ; i < rob.size() ; i++) {; 																			
						Vecteur D ;
						if (rob[i]->get_type() == 'T' and 
							D.egalite(pos,rob[i]->get_centre())){ 																																 
							for ( size_t t (0) ; t < rob.size() ; t++ ){ 
								if ( rob[t]-> get_uid() == 	rob[i] -> get_uid()){ 											
									forage(tabg[j]);
									rob[i] -> set_retour ( true ) ; 																	
									rob[i] -> set_but( x_base , y_base );}												
							}																
						}	
					}
				}else{
					jus = false ; 
					for ( size_t i (0) ; i < robots_voisins.size() ; i++) {																	
						if ( 	rob[i] -> get_type() == 'T' and 
								rob[i] -> get_retour() == false){																																
							Vecteur D ; 
							if (D.egalite( pos , rob[i] -> get_centre() ) == true) {
								for ( size_t t (0) ; t < rob.size() ; t++ ) {
									if ( 	rob[t]-> get_uid() == 	
											robots_voisins[i] -> get_uid() ) {					
											rob[i] -> set_retour ( true ) ; 																	
											rob[i] -> set_but( x_base , y_base );}												
								}																
							}
						}
					}
				}
			}
		} 
	}
}



void Forage ::  mode_remote ( 	vector < shared_ptr<Robot> >& rob ,
								vector < shared_ptr <Gisement> > tabg ){
	Vecteur V;  
	if ( atteint == false  ) deplacement_vers_but();
	else if ( atteint == true ){
		for ( size_t j (0) ; j < tabg.size() ; j++ ){
			V.norme_vecteur (tabg[j] -> getCercleG().get_centre() , pos);
			if( V.get_norme() <= tabg[j] -> getCercleG().get_rayon() ){														
				GisementPlein( tabg[j] );																						 
				if ( plein == true ){																					
					for ( size_t i (0) ; i < robots_voisins.size() ; i++) {																
						Vecteur D ; 
						if (robots_voisins[i] -> get_type() == 'T' and 
							robots_voisins[i] -> get_retour() == false and 		
							D.egalite(pos,robots_voisins[i]->get_centre() ) == true){ 
							for ( size_t t (0) ; t < rob.size() ; t++ ){ 
								if (rob[t]->get_uid()==robots_voisins[i]->get_uid()) {		
									forage(tabg[j]);
									rob[t] -> set_retour ( true ) ; 
									rob[t] -> set_but( x_base , y_base ); }																
							}
						}
					}
				}else if ( plein == false )  {
					for ( size_t i (0) ; i < robots_voisins.size() ; i++) {																		
						Vecteur D;
						if ( robots_voisins[i] -> get_type() == 'T' and
							 D.egalite(pos,robots_voisins[i]->get_centre()) == true){
							for ( size_t t (0) ; t < rob.size() ; t++ ) {
								if(rob[t]->get_uid()==robots_voisins[i]->get_uid()){ 			
									rob[i] -> set_retour ( true ) ; 																	
									rob[i] -> set_but( x_base , y_base );}												
							}																
						}
					}
				}	
			}
		}
	} 
}			


void Forage :: P_set_found ( bool a ) {}; 

double Forage :: P_get_xg () {return 0;}
double Forage :: P_get_yg () {return 0;}
double Forage :: P_get_taille () {return 0;}
double Forage :: P_get_capacite () {return 0;}
bool Forage :: P_get_found() {return plein;}

void Forage :: deplacement_vers_but () 
{
	if ( compteur_de_distance < maxD_forage ) {
		double D, r, m; 
		Vecteur V; 
				V.norme_vecteur( pos , but );  
				D = V.get_norme();
				r = fmod( D , deltaD ); 
				m = ( D - r) / deltaD; 
			if ( D < deltaD ) {
				pos.set_coordonnes( but.get_x() , but.get_y() ); 
				atteint = true; 
				compteur_de_distance= compteur_de_distance + r ; 
			}else { 
				pos.set_coordonnes ( 	pos.get_x() + (V.get_vect_x()/m) - (r/m), 
										pos.get_y() + (V.get_vect_y()/m) - (r/m));
				compteur_de_distance = compteur_de_distance + 5. ; 
			}
			
			pos.normalisation(pos); 
	}
}


//=========================================================Transport===================

Transport :: Transport (int id,double par,double x_1,double y_1,double x3,
						double y3, string a,string r)
						: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a){
	retour  = transformationStringBool(r);
	type = 'T';
}

shared_ptr <Robot> Transport ::  copie()  {
	return shared_ptr<Transport>(new Transport(*this));
}

Transport :: ~Transport() {}

void Transport :: mode_autonome ( 	vector < shared_ptr<Robot> >& rob ,
									vector < shared_ptr <Gisement> > tabg )
{
	Vecteur V;  
	V.norme_vecteur( pos , but ); 	
	if ( V.get_norme() != 0){
		
		deplacement_vers_but();		
	}else{						
				
			 rentrer_base();
	} 
}

void Transport ::  mode_remote ( 	vector < shared_ptr<Robot> >& rob ,
									vector < shared_ptr <Gisement> > tabg  ){ 
	
	Vecteur V;  
	V.norme_vecteur( pos , but ); 	
	if ( V.get_norme() != 0 ){
		deplacement_vers_but();		
	}else{							
			rentrer_base();
		
	} 
}


void Transport :: P_set_found ( bool a ) {}; 

double Transport :: P_get_xg () {return 0;}
double Transport :: P_get_yg () {return 0;}
double Transport :: P_get_taille () {return 0;}
double Transport :: P_get_capacite () {return 0;}
bool Transport :: P_get_found() {return true;}


void Transport :: deplacement_vers_but () 
{
	if ( compteur_de_distance < maxD_transp ) {
		double D, r, m; 
		Vecteur V; 
				V.norme_vecteur( pos , but );  
				D = V.get_norme();
				r = fmod( D , deltaD ); 
				m = ( D - r) / deltaD; 
			if ( D < deltaD ) {
				pos.set_coordonnes( but.get_x() , but.get_y() ); 
				atteint = true;
//				if (get_type()=='T') retour = true;
				compteur_de_distance= compteur_de_distance + deltaD ; 
			}else { 
				pos.set_coordonnes ( 	pos.get_x() + ((V.get_vect_x()-r)/m) , 
										pos.get_y() + ((V.get_vect_y()-r)/m));
				compteur_de_distance = compteur_de_distance + deltaD ; 
			}
			
			pos.normalisation(pos); 
	}
}

//=========================================================Communication==============
		
Communication :: Communication (int id,double par,double x_1,double y_1,double x3,
								double y3,std::string a)
								: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a) {
	type = 'C';
	if (a == "true" ) atteint= true;
	else atteint = false;

}

shared_ptr <Robot> Communication ::  copie() {
	return shared_ptr<Communication>(new Communication(*this));
}

Communication :: ~Communication() {}

void Communication :: mode_autonome ( 	vector < shared_ptr<Robot> >& rob ,
										vector < shared_ptr <Gisement> > tabg  )
{
	if ( atteint == false ) {															
	deplacement_vers_but(); 															
	}
}

void Communication :: mode_remote ( vector < shared_ptr<Robot> >& rob ,
									vector < shared_ptr <Gisement> > tabg  )		
{

	if ( atteint == false ) {			
	deplacement_vers_but(); 
	}

}

void Communication :: P_set_found ( bool a ) {}; 

double Communication :: P_get_xg () {return 0;}
double Communication :: P_get_yg () {return 0;}
double Communication :: P_get_taille () {return 0;}
double Communication :: P_get_capacite () {return 0;}
bool Communication :: P_get_found() {return false;}

void Communication :: deplacement_vers_but () 
{
	if ( compteur_de_distance < maxD_com ) {
		double D, r, m; 
		Vecteur V; 
				V.norme_vecteur( pos , but );  
				D = V.get_norme();
				r = fmod( D , deltaD ); 
				m = ( D - r) / deltaD; 
			if ( D < deltaD ) {
				pos.set_coordonnes( but.get_x() , but.get_y() ); 
				atteint = true; 
				compteur_de_distance= compteur_de_distance + 5. ; 
			}else { 
				pos.set_coordonnes ( 	pos.get_x() + (V.get_vect_x()/m) , 
										pos.get_y() + (V.get_vect_y()/m));
				compteur_de_distance = compteur_de_distance + 5. ; 
			}
			
			pos.normalisation(pos); 
	}
}

//=========================================================Robot algos=================









