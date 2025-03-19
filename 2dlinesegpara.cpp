#include <iostream>
#include <fstream>

using namespace std;

// Function to generate parametric points and save to a file
void generateLine(double x1, double y1, double x2, double y2) {
    ofstream dataFile("line_plot.dat"); // File to store points

    if (!dataFile) {
        cerr << "Error creating file!" << endl;
        return;
    }

    int totalPoints = 10; // Including start and end points

    // Generate exactly 8 points in between (10 total)
    for (int i = 0; i < totalPoints; i++) {
        double t = (double)i / (totalPoints - 1);
        double x = x1 + t * (x2 - x1);
        double y = y1 + t * (y2 - y1);
        dataFile << x << " " << y << endl; // Save to file
    }
    
    dataFile.close();
    
    // Generate GNUPlot script
    ofstream scriptFile("plot_script.gnu");
    if (!scriptFile) {
        cerr << "Error creating script file!" << endl;
        return;
    }

    scriptFile << "set title 'Line using Parametric Equation (10 Points)'\n";
    scriptFile << "set xlabel 'X-axis'\n";
    scriptFile << "set ylabel 'Y-axis'\n";
    scriptFile << "set grid\n";
    scriptFile << "plot 'line_plot.dat' with linespoints title 'Line and Points' lc rgb 'blue' pt 7\n";
    
    scriptFile.close();

    cout << "Data saved to 'line_plot.dat'.\n";
    cout << "Run the following command in WSL to plot the graph:\n";
    cout << "gnuplot -p plot_script.gnu\n";
}

int main() {
    double x1, y1, x2, y2;
    
    // Take user input
    cout << "Enter x1, y1: ";
    cin >> x1 >> y1;
    cout << "Enter x2, y2: ";
    cin >> x2 >> y2;

    generateLine(x1, y1, x2, y2);

    return 0;
}
