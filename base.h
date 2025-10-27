#ifndef BASE_H
#define BASE_H

#include "geomod.h"
#include "robot.h"
#include <fstream>
#include <memory>
#include "gisement.h"

using namespace std;



class Base {
	public:
	Base ( double x , double y , double r , int  P, int F , int T , int C );
	Cercle  get_cercle () const;
	Point get_centre() const ;

	double get_ressources() const;
	double get_x() const;
	double get_y() const;
	double get_nb_robot () ; 
	int get_set_nv_max_uid ();
	bool get_4G () ; 
		
	int get_nbP() const; 
	int get_nbC() const;
	int get_nbT() const;
	int get_nbF() const;
	
	bool ForageAVider () ;	
	bool get_vie () ;
	void set_vie ( bool a );
	Point GisementPlusLoin () ; 
		
	int robot_comm(vector < shared_ptr <Base> > listeB) ;
 
	void set_ressources ( double& ener );
	void MaJNbRobType (); 
	int ajout_robot ( shared_ptr<Robot> A ); 
	void Creation4G ();
	void maintenance () ; 
	void launch4G_3_supplemetaires ();
	void add_gisement_connus (); 
	void commande_gisement () ; 
	void trouver_max_uid ();
	void FindActive4G () ; 
	void ViderRobotsT () ; 
	void TabRemoteOrAutonomous ();
	void lancement_p();
	int get_couleur();
	void set_couleur(size_t i);
	bool decision_interet_gisement ( double x , double y , double r , double c ) ; 
	int generate_uid () ;
	int get_nb_robot() const;
	void saveBase1(ofstream& myfile);
	void saveBase2(ofstream& myfile);
	shared_ptr <Robot> get_robot(int i) const;

		
	~Base ();
	Base (const Base& other);
	
	size_t robots_size() const;
	shared_ptr<Robot> get_robots_base(int i) const;
	vector <shared_ptr<Robot>> get_liste_robot() const;
	void rec_DEF( shared_ptr<Base> B , shared_ptr <Robot> A );
		
		
	private:
	
	vector <shared_ptr<Robot> > robots_base;
	vector < shared_ptr<Robot> > robot_communication;
	vector < shared_ptr<Robot> > robots_remote;	
	vector < shared_ptr<Robot> > robots_autonomous;
	
	array<array<double , 3 > , 50 > Monde4G;
	
	int compteur;
	int max_uid; 
	int couleur;
	unsigned int nbP;
	unsigned int nbF;
	unsigned int nbT;
	unsigned int nbC;
	Cercle position;
	double ressources;
	bool Active4G; 
	bool vie; 
};
		
		string boolToString(bool a);
		vector <Cercle> getPositionsBases ( );
		
#endif


