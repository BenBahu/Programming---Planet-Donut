// projet.cc
// Auteurs : Georg Schwabedal et Daniel Silva


#include <iostream>
#include "geomod.h"
#include "simulation.h"
#include "message.h"
#include <gtkmm.h>
#include "gui.h"

using namespace std;

int main(int argc, char * argv[])
{
	shared_ptr<Simulation> sim = shared_ptr<Simulation>(new Simulation());
	auto app= Gtk::Application::create(); 
	
	if(argc == 2) sim->lecture(argv[1]);
		
	Windowx window;
	set_simulation(sim);								
	window.set_default_size(900, 900);

return app->run(window);}
