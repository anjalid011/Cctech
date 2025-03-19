#include <iostream>
#include <fstream>

using namespace std;

void generateLine(double x1, double y1, double x2, double y2) {
    ofstream dataFile("line_plot.dat"); 

    if (!dataFile) {
        cerr << "Error creating file!" << endl;
        return;
    }

    int totalPoints = 10; 

    for (int i = 0; i < totalPoints; i++) {
        double t = (double)i / (totalPoints - 1);
        double x = x1 + t * (x2 - x1);
        double y = y1 + t * (y2 - y1);
        dataFile << x << " " << y << endl; // Save to file
    }
    
    dataFile.close();
}

void plotGraph() {    
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

    system("gnuplot -p plot_script.gnu");
}

int main() {
    double x1, y1, x2, y2;
    
    cout << "Enter x1, y1: ";
    cin >> x1 >> y1;
    cout << "Enter x2, y2: ";
    cin >> x2 >> y2;

    generateLine(x1, y1, x2, y2);
    plotGraph();

    return 0;
}
