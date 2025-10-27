# Definitions de macros
OUT = projet
CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`
OFILES = projet.o simulation.o message.o gisement.o geomod.o base.o robot.o gui.o graphic.o

# Definition de la premiere regle

all: $(OUT)


projet.o: projet.cc
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)


$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ prog

#
#-- Regles de dependances generees automatiquement

 #DO NOT DELETE THIS LINE

