# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Output executable file
TARGET = test

# Source file
SRC = test.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default rule to compile the code and generate the executable
all: $(TARGET)

# Rule to create the executable from object files
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile the source file to an object file
$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC)

# Clean up the generated files
clean:
	rm -f $(OBJ) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# To generate the gnuplot plot (optional if you want to automate plotting)
plot: $(TARGET)
	./$(TARGET)

