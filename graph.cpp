#include <iostream>
#include <fstream>
#include <cmath>

int main() {
    double x1, y1, x2, y2;
    
    std::cout << "Enter the coordinates of the first endpoint (x1, y1): ";
    std::cin >> x1 >> y1;

    std::cout << "Enter the coordinates of the second endpoint (x2, y2): ";
    std::cin >> x2 >> y2;

    double m = (y2 - y1) / (x2 - x1);  
    double b = y1 - m * x1;          

    std::ofstream gnuplotScript("plot_script.gp");

    if (!gnuplotScript) {
        std::cerr << "Error opening file to write gnuplot script." << std::endl;
        return 1;
    }

    gnuplotScript << "set xrange [" << x1 - 2 << ":" << x2 + 2 << "]\n";  
    gnuplotScript << "set yrange [" << y1 - 2 << ":" << y2 + 2 << "]\n";  
    gnuplotScript << "set pointsize 1.5\n"; 

    gnuplotScript << "plot '-' using 1:2 with lines title 'Line: y = " << m << "x + " << b << "', \\\n";
    gnuplotScript << "     '-' using 1:2 with points pt 7 ps 1.5 title 'Points'\n";

    for (double x = x1 - 2; x <= x2 + 2; x += 0.5) {  
        double y = m * x + b;
        gnuplotScript << x << " " << y << "\n";
    }

    gnuplotScript << "e\n";  

    // We calculate 8 points between x1 and x2
    for (int i = 0; i < 8; ++i) {
        double x = x1 + (x2 - x1) * (i + 1) / 9.0;  // Evenly distribute points
        double y = m * x + b;  // Calculate the corresponding y value
        gnuplotScript << x << " " << y << "\n";
    }
    gnuplotScript << "e\n";  // End of points data

    gnuplotScript.close();

    system("gnuplot -p plot_script.gp");

    return 0;
}

