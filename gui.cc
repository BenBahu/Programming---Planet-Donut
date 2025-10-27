// projet.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include "gui.h"
#include "graphic.h"
#include "geomod.h"
#include "simulation.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>
#include <cairomm/context.h>

using namespace std;

#define GTK_COMPATIBILITY_MODE

#ifdef GTK_COMPATIBILITY_MODE
namespace Gtk
{
  template<class T, class... T_Args>
  auto make_managed(T_Args&&... args) -> T*
  {
    return manage(new T(std::forward<T_Args>(args)...));
  }
}
#endif

namespace {
	//size_t count2(4);
	constexpr int DEFAULT_SIZE(800);
	int count3(0);
	shared_ptr<Simulation> sim(nullptr);	
	bool link2(true), range (true),started(false),step(false);
}


// Fonctions de la fenetre
Windowx::Windowx()
:	m_box(Gtk::ORIENTATION_VERTICAL),
	m_box_Bottom(Gtk::ORIENTATION_VERTICAL,5),
	m_box_Top(Gtk::ORIENTATION_HORIZONTAL,5),
	m_box_Button(Gtk::ORIENTATION_VERTICAL,5)
{
	set_title("Planet Donut");			
	add(m_box);							
	m_box.set_border_width(5);
	m_box.add(m_box_Top);
	m_box.add(m_box_Bottom);
	m_box_Top.add(m_box_Button);
	m_box_Button.add(m_box_General);
	m_box_Button.add(m_box_Display);
	m_box_Bottom.add(scroll);
	
	//Ajoute les boutons de General et Toggle Display dans un box
	m_box_General.pack_start(	*Gtk::manage( new ButtonBox(false, "General", 5,		
			Gtk::BUTTONBOX_SPREAD)), Gtk::PACK_EXPAND_WIDGET);
			
	m_box_Display.pack_start(*Gtk::manage( new ButtonBox2(false, "Toggle Display", 5,
			Gtk::BUTTONBOX_SPREAD)), Gtk::PACK_EXPAND_WIDGET);

	m_box_Top.add(m_Frame_Horizontal);
	//Ce frame contient la surface de dessin 
	set_default_size(DEFAULT_SIZE, DEFAULT_SIZE);
	m_Frame_Horizontal.add(Area);
    m_Frame_Horizontal.set_hexpand(true); 
   
    m_Frame_Horizontal.set_halign(Gtk::ALIGN_FILL);
	m_Frame_Horizontal.set_vexpand(true);
    m_Frame_Horizontal.set_valign(Gtk::ALIGN_FILL);
  show_all_children();
  
  // updating a simulation in idle signal handler - called as quickly as possible
  Glib::signal_idle().connect( sigc::mem_fun(*this, &Windowx::on_idle));

}

// Keyboard signal handler:
bool ButtonBox::on_key_press_event(GdkEventKey * key_event)
{
	if(key_event->type == GDK_KEY_PRESS)
	{
		switch(gdk_keyval_to_unicode(key_event->keyval))
		{
			case 's':
				started=not(started);
				if (started) m_Button_Start.set_label("Stop");
				else m_Button_Start.set_label("Start");
				break;
			case '1':
				step=not(step);
				break;
		}
	}
	return true;
}


Windowx::~Windowx()
{
}

bool Windowx::on_idle()			// méthode de gtkm qui est apellé tout le temps 
								// faite pour mettre à jour la fenêtre 
{
	static unsigned count(0);
	if(not (sim==nullptr)){
		if(started)
		{	++count3;
			cout << "Mise à jour de la simulation numéro : " << ++count << endl;
			sim->simulation();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		else if (step )
		{
			step = false;
			sim->simulation();
			cout << "Mise à jour de la simulation numéro : " << ++count << endl;
		}
  
	Area.refresh();		// mise à jour 
	//scroll.tree_view_update();
	}
	scroll.tree_view_update();

  return true;  // return false when done
}

// Fonctions du widget scroll
// ==============================================================================


Scroll::Scroll()
     :_v_box(Gtk::ORIENTATION_VERTICAL, 10)
{
	add(_v_box);
	// This is the part for the scrolled_window
	_v_box.add(_scrolled_window);
	_scrolled_window.set_size_request(-1, 200); 
	_scrolled_window.add(_tree_view);

	_scrolled_window.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC,
								  Gtk::PolicyType::POLICY_AUTOMATIC);
	_scrolled_window.set_hexpand();

	_tree_view.append_column("nbP", _columns._col_nbP);
	_tree_view.append_column("nbF", _columns._col_nbF);
	_tree_view.append_column("nbT", _columns._col_nbT);
	_tree_view.append_column("nbC", _columns._col_nbC);
	_tree_view.append_column_numeric("Amount resource", _columns._col_resource, "%.2f");

	  auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
	  int cols_count = _tree_view.append_column("Mission completeness", *cell);

	auto progress_col = _tree_view.get_column(cols_count - 1);
	if(progress_col) progress_col->add_attribute(cell->property_value(),
								_columns._col_resource_percentage);
	
	
	show_all_children();
}

Scroll::~Scroll(){}

void Scroll::tree_view_update()
{
	Glib::RefPtr<Gtk::ListStore> ref_tree_model = Gtk::ListStore::create(_columns);
	_tree_view.set_model(ref_tree_model);
	
	if(not(sim == nullptr)){   
		for(size_t i = 0 ; i <sim->base_size() ; i++)
		{
			double ressource   = sim->get_base(i)->get_ressources();
			double ressource_p = ressource *100/finR;
		
		  auto row = *(ref_tree_model->append());
		  row[_columns._col_nbP] = sim->get_base(i)->get_nbP();
		  row[_columns._col_nbF] = sim->get_base(i)->get_nbF();
		  row[_columns._col_nbT] = sim->get_base(i)->get_nbT();
		  row[_columns._col_nbC] = sim->get_base(i)->get_nbC();
		  row[_columns._col_resource] = ressource;
		  row[_columns._col_resource_percentage] = ressource_p;
		}
  } else  {
		  auto row = *(ref_tree_model->append());
		  row[_columns._col_nbP] = 0;
		  row[_columns._col_nbF] = 0;
		  row[_columns._col_nbT] = 0;
		  row[_columns._col_nbC] = 0;
		  row[_columns._col_resource] = 0;
		  row[_columns._col_resource_percentage] = 0;
	 }
}


//Fonctions de la ButtonBox contenant les boutons Exit, Save, Open, Step et Start 
ButtonBox::ButtonBox(	bool horizontal, const Glib::ustring& title,
									gint spacing,  Gtk::ButtonBoxStyle layout)
: 	Gtk::Frame(title),
	m_Button_Exit("Exit"),

	m_Button_Open("Open"),
	m_Button_Step("Step"),
	m_Button_Save("Save")

{
	Gtk::ButtonBox* bbox = nullptr;
	m_Button_Start.set_label("Start");
	bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );

	bbox->set_border_width(5);

	set_halign(Gtk::ALIGN_FILL);
	 
	add(*bbox);
	m_Button_Exit.signal_clicked().connect(	sigc::mem_fun(*this, 
											&ButtonBox::on_button_clicked_Exit) );
	m_Button_Open.signal_clicked().connect(	sigc::mem_fun(*this, 
											&ButtonBox::on_button_clicked_Open) );
	m_Button_Save.signal_clicked().connect(	sigc::mem_fun(*this, 
											&ButtonBox::on_button_clicked_Save) );
	m_Button_Start.signal_clicked().connect(sigc::mem_fun(*this, 
											&ButtonBox::on_button_clicked_Start) );
	m_Button_Step.signal_clicked().connect(	sigc::mem_fun(*this, 
											&ButtonBox::on_button_clicked_Step) );

	/* Set the appearance of the Button Box */
	bbox->set_layout(layout);
	bbox->set_spacing(5);
	bbox->add(m_Button_Exit);
	bbox->add(m_Button_Start);
	bbox->add(m_Button_Open);
	bbox->add(m_Button_Step);
	bbox->add(m_Button_Save);
}

void ButtonBox::on_button_clicked_Exit(){
	exit(EXIT_SUCCESS);
}

void ButtonBox::on_button_clicked_Open(){
	started=false;
	m_Button_Start.set_label("Start");
	
	Gtk::FileChooserDialog dialog(	"Please choose a file",
									Gtk::FILE_CHOOSER_ACTION_OPEN);
	
	auto *win = dynamic_cast<Gtk::Window *>(this->get_toplevel());
	dialog.set_transient_for( *win);
	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);
	m_Label_Info.set_text("choosing a file");
	//Show the dialog and wait for a user response:
	int result = dialog.run();

	m_Label_Info.set_text("Done choosing a file");
	 //Handle the response:
	switch(result){
		case(Gtk::RESPONSE_OK):
		{
			cout << "Open clicked." << endl;
			istringstream data(dialog.get_filename());   
			string line ;
			while (getline (data,line,'/')){}
			char argv[line.length()+1];	
			char* filename = argv;
			for (size_t i=0; i< line.length(); i++) argv[i]= line[i];
			argv[line.length()]= '\0';
			cout << "File selected: " <<  line << endl;
			sim=shared_ptr<Simulation>(new Simulation());
			sim->lecture(filename);	
			if (sim->get_erreur()) {
				sim= nullptr;
			}
			break;
		}
		case(Gtk::RESPONSE_CANCEL):{
			cout << "Cancel clicked." << endl;
			break;
		}
		default:{
			cout << "Unexpected button clicked." << endl;
			break;
		}
	}
}

void ButtonBox::on_button_clicked_Save(){
	started=false;
	m_Button_Start.set_label("Start");
	
	Gtk::FileChooserDialog dialog(	"Please choose a file",
									Gtk::FILE_CHOOSER_ACTION_SAVE);
	auto *win = dynamic_cast<Gtk::Window *>(this->get_toplevel());
	dialog.set_transient_for( *win);					
	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Save", Gtk::RESPONSE_OK);
	m_Label_Info.set_text("choosing a file");
	//Show the dialog and wait for a user response:
	int result = dialog.run();

	m_Label_Info.set_text("Done choosing a file");
	 //Handle the response:
		switch(result){
		case(Gtk::RESPONSE_OK):
		{	
			cout << "Save clicked." << endl;
			istringstream data(dialog.get_filename());   
			string line ;
			while (getline (data,line,'/')){}
			char argv[line.length()+1];	
			char* filename = argv;
			for (size_t i=0; i< line.length(); i++) argv[i]= line[i];
			
			argv[line.length()]= '\0';
			save(filename);

			break;
		}
		case(Gtk::RESPONSE_CANCEL):{
			cout << "Cancel clicked." << endl;
			break;
		}
		default:{
			cout << "Unexpected button clicked." << endl;
			break;
		}
	}
}

void ButtonBox::on_button_clicked_Start(){ 
	started=not(started);
	if (started) m_Button_Start.set_label("Stop");
	else m_Button_Start.set_label("Start");
}

void ButtonBox::on_button_clicked_Step(){
	step=not(step);
}

//Fonctions de la ButtonBox contenant les boutons Toggle link et Toggle range

ButtonBox2::ButtonBox2(	bool horizontal, const Glib::ustring& title,
									gint spacing,  Gtk::ButtonBoxStyle layout)
: 	Gtk::Frame(title),
	m_Button_Link("Toggle link"),
	m_Button_Range("Toggle range")
{
	Gtk::ButtonBox* bbox2=Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL));

	bbox2->set_border_width(1);

	add(*bbox2);
	this->set_valign(Gtk::ALIGN_FILL);
	m_Button_Link.signal_clicked().connect(	sigc::mem_fun(*this, 
											&ButtonBox2::on_button_clicked_Link) );
											
	m_Button_Range.signal_clicked().connect(sigc::mem_fun(*this, 
											&ButtonBox2::on_button_clicked_Range) );

	/* Set the appearance of the Button Box */
	bbox2->set_layout(Gtk::BUTTONBOX_EXPAND);
	bbox2->set_spacing(1);
	bbox2->add(m_Button_Link);
	bbox2->add(m_Button_Range);

}

void ButtonBox2::on_button_clicked_Link(){
	link2=not (link2);
	}

void ButtonBox2::on_button_clicked_Range(){
	range=not(range);
}

//Fonctions de la DrawingArea

MyArea::MyArea(){}

MyArea::~MyArea(){}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();	
	graphic_set_context(cr);
	orthographic_projection(cr,DEFAULT_SIZE, DEFAULT_SIZE);
	dessin_cadre(height,width);
	if (not (sim==nullptr)){
		draw_gisements(height,width);
		draw_bases(height, width);
		cr->set_source_rgb(0,0,0);
	}

	
  return true;
}

//Convertion du systeme d'axe de DrawingArea vers celle de Planet Donut
void MyArea::orthographic_projection(	const Cairo::RefPtr<Cairo::Context>& cr,
										double width, double height)
{
	double xMax(dim_max),xMin(-dim_max),yMax(dim_max),yMin(-dim_max);
	
	// déplace l'origine au centre de la fenêtre
	cr->translate(width/2, height/2);
  
	// normalise la largeur et hauteur aux valeurs fournies par le cadrage
	// ET inverse la direction de l'axe Y
	cr->scale(width/(xMax - xMin), -height/(yMax - yMin));
  
	// décalage au centre du cadrage
	cr->translate(-(xMin + xMax)/2, -(yMin +yMax)/2);
}


void MyArea::refresh()
{
  auto win = get_window();
  if(win)
  {
	  Gdk::Rectangle r(0,0, get_allocation().get_width(), 
	                        get_allocation().get_height());
	  win->invalidate_rect(r,false);
  }
}

void set_simulation(shared_ptr<Simulation> simulation){
	sim = simulation ;
}

void save(char* filename){
	ofstream myfile;
	myfile.open (filename);
	if (sim->gisement_size()>0) myfile<<sim->gisement_size()<<"\n";
	//Save Gisements
	for (size_t i(0); i< sim->gisement_size(); i++){
		myfile<<sim->get_gisement(i)->get_x()<< " ";
		myfile<<sim->get_gisement(i)->get_y()<<" ";
		myfile<<sim->get_gisement(i)->get_rayon()<<" ";
		myfile<< sim->get_gisement(i)->get_qt_resources()<<"\n";}
	
	//Save Bases
	if (sim->base_size()>0) myfile<<sim->base_size()<<"\n";
	for (size_t i(0); i< sim->base_size() ; i++){
			sim->get_base(i)->saveBase1(myfile);
		}
	myfile.close();
}

void draw_bases(int height, int width){
	for (size_t i(0); i<sim->base_size(); i++){ 
		set_couleur_base(sim->get_base(i)->get_couleur());
		sim->get_base(i)->get_cercle().get_centre().dessin('B', 10*rayon_base);
		
		//Dessine les robots
		for(int j(0);j <sim-> get_base(i)->get_nb_robot(); j++){
			char C = sim->get_base(i)->get_robot(j)->get_type();
			sim->get_base(i)->get_robot(j)->get_centre().dessin(C, rayon_comm);
			set_couleur_base(sim->get_base(i)->get_couleur());
			if (range){
				sim->get_base(i)->get_robot(j)->get_centre().dessin('R', rayon_comm);
				}
				set_couleur_base(sim->get_base(i)->get_couleur());
			for(size_t k(0); k < sim-> get_base(i)->get_robot(j)->size_voisin();k++){
				Vecteur V;
				V.norme_vecteur(sim->get_base(i)->get_robot(j)->get_centre(),
								sim->get_base(i)->get_robot(j)->robot_voisins(k)
								->get_centre());
				
				if (link2) {
					V.dessin();
					set_couleur_base(sim->get_base(i)->get_couleur());
				}
			}
		}
	}
}
	

void draw_gisements(int height, int width){
	//Desssine les gisements
	for (size_t i(0); i<sim->gisement_size(); i++){
		double vie = sim->get_gisement(i)->get_vie();
		sim->get_gisement(i)->getCercleG().dessin(	'G', sim->get_gisement(i)->
													get_rayon(),vie);
	}
}

