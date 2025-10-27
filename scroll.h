#ifndef GTKMM_EXAMPLE_SCROLL_H
#define GTKMM_EXAMPLE_SCROLL_H

#include <gtkmm.h>

class Scroll : public Gtk::Window
{

public:
  Scroll();
  virtual ~Scroll();
  void tree_view_update(); // necessary for the project

private:
  //layout
  Gtk::Box _v_box;

  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Button m_button;
  
  // necessary for the project: internal class for private use of scrolledWindow
  class Model_columns : public Gtk::TreeModel::ColumnRecord
  {
   public:
     Model_columns()
     {
       add(_col_id);
       add(_col_nbP);
       add(_col_nbF);
       add(_col_nbT);
       add(_col_nbC);
       add(_col_resource);
       add(_col_resource_percentage);
     }

     Gtk::TreeModelColumn<int> _col_id;
     Gtk::TreeModelColumn<int> _col_nbP;
     Gtk::TreeModelColumn<int> _col_nbF;
     Gtk::TreeModelColumn<int> _col_nbT;
     Gtk::TreeModelColumn<int> _col_nbC;
     Gtk::TreeModelColumn<double> _col_resource;
     Gtk::TreeModelColumn<int> _col_resource_percentage;
  };

  Model_columns _columns;

  Gtk::ScrolledWindow _scrolled_window;
  Gtk::TreeView _tree_view;

  unsigned count;
};

#endif // GTKMM_EXAMPLE_SCROLL_H
