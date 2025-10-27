OUT = projet
CXX = g++
CXXFLAGS = -Wall -std=c++11 
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`
OFILES = projet.o simulation.o message.o gisement.o geomod.o base.o robot.o gui.o graphic.o 

all: $(OUT)

projet.o:  projet.cc geomod.h simulation.h message.h gisement.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

simulation.o: simulation.cc simulation.h gisement.h geomod.h robot.h \
 base.h constantes.h
		$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
	
message.o: message.cc message.h
		$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

gisement.o: gisement.cc message.h gisement.h geomod.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

geomod.o: geomod.cc geomod.h constantes.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

base.o: base.cc geomod.h base.h simulation.h gisement.h message.h \
 constantes.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

robot.o: robot.cc robot.h gisement.h geomod.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
	
gui.o: gui.cc gui.h 
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
	
graphic.o : graphic.cc graphic.h graphic_gui.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)



$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)

clean:
	@echo "Cleaning compilation files"
	@rm *.o $(OUT) *.cc~ *.h~

#
#-- Regles de dependances generees automatiquement

 #DO NOT DELETE THIS LINE






