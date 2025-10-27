// simulation.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include <sstream>
#include <fstream>
#include "simulation.h"

using namespace std;


namespace{
	enum Etat_lecture {	NB_GISEMENT,GISEMENTS,NB_BASE,BASE,DEF,
						ROBOTP,ROBOTF,ROBOTT,ROBOTC,FIN};
	
	static int etat1(NB_GISEMENT), etat2(NB_BASE);
	static int base2(0);
};

Simulation::Simulation(){
	erreurs= 0;
	erreur= false;}

Simulation::~Simulation(){}

void Simulation::lecture(char* nom)
{
	set_max(dim_max);
    string line;
    ifstream fichier(nom); 
    if(fichier.fail()) exit(EXIT_FAILURE);
   
	while(getline(fichier >> ws,line)) 
       {
		// ligne de commentaire à ignorer, on passe à la suivante
		if(line[0]=='#')  continue; 
		decodage_ligne1(line);
		if (erreurs > 0) continue;
        }
    //Verification que toutes les bases ont un robot de comm au centre
    for (size_t i(0); i<liste_base.size(); i++){
		erreurs+=liste_base[i] -> robot_comm(liste_base);
		liste_base[i]->set_couleur(i);
	}
	//Remises des etats a leur valeur initiales afin de permettre 
	//la lecture d'un deuxieme fichier
	etat1= NB_GISEMENT;
	etat2= NB_BASE;
	base2=0;
	if (erreurs > 0) erreur = true;
	
}

//Fonction qui definit l'etat du switch de l'automate de lecture
void Simulation::set_etat (	int& etat2, double nbP, double nbF, double nbT, double nbC, 
				double bases){
	switch(etat2){
		case BASE:
			if (nbP>0) etat2 = ROBOTP;
			else if (nbF>0) etat2 = ROBOTF;
			else if (nbT>0) etat2 = ROBOTT;
			else if (nbC>0)etat2 = ROBOTC;
			else etat2= BASE;
			break;
					
		case ROBOTP:
			if (nbF>0) etat2 = ROBOTF;
			else if (nbT>0) etat2 = ROBOTT;
			else if (nbC>0)etat2 = ROBOTC;
			else etat2 = BASE;
			break;
					
		
		case ROBOTT:
			if (nbC>0)etat2 = ROBOTC;
			else etat2 = BASE;
			break;
	
		case ROBOTF:
			if (nbT>0) etat2 = ROBOTT;
			else if (nbC>0)etat2 = ROBOTC;
			else etat2 = BASE;
			break;
		
		case ROBOTC:
			etat2 = BASE;
			break;
	}
}

//Automate de lecture pour les gisement
void Simulation::decodage_ligne1(string line){
	istringstream data(line);
	static int nombre(0), g(0);	
	static double x(0), y(0) ,rayon(0) ,ressource(0);
	switch(etat1) {
		case NB_GISEMENT:
			data >> nombre;
			etat1=GISEMENTS;
			if (nombre == 0) etat1=DEF;
			break;
			
		case GISEMENTS:
			data>>x>>y>>rayon>>ressource;
			//cout << x <<" "<< y <<endl;
			if (g<nombre) g++;
			ajout_gisement(shared_ptr<Gisement>( new Gisement(x,y,rayon, ressource)));
			if (g==nombre) etat1=DEF;
			break;
			
		case DEF:
			//cout<<"Coucou"<<endl;
			g=0;
			nombre=0;
			decodage_ligne2(line);
			break;
	}
}

//Automate de lecture pour les bases et les robots

void Simulation::decodage_ligne2(string line){		
	
	istringstream data(line);
	static double x(0) ,y(0) ,ressource(0),nbP(0) , nbT(0), nbC(0), nbF(0), dp(0), 
	uid(0), xb(0), yb(0),nb_robots(0), xg(0),yg(0),rayong(0),capaciteg(0),nombre(0);			
	static string atteint,retour,found;
	
	switch (etat2){
		case NB_BASE:
			data >> nombre;
			etat2= BASE;
			break;
		case BASE:
			if (base2 <=nombre){
				data>>x>>y>>ressource>>nbP>>nbF>>nbT>>nbC;
				ajout_base(shared_ptr<Base>(new Base(x,y,ressource,nbP,nbF, nbT,nbC)));
				if (nbC == 0) {
					cout<<message::missing_robot_communication(liste_base[base2]
																->get_x(),
																liste_base[base2]
																->get_y());
					++erreurs;
				}
				set_etat(etat2, nbP, nbF, nbT, nbC,base2);
				nb_robots=0;
				++base2;
				} 
			else break;
			break;
			
		case ROBOTP:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint>>retour>>found;
			if (found =="false") { 
				liste_base[base2-1]->ajout_robot(shared_ptr<Prospecteur>(new 
														Prospecteur(uid,dp,x,y,xb,yb,
														atteint,retour,found)));}	
			else { 
				data>>xg>>yg>>rayong>>capaciteg;
				liste_base[base2-1]->ajout_robot(shared_ptr<Prospecteur>(new 
														Prospecteur(uid,dp,x,y,xb,yb,
														atteint,retour,found,xg,yg,
														rayong,capaciteg)));}
			if (nb_robots+1==nbP) {
				set_etat(etat2, nbP, nbF, nbT, nbC,base2);			
				nb_robots=0;
				break;} 
			nb_robots++;
			break;
			
		case ROBOTF:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint;
			liste_base[base2-1] -> ajout_robot(shared_ptr<Forage>(new Forage(uid, dp,x,
																	y,xb,yb,atteint)));
			if (nb_robots+1==nbF) {
				nb_robots=0;
				set_etat(etat2, nbP, nbF, nbT, nbC,base2);
				break;}
			else nb_robots++;
			break;
	
		case ROBOTT:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint>>retour;
			liste_base[base2-1] -> ajout_robot(shared_ptr<Transport>(new Transport(uid,
												dp,x,y,xb,yb,atteint,retour)));
			if (nb_robots+1==nbT) {
				nb_robots=0;
				set_etat(etat2, nbP, nbF, nbT, nbC,base2);			
				break;}
			 else  nb_robots++;
			break;
			
		case ROBOTC:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint;
			liste_base[base2-1] -> ajout_robot(shared_ptr<Communication>(new 
										Communication(uid,dp,x,y,xb,yb,atteint)));
			if (nb_robots+1==nbC) {
				set_etat(etat2, nbP, nbF, nbT, nbC,base2);
				nb_robots=0;			
				break;}
			else nb_robots++;
			break;
	}		
}

void Simulation::ajout_gisement ( shared_ptr<Gisement> A) 
{
	bool presence (false);
	int tmp(0);
	for ( size_t i (0); i < liste_gisement.size() ; i++ ){
	 if (intersection_deux_cercles(A ->getCercleG(),liste_gisement[i]->getCercleG())){

				presence = true; 
				tmp= static_cast<int>(i);
			}	
	}
	if ( presence == false) {
		
		liste_gisement.push_back( A );
		
	
	} else {
		std::cout<<message::field_superposition(A -> getCercleG().get_x(), 
							A -> getCercleG().get_y(),liste_gisement[tmp] -> 
							getCercleG().get_x(),liste_gisement[tmp] -> 
							getCercleG().get_y());
		++erreurs;
	} 
	
};
void Simulation::MajBase(){
	for(size_t i(0);i< liste_base.size(); i++){
		if (liste_base[i]->get_ressources()<=0){
				
			liste_base[i]->set_vie(false);
		}
	}
	vector <shared_ptr<Base>> liste;
	for (size_t i(0) ; i < liste_base.size(); i++){
		if (liste_base[i]->get_vie()){
			liste.push_back(liste_base[i]);
		}
	}
	liste_base = liste;
}

void Simulation::set_erreur(int a){
	erreur=erreur+a;
}

void Simulation::reset_erreurs(){
	erreurs=0;
	erreur= false;
}
shared_ptr<Gisement> Simulation::get_gisement(int i){
	return liste_gisement[i];
}

shared_ptr<Base> Simulation::get_base(int i){
	return liste_base[i];
}

size_t Simulation::gisement_size(){
	return liste_gisement.size();
}

size_t Simulation::base_size(){
	return liste_base.size();
}

void Simulation :: TabRobotsConnectBases( shared_ptr<Base> A )
{

	for ( size_t l(0) ; l < A->robots_size() ; l++ ) 
	{
		A->get_robots_base(l)-> set_Connect(false);
	}
	
	for ( size_t i(0) ; i< A -> robots_size() ; i++ ) 
	{
		Vecteur V; 
		bool fin (false); 
		if (V.egalite(A->get_centre(),A->get_robots_base(i)->get_centre() )== true and 
			fin == false)
		{
			A->rec_DEF(A ,  A -> get_robots_base(i)); 
		}
	}
}

void Simulation :: TabTotalRobot () 
{
for ( size_t i(0) ; i < liste_base.size() ; i++ ) 
	{
		for (size_t j( 0) ; j < liste_base[i] -> robots_size() ; j++ ) 
		{ 
		total_robots.push_back( liste_base[i] -> get_robots_base(j) );  
		}
	}
}

void Simulation :: creation (shared_ptr<Base> A) 																				
{


	for ( size_t i(0); i < A -> robots_size() ; i++ ){																		 
			A -> get_robots_base(i) -> set_base (  A-> get_x() , A -> get_y() );  
	}
	
	A -> TabRemoteOrAutonomous () ;															
	A -> MaJNbRobType();	
	A -> Creation4G(); 																						
	A -> FindActive4G();																				
	
	
	if ((A->get_4G()==false and A->get_ressources()>= 250 )  or 
		(A->get_ressources()>60. and A->get_nbF()== 1 and A-> get_nbT() == 1  
		and A -> get_4G() == false)){										
		A -> launch4G_3_supplemetaires(); 																
	}
	else if ((	A->get_nbP()<4 and A->get_ressources()>=200) or (A->get_nbP()<4 and 
				A->get_ressources()>30 and A->get_nbF() == 1 and A->get_nbT() ==1 )){  	
		A -> lancement_p(); 			 																	
	}
	else if ( A -> get_ressources() > 210)
	{					
		A-> commande_gisement();
	}	
}



void Simulation :: VideTabTotalConnectFalse ()
{
	for ( size_t i(0)  ; i < total_robots.size() ; i ++ ) 
	{
		total_robots[i] -> set_Connect(false); 
	}
}


void Simulation :: maintenance_bases ( shared_ptr<Base> A )
{
	 A -> maintenance (); 																				
}


void Simulation :: update_autonomous ( shared_ptr<Base> A )														
{
	for ( size_t j(0) ; j < A -> robots_size() ; j++ )									
	{
		if ( A-> get_robots_base(j) -> get_Connect() == false ) 
			{
				vector<shared_ptr<Robot>> liste =A->get_liste_robot();
			A->get_robots_base(j)->mode_autonome(liste,liste_gisement);
		}											 								
	}	
}

void Simulation :: update_remote ( shared_ptr<Base> A )
{
	for ( size_t j(0) ; j < A -> robots_size() ; j++ )										
	{
		if ( A-> get_robots_base(j) -> get_Connect() == true ) 
		{
			vector<shared_ptr<Robot>> liste =A->get_liste_robot();
			A->get_robots_base(j)->mode_remote(liste,liste_gisement );
		}											 							
	}

}


void update_voisins ( shared_ptr<Base> A ) 																	
{ 
	Vecteur V; 																								
	for ( size_t i (0) ; i < A -> robots_size() ; ++i ){ 												
		A -> get_robots_base(i) -> clear_voisins();																								
		for ( size_t j (0) ; j < A -> robots_size() ; ++j ){										
			
			V.norme_vecteur(A -> get_robots_base(i) -> get_centre() , 
							A -> get_robots_base(j)-> get_centre() ); 					
																																 
																																									
			if ( V.get_norme() <= rayon_comm ) 																				 
			{
				if (A-> get_robots_base(i) -> get_uid() == 
					A -> get_robots_base(j) -> get_uid()){} 
																																									
				else {																																    
					A->get_robots_base(i)-> set_voisin(A->get_robots_base(j)->copie());
					 																 
				}							
			}
		}
	}	
}


void Simulation::ajout_base ( shared_ptr<Base> A ){

	bool intersection_base (false),intersection_gisement(false);
	int base(0),gisement(0);
	
	//Verification d'intersection base-gisement
	for ( size_t i (0); i < liste_gisement.size() ; i++ ){
		if(intersection_deux_cercles(A->get_cercle(),liste_gisement[i]->getCercleG())){
			intersection_gisement = true; 
			gisement= static_cast<int>(i);
		}
	}
	for ( size_t i (0); i < liste_base.size() ; i++ ){
		if (intersection_deux_cercles (A->get_cercle(),liste_base[i]->get_cercle())){

			intersection_base = true; 
			base= static_cast<int>(i);			
		}		
	}
	//Verification d'intersection gisement-gisement		
	if (intersection_gisement==true){
		std::cout<<message::base_field_superposition(A->get_x(),A->get_y(),
													liste_gisement[gisement]->get_x(),
													liste_gisement[gisement]->get_y());
		++erreurs;
	}
	else if (intersection_base==true){
		std::cout<<message::base_superposition(	A -> get_x(), A-> get_y(),
												liste_base[base] -> get_x(),
												liste_base[base] -> get_y());
		++erreurs;
	} 
	else if ( intersection_base == false) {
		liste_base.push_back( A );
	}
}


bool Simulation::get_erreur(){
	return erreur;
}



void Simulation :: simulation ()
{
	TabTotalRobot();									
	for ( size_t i(0) ; i < liste_base.size() ; i++ ){
	
		for ( size_t j(0) ; j < liste_base.size() ; j++) {
			update_voisins ( liste_base[i]); 									
		}		

		TabRobotsConnectBases(liste_base[i]); 									
		maintenance_bases(liste_base[i]); 
		creation (liste_base[i]) ;															
		update_remote (liste_base[i]);	
		update_autonomous ( liste_base[i]); 		
		MajBase();
	}
}









