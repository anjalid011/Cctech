CXX = g++
CXXFLAGS = -Wall -fPIC -Igeometry/include

GEOM_SRC = geometry/src
GEOM_INC = geometry/include
GEOM_LIB = geometry/lib
GEOM_SCRIPTS = geometry/scripts
APP_SRC = application


OBJS = $(GEOM_LIB)/Line.o $(GEOM_LIB)/Rectangle.o $(GEOM_LIB)/Cuboid.o

LIBGEOM = $(GEOM_LIB)/libgeometry.so

EXEC = $(APP_SRC)/main

all: $(LIBGEOM) $(EXEC)

$(GEOM_LIB)/Line.o: $(GEOM_SRC)/Line.cpp $(GEOM_INC)/Line.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Rectangle.o: $(GEOM_SRC)/Rectangle.cpp $(GEOM_INC)/Rectangle.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Cuboid.o: $(GEOM_SRC)/Cuboid.cpp $(GEOM_INC)/Cuboid.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIBGEOM): $(OBJS)
	$(CXX) -shared -o $@ $^

$(EXEC): $(APP_SRC)/main.cpp $(LIBGEOM)
	$(CXX) -o $@ $(APP_SRC)/main.cpp -I$(GEOM_INC) -L$(GEOM_LIB) -lgeometry

run:
	cd application && ./main

clean:
	rm -f $(OBJS) $(LIBGEOM) $(EXEC) geometry/scripts/*.txt

