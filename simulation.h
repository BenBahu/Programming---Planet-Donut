// simulation
// Auteurs : Georg Schwabedal et Daniel Silva


#ifndef SIMULATION
#define SIMULATION

#include "base.h"
#include "gisement.h"
#include "robot.h"
#include "constantes.h"
#include <memory>
#include "message.h"
#include <vector>
#include <string>

using namespace std;


class Simulation{
	
	public:
	
	Simulation();
	~Simulation();
	
	void simulation (); // Methode 	qui fait un "step"

	void lecture(char* nom);
	void set_etat (	int& etat, double nbP, double nbF, double nbT, double nbC,
					double bases);
	void decodage_ligne1(string line);
	void decodage_ligne2(string line);
	void TabRobotsConnectBases(shared_ptr<Base> A );
	void MajBase();
	
	void TabTotalRobot ();
	void VideTabTotalConnectFalse (); 
	
	void maintenance_bases ( shared_ptr<Base> A );
	void creation (shared_ptr<Base> A); 
	void update_remote ( shared_ptr<Base> A );
	void update_autonomous ( shared_ptr<Base> A);
	
	shared_ptr<Gisement> get_gisement(int  i);
	shared_ptr<Base> get_base(int i);
	size_t gisement_size();
	size_t base_size();	
	
	
	void ajout_base ( shared_ptr<Base> A );
	void ajout_gisement ( shared_ptr <Gisement> A);
	void verification (shared_ptr<Base> A);
	void AffichageRobots ();
	void set_erreur(int a);
	bool get_erreur();
	void reset_erreurs();


	private:
	int erreurs;
	bool erreur;
	vector < shared_ptr <Gisement>  > liste_gisement; 
	vector < shared_ptr<Base> > liste_base;
	vector < shared_ptr<Robot> > total_robots;										// ce vector est la pour assurer la conservation de l'information originelle des robots
	//void effacer ( shared_ptr<Base> A );									// sinon on se retrouve dans la situation dans laquelle les robots des 
										// premières bases ont déjà changé ( au sujet pt revoir le code de la fonction update voisins) 

};



	void update_voisins ( shared_ptr<Base> A );

	
	 
	
	
#endif


