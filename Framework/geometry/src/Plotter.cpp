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

void Plotter::plot2D(const std::string& filename, const std::string& title) {
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

    pclose(gnuplot);
}

void Plotter::plot2DTrans(const std::string& filename, const std::string& transformedFile, const std::string& title) {
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

void Plotter::plot3D(const std::string& filename, const std::string& title) {
    FILE *gnuplot = popen("/usr/bin/gnuplot -persistent", "w");
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

    pclose(gnuplot);
}

void Plotter::plot3DTrans(const std::string& filename, const std::string& transformedFile, const std::string& title) {
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
