# CXX=g++
# CPPFLAGS=-c -O2 -std=c++11 
# LIBS=-lsfml-graphics -lsfml-window -lsfml-system
# SOURCES=nwgui.cpp main.cpp graph_vis.cpp drawables.cpp application.cpp link.cpp node.cpp network.cpp parser.cpp libs/pugixml.cpp shortest_paths.cpp
# SOURCEHPP=nwgui.hpp graph_vis.hpp drawables.hpp application.hpp link.hpp node.hpp packet.hpp network.hpp event.hpp parser.hpp libs/pugixml.hpp shortest_paths.hpp
# OBJECTS=$(subst .cpp,.o,$(SOURCES))
# EXECUTABLE=main

# all: $(OBJECTS)
	# $(CXX) -o $(EXECUTABLE) $(OBJECTS)  $(LIBS)

# #these two recipes give all hpps to all object files	
# %.o: %.cpp
	# $(CXX) -c $< -o $@ $(CPPFLAGS)

# %.o: %.hpp
	# $(CXX) -c $< -o $@ $(CPPFLAGS)


# clean:
	# rm -f *.o $(EXECUTABLE)

# run: main
	# ./main
	
	
# CXX=g++
# CPPFLAGS= -O2 -std=c++11
# SOURCES=main.cpp 
# EXECUTABLE=main

# all: 
	# $(CXX) $(CPPFLAGS) -I ./eigen/ $(SOURCES) -o $(EXECUTABLE)

	
	
	
	
		
CXX=g++
CPPFLAGS= -O2 -std=c++11 -g
SOURCES=dist/jsoncpp.cpp main.cpp 
EXECUTABLE=main
OBJECTS = jsoncpp.o main.o

all: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o $(EXECUTABLE)

jsoncpp.o: dist/jsoncpp.cpp
	 $(CXX) -c $(CPPFLAGS) dist/jsoncpp.cpp 
	 
main.o: main.cpp 
	$(CXX) -c $(CPPFLAGS) -I ./eigen/ main.cpp


	
clean:
	rm -f *.o $(EXECUTABLE)
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	