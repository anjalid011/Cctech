# Compiler
CXX = g++
CXXFLAGS = -Wall -fPIC -Igeometry/include

# Directories
GEOM_SRC = geometry/src
GEOM_INC = geometry/include
GEOM_LIB = geometry/lib
GEOM_SCRIPTS = geometry/scripts
APP_SRC = application

# Object Files
OBJS = $(GEOM_LIB)/Line.o $(GEOM_LIB)/Rectangle.o $(GEOM_LIB)/Cuboid.o

# Shared Library
LIBGEOM = $(GEOM_LIB)/libgeometry.so

# Executable
EXEC = $(APP_SRC)/main

# Default target: build everything
all: $(LIBGEOM) $(EXEC)

# Compile the shared library
$(LIBGEOM): $(OBJS)
	$(CXX) -shared -o $@ $^

# Compile object files
$(GEOM_LIB)/%.o: $(GEOM_SRC)/%.cpp $(GEOM_INC)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main executable
$(EXEC): $(APP_SRC)/main.cpp $(LIBGEOM)
	$(CXX) -o $@ $(APP_SRC)/main.cpp -I$(GEOM_INC) -L$(GEOM_LIB) -lgeometry

# Run the program with the correct library path
run: $(EXEC)
	# export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(pwd)/geometry/lib && ./$(EXEC)
	export LD_LIBRARY_PATH=$(pwd)/geometry/lib && ./application/main
# Clean up compiled files
clean:
	rm -f $(OBJS) $(LIBGEOM) $(EXEC) geometry/scripts/*.txt