CXX = g++
CXXFLAGS = -Wall -fPIC -Igeometry/include

GEOM_SRC = geometry/src
GEOM_INC = geometry/include
GEOM_LIB = geometry/lib
GEOM_SCRIPTS = geometry/scripts
APP_SRC = application

OBJS = $(GEOM_LIB)/Line.o $(GEOM_LIB)/Rectangle.o $(GEOM_LIB)/Cuboid.o $(GEOM_LIB)/Circle.o $(GEOM_LIB)/Cone.o $(GEOM_LIB)/Sphere.o $(GEOM_LIB)/Transformations.o $(GEOM_LIB)/Plotter.o $(GEOM_LIB)/Cylinder.o $(GEOM_LIB)/StlToDat.o $(GEOM_LIB)/Robot.o $(GEOM_LIB)/ObjToStl.o

LIBGEOM = $(GEOM_LIB)/libgeometry.so
EXEC = $(APP_SRC)/main

all: $(GEOM_LIB) $(LIBGEOM) $(EXEC)

$(GEOM_LIB):
	mkdir -p $(GEOM_LIB)  # Ensures that the geometry/lib directory exists

$(GEOM_LIB)/Line.o: $(GEOM_SRC)/Line.cpp $(GEOM_INC)/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Rectangle.o: $(GEOM_SRC)/Rectangle.cpp $(GEOM_INC)/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Cuboid.o: $(GEOM_SRC)/Cuboid.cpp $(GEOM_INC)/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Sphere.o: $(GEOM_SRC)/Sphere.cpp $(GEOM_INC)/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Circle.o: $(GEOM_SRC)/Circle.cpp $(GEOM_INC)/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Cone.o: $(GEOM_SRC)/Cone.cpp $(GEOM_INC)/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Cylinder.o: $(GEOM_SRC)/Cylinder.cpp $(GEOM_INC)/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Transformations.o: $(GEOM_SRC)/Transformations.cpp $(GEOM_INC)/Transformations.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Plotter.o: $(GEOM_SRC)/Plotter.cpp $(GEOM_INC)/Plotter.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/StlToDat.o: $(GEOM_SRC)/StlToDat.cpp $(GEOM_INC)/StlToDat.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Robot.o: $(GEOM_SRC)/Robot.cpp $(GEOM_INC)/Robot.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/ObjToStl.o: $(GEOM_SRC)/ObjToStl.cpp $(GEOM_INC)/ObjToStl.h
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(LIBGEOM): $(OBJS)
	$(CXX) -shared -o $@ $^

$(EXEC): $(APP_SRC)/main.cpp $(LIBGEOM)
	$(CXX) -o $@ $(APP_SRC)/main.cpp -I$(GEOM_INC) -L$(GEOM_LIB) -lgeometry

run:
	cd application && ./main

clean:
	rm -f $(OBJS) $(LIBGEOM) $(EXEC) $(GEOM_SCRIPTS)/*.dat $(GEOM_SCRIPTS)/*.stl
	

