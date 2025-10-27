#include <vector>
#include <iostream>
#include "scroll.h"

// ces lignes encadrées par l'option de compilation sont nécessaires pour GTKmm 3.

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

// ==============================================================================
// cette constante et le modèle de struct qui suit simulent les données que pourrait
// fournir le module simulation en réponse à une demande de tree_view_update()
constexpr unsigned max_tab(10);

struct SimData
{
  unsigned nbP;
  unsigned nbF;
  unsigned nbT;
  unsigned nbC;
  double ressource;
  double ressource_p;
};


// =================================


Scroll::Scroll()
     :_v_box(Gtk::ORIENTATION_VERTICAL, 10),
      m_button("Add one more"), count(0)
{
  set_title("démo scroll");
  // Sets the border width of the window. // cosmetique
  set_border_width(5);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this,
              &Scroll::on_button_clicked));

  add(_v_box);
 
  // This packs the buttonfirst into the vertical box
  _v_box.add(m_button);
  
  // This is the part for the scrolled_window
  _v_box.add(_scrolled_window);
  _scrolled_window.set_size_request(500, 200);  // replace 500 by -1 for the project
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
  if(progress_col)
	progress_col->add_attribute(cell->property_value(),
								_columns._col_resource_percentage);

  show_all_children();
}

Scroll::~Scroll()
{
}

// ==================== to adapt for the project  =====================================
// in this simple example, the button action increases a counter each time it is
// used. Then it asks to update the diaplay of the table of values.
// HOWEVER, for the project, many other causes should lead to such an update: file
// reading, simulation update, etc... For these reason the call to tree_view_update()
// should be done in the method on_draw of your GUI.

void Scroll::on_button_clicked()
{
  ++count;
  std::cout << "count value is now " << count << std::endl;
    
  tree_view_update(); // for the project, move this call in on_draw()
}

// the declaration below should not exist in your gui module; instead you should have a
// local vector declared in the method tree_view_update() and such a vector such be
// updated with the value returned by a call to your simulation module.

namespace
{
  static std::vector<SimData> report(max_tab); // init with zeros
}

// ===================== the parts to adapt have a comment ==================
void Scroll::tree_view_update()
{
  Glib::RefPtr<Gtk::ListStore> ref_tree_model = Gtk::ListStore::create(_columns);
  _tree_view.set_model(ref_tree_model);

  if(true) // here there should be a test about the existence of a simulation
  {
	// here a call to a method from your simulation class should create and 
	// return a vector like report, except its number of lines will be
	// determined by the simulation (not a constant like in this toy example).
	if(count > report.size()) 
		std::cout << max_tab << " lines max are displayed" << std::endl;

	for(size_t i = 0 ; i < count and i <report.size() ; ++i)
	{
	  report[i].nbP = i;
	  report[i].nbF = i;
	  report[i].nbT = i;
	  report[i].nbC = i;
	  report[i].ressource   = 1000*i;
	  report[i].ressource_p = 10*i;
		
	  auto row = *(ref_tree_model->append());
	  row[_columns._col_nbP] = report[i].nbP;
	  row[_columns._col_nbF] = report[i].nbF;
	  row[_columns._col_nbT] = report[i].nbT;
      row[_columns._col_nbC] = report[i].nbC;
	  row[_columns._col_resource] = report[i].ressource;
	  row[_columns._col_resource_percentage] = report[i].ressource_p;
	}
	
	// please note that you have to bring the mouse cursor to the right side 
	// of the scroll window to see the scrolling widget
  }
}
