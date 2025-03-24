The file contains A C++ Frame work for plotting 2D and #D geometric shapes (lines,Rectangles and Cuboids) Using Gnuplot.
After Installation(Clone the Repository and install all the dependencies like gcc comands and Gnuplot) and setup is done.
framework/
│── geometry/
│   │── include/      
│   │   ├── Line.h
│   │   ├── Rectangle.h
│   │   ├── Cuboid.h
│   │── src/           
│   │   ├── Line.cpp
│   │   ├── Rectangle.cpp
│   │   ├── Cuboid.cpp
│   │── lib/            # Compiled shared libraries
│   │── scripts/        # Txt Files for storing the data points
│── application/
│   │── main.cpp        # Main executable
│── Makefile            

To complile the code : make
To run the Program: make run
