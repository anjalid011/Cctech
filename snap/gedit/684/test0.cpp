#include <bits/stdc++.h>
#include "gnuplot-iostream.h"
using namespace std;

vector<pair<double,double>> generatePoints(double x1, double y1, double x2, double y2){
    vector<pair<double, double>> points;
    
    double dx = (x2 - x1) / 9.0;  
    double dy = (y2 - y1) / 9.0;

    for (int i = 0; i < 10; i++) {
        double x = x1 + i * dx;
        double y = y1 + i * dy;
        points.push_back({x, y});
    }

    return points;
}

int main(){
    // setup gnuplot interface
    Gnuplot gp;
    
    // input start and end coordinates
    double x1, x2, y1, y2;
    cout << "Enter start coords: ";
    cin >> x1 >> y1;
    cout << "Enter end coords: ";
    cin >> x2 >> y2;

    // generate points for the line and plot
    vector<pair<double,double>> points = generatePoints(x1, y1, x2, y2);

    // Plot the line and the points using Gnuplot
    gp << "plot '-' using 1:2 with lines title 'Line: y = mx + b', \\\n";
    gp << "     '-' using 1:2 with points pt 7 ps 1.5 title 'Points'\n";

    // Send the line data to Gnuplot (Line from the generated points)
    gp.send1d(points);

    return 0;
}

