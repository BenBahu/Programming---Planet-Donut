// base.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include "base.h"
#include "constantes.h"
#include "message.h"
#include <string>

void Base :: trouver_max_uid ()
{
	int id (0); 
	for ( size_t i (0); i < robots_base.size() ; i++ ) 
	{
		if ( robots_base[i] -> get_uid () > id ) 
		{
		id = robots_base[i] -> get_uid(); 
		}
	}
max_uid = id ; 
}



int Base::get_nb_robot() const {
	return robots_base.size();
}

shared_ptr <Robot> Base :: get_robot(int i) const{
	return robots_base[i];
}

int Base::get_nbF() const{
	return nbF;
}

int Base::get_nbP() const {
	return nbP;
}

int Base::get_nbC() const {
	return nbC;
}

int Base::get_nbT() const {
	return nbT;
}

double Base :: get_nb_robot ()
{
	return robots_base.size(); 
} 

bool Base :: get_4G () 
{
	return Active4G; 
}

bool Base :: get_vie () 
{return vie;
}

void Base :: set_vie ( bool a )
{
	vie = a; 
}

Cercle Base::get_cercle () const 
{ 
	return position;
}

Base :: Base ( double x , double y ,  double r , int  P, int F , int T , int C )
{ 
	nbP =P; 
	nbF =F;
	nbT =T;
	nbC =C;
	position.set_centre (x, y);
	position.set_rayon(rayon_base);
	set_ressources (r); 
	compteur=0;
	vie = true;
	
}

double Base::get_x() const{
	return get_cercle().get_centre().get_x();
	}
double Base::get_y() const{
	return get_cercle().get_centre().get_y();
}

void Base::set_couleur(size_t i){
	couleur = i+1;}

int Base::get_couleur(){
	return couleur;}

double Base :: get_ressources () const
{
	return ressources; 
}

void Base :: set_ressources( double& ener )
{
	ressources = ener; 
}


Point Base::get_centre() const {
	return get_cercle().get_centre();
}

//Verification que au moins un robot comm est present dans la base

int Base :: robot_comm(vector <shared_ptr <Base>> listeB) {
	
	bool presence_robotC(false);
	for (size_t i(0); i < robots_base.size(); i++)
	{
			if ( presence_robotC == false ) 
				{
				if (robots_base[i] -> get_type() == 'C'){
					Vecteur b;
					if (b.egalite(get_centre(), robots_base[i] -> get_centre()) == true
						and b.egalite(get_centre(),robots_base[i]->get_But())== true){
						presence_robotC = true;
						robots_base[i] -> set_robot_base(true); 
						robot_communication.push_back( robots_base[i]  );
					}
				}
			}
	}
	if (presence_robotC == false) {
		cout<<message::missing_robot_communication(get_x(),get_y())<<endl;
		return 10;
	}
return 0;
}

//Fonction de ajout d'une base a la liste avec toutes les base




//Addition d'un robot a une base et verification de UIDs differents
int  Base :: ajout_robot ( shared_ptr<Robot> A)
{

	bool uid_egal (false);
	for ( size_t i (0) ; i < robots_base.size() ; i++ ) {
		if ( A -> get_uid() == robots_base[i] -> get_uid() ){
			uid_egal = true;
		}
	}
	if (uid_egal) {
			cout<<message::identical_robot_uid(A -> get_uid());
			return 1;
	}
	
	robots_base.push_back( A );
	return 0;
}



int Base :: get_set_nv_max_uid ()
{
max_uid = max_uid+1;
return max_uid; 	
}

void Base :: Creation4G ()
{
	
	Monde4G ={
	position.get_x() + 0 * rayon_comm , position.get_y() + 0 * rayon_comm , 1 ,	//debut premier niveau
	position.get_x() + 1 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,
	position.get_x() - 1 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,	
	position.get_x() + 0 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() + 0 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() - 1 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() - 1 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,	//debut deuxieme niveau
	position.get_x() - 1 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	position.get_x() + 0 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() + 0 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() - 1 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 , // debut troisieme niveau 
	position.get_x() - 2 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() - 1 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() + 0 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() + 0 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,	
	position.get_x() - 1 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	0 , 0 , 1, 
	};

	for ( size_t i(0); i < 49 ; i ++ ) 
	{
		normalisationGlobal( Monde4G[i][0] , Monde4G[i][1]); 
	}
}


Base :: ~Base ()
{ 

}

Base :: Base(const Base& other) 
	: nbP(other.nbP), nbF(other.nbF), nbT(other.nbT), nbC(other.nbC),
	position(other.position), ressources(other.ressources) 
{
	for (size_t i(0) ; i < robots_base.size() ; ++i) {
		robots_base.push_back((*(other.robots_base[i])).copie());
	}
	vie = true;
	
}

string boolToString(bool a){
	if(a == false) return "false";
	else return "true";
}

void Base::saveBase1(ofstream& myfile){

	myfile<<get_x() <<" "<<get_y()<<" "<<get_ressources()<<" "<<get_nbP()<<" ";
	myfile<<get_nbF()<<" "<<get_nbT()<<" "<<get_nbC()<<"\n";
		
	for (int j(0); j <get_nb_robot(); j++ ){
		if(get_robot(j)->get_type() == 'P'){
			myfile<<get_robot(j)->get_uid()<<" ";
			myfile<<get_robot(j)->get_compteur_de_distance ()<<" ";
			myfile<<get_robot(j)->get_x()<<" "<<get_robot(j)->get_y()<<" ";
			myfile<<get_robot(j)->get_But().get_x()<<" ";
			myfile<<get_robot(j)->get_But().get_y()<<" ";
			myfile<<boolToString(get_robot(j)->get_atteint())<<" ";
			myfile<<boolToString(get_robot(j)->get_atteint())<<" ";
			myfile<<boolToString(get_robot(j)->get_retour())<<" ";
			myfile<<boolToString(get_robot(j)->P_get_found());
			if (get_robot(j)->P_get_found()==true  ){
				myfile<< "true"<<get_robot(j)->P_get_xg()<<" ";
				myfile<< get_robot(j)->P_get_yg()<<" ";
				myfile<<get_robot(j)->P_get_taille()<<" ";
				myfile<<get_robot(j)->P_get_capacite()<< "\n";}
			else {myfile <<"\n";}	
		}	
	}
	saveBase2(myfile);
}


void Base::saveBase2(ofstream& myfile){
	
	for (int j(0); j <get_nb_robot(); j++ ){
		if (get_robot(j)->get_type() == 'F'){
			myfile<<get_robot(j)->get_uid()<<" ";
			myfile<<get_robot(j)->get_compteur_de_distance ()<<" ";
			myfile<<get_robot(j)->get_x()<<" "<<get_robot(j)->get_y()<<" ";
			myfile<<get_robot(j)->get_But().get_x()<<" ";
			myfile<<get_robot(j)->get_But().get_y()<<" ";
			myfile<<boolToString(get_robot(j)->get_atteint())<<"\n";
		}
	}		
	for (int j(0); j <get_nb_robot(); j++ ){
		if (get_robot(j)->get_type() == 'T'){
			myfile<<get_robot(j)->get_uid()<<" ";
			myfile<<get_robot(j)->get_compteur_de_distance ()<<" ";
			myfile<<get_robot(j)->get_x()<<" "<<get_robot(j)->get_y()<<" ";
			myfile<<get_robot(j)->get_But().get_x()<<" ";
			myfile<<get_robot(j)->get_But().get_y()<<" ";
			myfile<<boolToString(get_robot(j)->get_atteint())<<" ";
			myfile<<boolToString(get_robot(j)->get_retour())<<"\n";
		}
	}	
	for (int j(0); j <get_nb_robot(); j++ ){
		if (get_robot(j)->get_type() == 'C'){	
			myfile<<get_robot(j)->get_uid()<<" ";
			myfile<<get_robot(j)->get_compteur_de_distance ()<<" ";
			myfile<<get_robot(j)->get_x()<<" "<<get_robot(j)->get_y()<<" ";
			myfile<<get_robot(j)->get_But().get_x()<<" ";
			myfile<<get_robot(j)->get_But().get_y()<<" ";
			myfile<<boolToString(get_robot(j)->get_atteint())<<"\n";	
		}
	}		
}

void Base :: maintenance ()
{
	Vecteur V; 
	if (ressources >= finR){
		ressources= finR;
		for (size_t i (0); i < robots_base.size(); i++){
			get_robot(i)->set_retour(true);
		}
	} else{
		for ( size_t i (0) ; i < robots_base.size() ;  i++ ) {
			if ( robots_base[i] -> get_Connect() ){ 
				V.norme_vecteur ( position.get_centre() ,robots_base[i]->get_centre());
				if ( V.get_norme() <= deltaD)
				{							
					if ( robots_base[i] -> get_compteur_de_distance() != 0  ) 
					{
						double rep;
						rep = robots_base[i]-> get_compteur_de_distance()*cost_repair; 
						double nv_qt = get_ressources() - rep ;	
						set_ressources ( nv_qt ); 
						double null (0);
						robots_base[i]-> set_compteur_de_distance( null ) ; 
					}
				}
			}	
		}
		ViderRobotsT();
	}
}

void Base :: launch4G_3_supplemetaires () 
{
	shared_ptr<Communication> comm;
	int i (0); 	
													
	do {	
		if ( Monde4G[compteur][2] == 0 )  
		{
			double x7 = Monde4G[compteur][0];		
			double y7 = Monde4G[compteur][1];
			
			comm =shared_ptr<Communication>(new Communication (get_set_nv_max_uid(),0,
											Monde4G[0][0],Monde4G[0][1] , x7 , y7 , 
											"false" ));
			robots_base.push_back(comm); 																													
			i = i + 1;																														
																							
			ressources = ressources - cost_com ; 																					
		}
		compteur+=1; 																													
	} while ( i <3 and compteur < 49 ); 																										
	if ( i == 0 ) Active4G = true; 											
}


bool Base :: decision_interet_gisement ( double x , double y , double r , double c )
{
	bool occupe = false ; 
	Vecteur V; 
	Point P ; 
	P.set_coordonnes( x ,y ); 
	V.norme_vecteur( P , get_centre() ); 
	double reste = fmod ( c , deltaR ); 
	double passages = (c-reste)/deltaR; 
	double cout_gisement = 	cost_forage + cost_transp + ( V.get_norme() - r ) 
							* cost_repair * passages * 2 ;  
	for ( size_t j (0) ; j < robots_base.size() ; j++ ) 
	{
		if ( robots_base[j] -> get_Connect() ) 
		{
			if ( 	robots_base[j] -> get_type() == 'T' or 
					robots_base[j]-> get_type() == 'F' ) 
			{
				if ( 	robots_base[j] -> get_But().get_x() == x and 
						robots_base[j] -> get_But().get_y() ) 
				{
					occupe = true; 
				}
			}
		}
	}
	if ( c > cout_gisement and occupe == false) {
	return true; 
	}else {
	return false; 
	}	
}


void Base :: commande_gisement () {
	shared_ptr<Forage> forage(nullptr);
	shared_ptr<Transport> transport(nullptr);
	for ( size_t i (0); i < robots_base.size() ; i++){ 
	
		if ( 	robots_base[i] -> get_type() == 'P' and 
				robots_base[i] -> get_Connect() == true){ 
			
			if ( robots_base[i]-> P_get_found() == true ){
				robots_base[i] -> P_set_found ( false ) ;
				if (decision_interet_gisement( 	robots_base[i]-> P_get_xg() , 
												robots_base[i]-> P_get_yg() , 
												robots_base[i]-> P_get_taille() , 
												robots_base[i]-> P_get_capacite())){
				
					forage=shared_ptr <Forage>( new Forage ( get_set_nv_max_uid() , 0 ,
												get_x(),get_y(),robots_base[i]-> 
												P_get_xg(),robots_base[i]-> P_get_yg(),
												"false" ));
					transport=shared_ptr<Transport>(new Transport(get_set_nv_max_uid(),
													0,get_x(),get_y(),robots_base[i]-> 
													P_get_xg(),robots_base[i]->
													P_get_yg() , "false" , "false" ));
					robots_base.push_back(forage);
					ressources = ressources - cost_forage; 
					robots_base.push_back(transport ); 
					ressources = ressources - cost_transp;
					robots_base[i] -> set_retour ( false) ;
					 
					robots_base[i]->set_but(robots_base[i]->get_centre().get_x()+10. , 
					robots_base[i]-> get_centre().get_y()+ 10.);			
				}
			}
		}
	}	
}

void Base :: FindActive4G ()
{
	for ( size_t i (0) ; i < 49; i++ )
	{
		for ( size_t j(0) ; j < robots_base.size() ; j++ ) 
		{
			if ( 	robots_base[j] -> get_type() == 'C' and 
					robots_base[j] -> get_Connect() == true ) 
			{
				if ( 	 Monde4G[i][0] == robots_base[j] -> get_But().get_x() and 
						Monde4G[i][1] == robots_base[j] -> get_But().get_y()) 
				{
					Monde4G[i][2] = 1;
				}
			}
		}
	}
}


void Base :: MaJNbRobType ()
{
	nbF = 0;
	nbP = 0;
	nbC = 0;
	nbT = 0;
	for( size_t i(0) ; i < robots_base.size() ; i++ ) 
	{

		if ( robots_base[i] -> get_type() == 'F' ) 
		{ 
			nbF = nbF + 1 ; 
		}
		else if  ( robots_base[i] -> get_type() == 'P' )
		{ 
			nbP = nbP + 1 ;
		}
		else if  ( robots_base[i] -> get_type() == 'C' ) 
		{ 
			nbC = nbC + 1 ; 
		}
		else if ( robots_base[i] -> get_type() == 'T' ) 
		{ 
			nbT = nbT + 1 ; 
		}
	} 
}



void Base :: ViderRobotsT ()
{
	Vecteur V ; 
	for ( size_t i (0) ; i < robots_base.size() ; i++) 
	{
		V.norme_vecteur ( robots_base[i]->get_centre() , position.get_centre() ) ;
		if (V.get_norme() == 0 and robots_base[i] -> get_type() == 'T' and 
			robots_base[i] -> get_retour() == true )  		
		{
			ressources = ressources + deltaR; 
			robots_base[i]-> set_but ( GisementPlusLoin() );
			robots_base[i]-> set_retour(false);
			cout << robots_base[i] -> get_retour() << endl; 
		}
	}
} 

bool Base :: ForageAVider () {
	for ( size_t j(0); j < robots_base.size() ; j++ )
	{
		if ( robots_base[j]->get_type()=='F' and robots_base[j]->P_get_found()== true ){ 
			return true ;
		}	
	}
	return false;
}

Point Base :: GisementPlusLoin () 
{
	Vecteur V; 
	Point P; 
	double d_g_max (0); 
	for ( size_t i(0) ; i < robots_base.size() ; i++ )
	{
		if (robots_base[i]->get_type()== 'F' and robots_base[i]->P_get_found() == true 
			and robots_base[i] -> get_Connect() == true and 
			robots_base[i] -> get_jus()== true ) 
		{ 
			for ( size_t h (0) ; h < robots_base.size() ; h++ ) 
			{
				if (robots_base[h]->get_Connect()== true and 
					robots_base[h]-> get_type() == 'T' and 
					robots_base[h]->get_But().get_x() != robots_base[i]-> get_x() and 
					robots_base[h]-> get_But().get_y() != robots_base[i]-> get_y()) 				
				{
					V.norme_vecteur(position.get_centre(),
									robots_base[i]->get_centre()); 
					if ( V.get_norme() >  d_g_max ) 
					{
						P.set_coordonnes (	robots_base[i]-> get_centre().get_x() , 
											robots_base[i]-> get_centre().get_y() );
						d_g_max = V.get_norme(); 
					}
				}
			}
		}
	}
	return P; 
}

void Base :: TabRemoteOrAutonomous(){
	
	robots_remote.clear();
	robots_autonomous.clear();
	for ( size_t i(0) ; i < robots_base.size() ; i++ )
	{
		if ( robots_base[i] -> get_Connect() == true) 
		{
			robots_remote.push_back(robots_base[i] -> copie());
		} else {
			robots_autonomous.push_back(robots_base[i] -> copie());
		}
	} 
}


void Base :: lancement_p()
{
	shared_ptr<Prospecteur> prospecteur(nullptr);
	int i(0); 
	do{
		double x7 = position.get_x() + 10. ; 
		double y7 = position.get_y() + 10. ; 
		prospecteur= shared_ptr<Prospecteur>(	new Prospecteur(get_set_nv_max_uid(),0,
												position.get_x() , position.get_y(),x7,
												y7 , "false" , "false" , "false" , 
												0 , 0 , 0 , 0 ));
		robots_base.push_back(prospecteur);
		nbP = nbP + 1; 
		i = i + 3; 
		ressources = ressources - cost_prosp ; 
	} while ( i < 3 and nbP < 7) ;
}

shared_ptr<Robot> Base::get_robots_base(int i) const{
	return robots_base[i];
}

size_t Base::robots_size() const {
	return robots_base.size();
}

vector <shared_ptr<Robot>> Base::get_liste_robot() const{
	return robots_base;}



void Base::rec_DEF( shared_ptr <Base> B ,  shared_ptr <Robot> A ) 													
{
	for ( size_t i (0) ; i < B -> robots_base.size() ; i++ ){ 
		
		if ( B -> robots_base[i] -> get_uid() == A -> get_uid() ) {			
			
			B -> robots_base[i]-> set_Connect ( true ) ; 
		}
	}
	for ( size_t j(0) ; j < A -> size_voisin() ; j++ ){
	
		for ( size_t i (0) ; i < B -> robots_base.size() ; i++ ){  							
			
			if (B->robots_base[i]->get_uid()== A->voisin_uid(j) and 
				B-> robots_base[i] -> get_Connect() == false) {									 
																																															
				rec_DEF( B , B-> robots_base[i] ); 
				}
		}				
	}
}









