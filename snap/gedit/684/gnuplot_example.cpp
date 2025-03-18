#include <iostream>
#include <fstream>
#include <cmath>

int main() {
    // Open a gnuplot script file
    std::ofstream gnuplotScript("plot_script.gp");

    // Check if the file opened successfully
    if (!gnuplotScript) {
        std::cerr << "Error opening file to write gnuplot script." << std::endl;
        return 1;
    }

    // Set the plot ranges
    gnuplotScript << "set xrange [-10:10]\n";
    gnuplotScript << "set yrange [-30:50]\n";
    gnuplotScript << "set pointsize 1.5\n"; // Set the point size

    // Plot the line equation y = 4x + 5 and the points
    gnuplotScript << "plot '-' using 1:2 with lines title 'y = 4x + 5', \\\n";
    gnuplotScript << "     '-' using 1:2 with points pt 7 ps 1.5 title 'Points'\n";

    // Write the data for the line
    for (double x = -10; x <= 10; x += 2) {
        double y = 4 * x + 5;
        gnuplotScript << x << " " << y << "\n";
    }

    gnuplotScript << "e\n";  // End of line data

    // Write the data for the points (8 points)
    for (double x = -8; x <= 6; x += 2) {
        double y = 4 * x + 5;
        gnuplotScript << x << " " << y << "\n";
    }

    gnuplotScript << "e\n";  // End of points data

    // Close the file
    gnuplotScript.close();

    // Run the gnuplot command with the script file
    system("gnuplot -p plot_script.gp");

    return 0;
}

