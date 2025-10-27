#ifndef	ROBOT_H
#define ROBOT_H

#include "geomod.h"
#include "constantes.h"
#include "gisement.h"

using namespace std;

class Robot{
	
	
	public:
	Robot ( int id ,double p ,double x ,double y ,double x1 ,double y1 ,string at);
	virtual ~ Robot(); 	
	virtual shared_ptr <Robot> copie()  = 0;
	
	void set_compteur_de_distance ( double dp ); 
	void set_robot_base ( bool f); 
	void set_but ( double x3 , double y3); 
	void set_but ( Point A ); 
	void set_Connect( bool a );
	void set_retour ( bool b ) ; 
	void set_jus ( bool b ) ; 
	void rentrer_base ();
	void set_base ( double xb , double yb ) ;
	double get_compteur_de_distance () const;
	int get_uid () const ; 
	
	virtual void deplacement_vers_but () = 0;
	
	Point get_centre() const;
	Point get_But () const; 
	
	bool transformationStringBool ( std::string A ) ;
	bool get_Comm_Base () const;
	bool get_Connect () ; 
	bool get_retour () ; 
	bool get_atteint () ; 
	bool get_jus () ; 
	
	char get_type (); 
	
	virtual void mode_autonome( vector < shared_ptr<Robot>  >& rob , 
								vector < shared_ptr <Gisement> > tabg ) = 0;  
	virtual void mode_remote ( 	vector < shared_ptr<Robot>  >& rob , 
								vector < shared_ptr <Gisement>> tabg ) = 0;
	virtual double P_get_xg () {return 0;};
	virtual double P_get_yg () { return 0;};
	virtual double P_get_taille () {return 0;};
	virtual double P_get_capacite () {return 0;};
	virtual bool P_get_found() {return true;};
	virtual void P_set_found ( bool a ) {}; 
	
	

	bool get_retour() const;
	double get_x() const;
	double get_y() const;
	double voisin_uid(int i) const ;
	shared_ptr<Robot> robot_voisins(int i ) const;
	void set_voisin(shared_ptr<Robot> voisin);
	size_t size_voisin() const;
	void clear_voisins();
	
		

	protected:
	vector <shared_ptr <Robot> > robots_voisins;
	
	int uid;  
	
	double compteur_de_distance;
	double x_base;
	double y_base; 
	
	Point pos;
	Point but; 
	
	char type;
	
	bool atteint;
	bool Connect;
	bool retour; 
	bool robot_base;
	bool jus ; 
};



class Prospecteur : public Robot 
{
	public:
	Prospecteur (	int id,double par,double x_1,double y_1,double x3,double y3,
					std::string a,std::string r,std::string f,double x4,double y4,
					double t,double c);
					
	Prospecteur(	int id,double par,double x_1,double y_1,double x3,double y3, 
					string a, string b,string c);
	~Prospecteur();
	 
	
	void mode_autonome( vector <shared_ptr<Robot> >& rob , 
						vector < shared_ptr <Gisement>> tabg ) override; 
	void mode_remote ( 	vector < shared_ptr<Robot>  >& rob , 
						vector < shared_ptr <Gisement> > tabg);
	void set_found ( bool i ); 
	void set_xg ( double x1 );
	void set_yg ( double y1 );
	void set_taille( double t ); 
	void set_capacite ( double c );
	void set_random_but(Vecteur V);

	
	bool get_found () const ; 
	
	virtual void deplacement_vers_but () override;

	virtual double P_get_xg () override;
	virtual double P_get_yg () override;
	virtual double P_get_taille () override;
	virtual double P_get_capacite () override;
	virtual bool P_get_found() override;
	virtual void P_set_found ( bool a ) override; 
	
	shared_ptr <Robot> copie() ;
	
	private: 
	bool found;
	double xg;
	double yg;
	double taille; 
	double capacite; 
 
};


class Forage : public Robot 
{
	public:
	Forage (int id,double par,double x_1,double y_1 , double x3,double y3,string a); 
	shared_ptr <Robot> copie() ;
	~Forage();
	void mode_autonome (vector < shared_ptr<Robot> >& rob , 
						vector < shared_ptr <Gisement> > tabg) override;
	void mode_remote ( 	vector < shared_ptr<Robot> >& rob ,
						vector < shared_ptr <Gisement> > tabg ) override;
	void GisementPlein ( shared_ptr <Gisement> C ) ; 
	void forage ( shared_ptr <Gisement> A ) ; 

	virtual void deplacement_vers_but () override;
	
	virtual double P_get_xg () override;
	virtual double P_get_yg () override;
	virtual double P_get_taille () override;
	virtual double P_get_capacite () override;
	virtual bool P_get_found() override;
	virtual void P_set_found ( bool a) override; 

	
	private : 
	bool plein;
};


class Transport : public Robot
{
	public:
	Transport (	int id,double par,double x_1,double y_1,double x3,double y3,string a,
				string r);
	shared_ptr<Robot> copie()  ;
	~Transport();
	void mode_autonome( vector < shared_ptr<Robot>  >& rob ,
						vector < shared_ptr <Gisement> > tabg ) override;
	void mode_remote ( 	vector < shared_ptr<Robot>  >& rob ,
						vector < shared_ptr <Gisement> > tabg );

	virtual void deplacement_vers_but () override;
	
	virtual double P_get_xg () override;
	virtual double P_get_yg () override;
	virtual double P_get_taille () override;
	virtual double P_get_capacite () override;
	virtual bool P_get_found() override;
	virtual void P_set_found (bool a ) override; 
	
	private :
	

};



class Communication : public Robot
{
	public:
	Communication (	int id,double par,double x_1,double y_1 , double x3,double y3,
					string a); 
	shared_ptr<Robot> copie() ;
	~Communication();
	void mode_autonome( vector < shared_ptr<Robot> >& rob ,
						vector < shared_ptr <Gisement> > tabg ) override;
	void mode_remote ( 	vector < shared_ptr<Robot> >& rob ,
						vector < shared_ptr <Gisement> > tabg ) override; 

	virtual void deplacement_vers_but () override;
	
	virtual double P_get_xg () override;
	virtual double P_get_yg () override;
	virtual double P_get_taille () override;
	virtual double P_get_capacite () override;
	virtual bool P_get_found() override;
	virtual void P_set_found ( bool a ) override; 
	
	private :
};

#endif
