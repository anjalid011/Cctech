CXX = g++
CXXFLAGS = -Wall -Igeometry/include -D_USE_MATH_DEFINES

GEOM_SRC = geometry/src
GEOM_INC = geometry/include
GEOM_LIB = geometry/lib
GEOM_SCRIPTS = geometry/scripts
APP_SRC = application

OBJS = $(GEOM_LIB)/Line.o $(GEOM_LIB)/Rectangle.o $(GEOM_LIB)/Cuboid.o $(GEOM_LIB)/Circle.o $(GEOM_LIB)/Cone.o $(GEOM_LIB)/Sphere.o $(GEOM_LIB)/Transformations.o $(GEOM_LIB)/Plotter.o $(GEOM_LIB)/Cylinder.o $(GEOM_LIB)/FileHandler.o

LIBGEOM = $(GEOM_LIB)/libgeometry.dll
EXEC = $(APP_SRC)/main.exe

all: $(GEOM_LIB) $(LIBGEOM) $(EXEC)

$(GEOM_LIB):
	mkdir $(GEOM_LIB) 2> NUL || exit 0

$(GEOM_LIB)/Line.o: $(GEOM_SRC)/Shapes/Line.cpp $(GEOM_INC)/Shapes/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Rectangle.o: $(GEOM_SRC)/Shapes/Rectangle.cpp $(GEOM_INC)/Shapes/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Cuboid.o: $(GEOM_SRC)/Shapes/Cuboid.cpp $(GEOM_INC)/Shapes/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Sphere.o: $(GEOM_SRC)/Shapes/Sphere.cpp $(GEOM_INC)/Shapes/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Circle.o: $(GEOM_SRC)/Shapes/Circle.cpp $(GEOM_INC)/Shapes/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Cone.o: $(GEOM_SRC)/Shapes/Cone.cpp $(GEOM_INC)/Shapes/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Cylinder.o: $(GEOM_SRC)/Shapes/Cylinder.cpp $(GEOM_INC)/Shapes/Geometry.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Transformations.o: $(GEOM_SRC)/Shapes/Transformations.cpp $(GEOM_INC)/Shapes/Transformations.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/Plotter.o: $(GEOM_SRC)/Shapes/Plotter.cpp $(GEOM_INC)/Shapes/Plotter.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GEOM_LIB)/FileHandler.o: $(GEOM_SRC)/Conversions/FileHandler.cpp $(GEOM_INC)/Conversions/FileHandler.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIBGEOM): $(OBJS)
	$(CXX) -shared -o $@ $^

$(EXEC): $(APP_SRC)/main.cpp $(LIBGEOM)
	$(CXX) -o $@ $(APP_SRC)/main.cpp -I$(GEOM_INC) -L$(GEOM_LIB) -lgeometry

run:
	cd application && main.exe

clean:
	del /Q $(subst /,\,$(OBJS)) 2> NUL
	del /Q $(subst /,\,$(LIBGEOM)) 2> NUL
	del /Q $(subst /,\,$(EXEC)) 2> NUL
	del /Q $(subst /,\,$(GEOM_SCRIPTS))\*.dat 2> NUL
	del /Q $(subst /,\,$(GEOM_SCRIPTS))\*.stl 2> NUL
	del /Q $(subst /,\,$(GEOM_SCRIPTS))\*.obj 2> NUL










{
