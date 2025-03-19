#include <iostream>
#include <fstream>

using namespace std;

class Line3D {
private:
    double x1, y1, z1, x2, y2, z2;
    int totalPoints;

public:
    Line3D(double x1, double y1, double z1, double x2, double y2, double z2, int totalPoints = 10) {
        this->x1 = x1;
        this->y1 = y1;
        this->z1 = z1;
        this->x2 = x2;
        this->y2 = y2;
        this->z2 = z2;
        this->totalPoints = totalPoints;
    }
    
    void generatePoints() {
        ofstream dataFile("line_plot.dat");

        if (!dataFile) {
            cerr << "Error creating file!" << endl;
            return;
        }

        // Generate points including start and end
        for (int i = 0; i < totalPoints; i++) {
            double t = (double)i / (totalPoints - 1);
            double x = x1 + t * (x2 - x1);
            double y = y1 + t * (y2 - y1);
            double z = z1 + t * (z2 - z1);
            dataFile << x << " " << y << " " << z << endl; // Save (x, y, z)
        }
        
        dataFile.close();
        cout << "Data saved to 'line_plot.dat'.\n";
    }

    void generateGnuplotScript() {
        ofstream scriptFile("plot_script.gnu");

        if (!scriptFile) {
            cerr << "Error creating script file!" << endl;
            return;
        }

        scriptFile << "set title '3D Line using Parametric Equation'\n";
        scriptFile << "set xlabel 'X-axis'\n";
        scriptFile << "set ylabel 'Y-axis'\n";
        scriptFile << "set zlabel 'Z-axis'\n";
        scriptFile << "set grid\n";
        scriptFile << "splot 'line_plot.dat' with linespoints title '3D Line' lc rgb 'blue' pt 7\n";

        scriptFile.close();
    }

    void plotGraph() {
        cout << "Run the following command\n";
        cout << "gnuplot -p plot_script.gnu\n";
    }
};

int main() {
    double x1, y1, z1, x2, y2, z2;

    cout << "Enter x1, y1, z1: ";
    cin >> x1 >> y1 >> z1;
    cout << "Enter x2, y2, z2: ";
    cin >> x2 >> y2 >> z2;

    Line3D line(x1, y1, z1, x2, y2, z2);

    line.generatePoints();
    line.generateGnuplotScript();
    line.plotGraph();

    return 0;
}
