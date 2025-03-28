#include "Plotter.h"
#include <cmath>
#include <iostream>
#include <fstream>
#define PI 3.14159265358979323846

void Plotter::savePoints(const std::string& filename, const std::vector<std::vector<double>>& points) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file " << filename << " for writing!\n";
        return;
    }
    for (const auto& point : points) {
        for (double coord : point) {
            file << coord << " ";
        }
        file << "\n";
    }
    file.close();
}

void Plotter::plot2D(const std::string& filename, const std::string& transformedFile, const std::string& title) {
    FILE *gnuplot = popen("gnuplot -persist", "w");
    if (!gnuplot) {
        std::cerr << "Error: Unable to open gnuplot!\n";
        return;
    }

    fprintf(gnuplot, "set terminal wxt\n");
    fprintf(gnuplot, "set mouse\n");
    fprintf(gnuplot, "set xlabel 'X-axis'\n");
    fprintf(gnuplot, "set ylabel 'Y-axis'\n");
    fprintf(gnuplot, "plot '%s' using 1:2 with lines lw 2 title 'Original', \\\n", filename.c_str());
    fprintf(gnuplot, "     '%s' using 1:2 with lines lw 2 lc rgb 'red' title 'Transformed'\n", transformedFile.c_str());

    pclose(gnuplot);
}

void Plotter::plot3D(const std::string& filename, const std::string& transformedFile, const std::string& title) {
    FILE *gnuplot = popen("gnuplot -persist", "w");
    if (!gnuplot) {
        std::cerr << "Error: Unable to open gnuplot!\n";
        return;
    }

    fprintf(gnuplot, "set terminal wxt\n");
    fprintf(gnuplot, "set mouse\n");
    fprintf(gnuplot, "set xlabel 'X-axis'\n");
    fprintf(gnuplot, "set ylabel 'Y-axis'\n");
    fprintf(gnuplot, "set zlabel 'Z-axis'\n");
    fprintf(gnuplot, "set view 60, 30\n");
    fprintf(gnuplot, "splot '%s' using 1:2:3 with lines lw 2 title 'Original', \\\n", filename.c_str());
    fprintf(gnuplot, "      '%s' using 1:2:3 with lines lw 2 lc rgb 'red' title 'Transformed'\n", transformedFile.c_str());

    pclose(gnuplot);
}

void Plotter::plotSphere(double x, double y, double z, double radius, const std::string& label) {
    std::ofstream file(".././geometry/scripts/sphere.dat");
    for (double theta = 0; theta < 360; theta += 10) {
        for (double phi = 0; phi < 180; phi += 10) {
            double xPos = x + radius * sin(phi * M_PI / 180.0) * cos(theta * M_PI / 180.0);
            double yPos = y + radius * sin(phi * M_PI / 180.0) * sin(theta * M_PI / 180.0);
            double zPos = z + radius * cos(phi * M_PI / 180.0);
            file << xPos << " " << yPos << " " << zPos << "\n";
        }
        file << "\n";
    }
    file.close();
    system("gnuplot -e \"splot '.././geometry/scripts/sphere.dat' with points\"");
}

void Plotter::plotCylinder(double x, double y, double z, double radius, double height, const std::string& label) {
    std::ofstream file(".././geometry/scripts/cylinder.dat");
    for (double theta = 0; theta < 360; theta += 10) {
        for (double h = 0; h <= height; h += 1) {
            double xPos = x + radius * cos(theta * M_PI / 180.0);
            double yPos = y + radius * sin(theta * M_PI / 180.0);
            double zPos = z + h;
            file << xPos << " " << yPos << " " << zPos << "\n";
        }
        file << "\n";
    }
    file.close();
    system("gnuplot -e \"splot '.././geometry/scripts/cylinder.dat' with points\"");
}

void Plotter::plotCone(double x, double y, double z, double radius, double height, const std::string& label) {
    std::ofstream file(".././geometry/scripts/cone.dat");
    for (double theta = 0; theta < 360; theta += 10) {
        for (double h = 0; h <= height; h += 1) {
            double r = radius * (1 - (h / height));
            double xPos = x + r * cos(theta * M_PI / 180.0);
            double yPos = y + r * sin(theta * M_PI / 180.0);
            double zPos = z + h;
            file << xPos << " " << yPos << " " << zPos << "\n";
        }
        file << "\n";
    }
    file.close();
    system("gnuplot -e \"splot '.././geometry/scripts/cone.dat' with points\"");
}

void Plotter::plotCuboid(double x, double y, double z, double width, double depth, double height, const std::string& label) {
    std::ofstream file(".././geometry/scripts/cuboid.dat");
    double x1 = x - width / 2, x2 = x + width / 2;
    double y1 = y - depth / 2, y2 = y + depth / 2;
    double z1 = z, z2 = z + height;
    
    double vertices[8][3] = {
        {x1, y1, z1}, {x2, y1, z1}, {x2, y2, z1}, {x1, y2, z1},
        {x1, y1, z2}, {x2, y1, z2}, {x2, y2, z2}, {x1, y2, z2}
    };
    
    int edges[12][2] = {
        {0,1}, {1,2}, {2,3}, {3,0}, {4,5}, {5,6}, {6,7}, {7,4}, {0,4}, {1,5}, {2,6}, {3,7}
    };
    
    for (int i = 0; i < 12; i++) {
        file << vertices[edges[i][0]][0] << " " << vertices[edges[i][0]][1] << " " << vertices[edges[i][0]][2] << "\n";
        file << vertices[edges[i][1]][0] << " " << vertices[edges[i][1]][1] << " " << vertices[edges[i][1]][2] << "\n\n";
    }
    file.close();
    system("gnuplot -e \"splot '.././geometry/scripts/cuboid.dat' with lines\"");
}