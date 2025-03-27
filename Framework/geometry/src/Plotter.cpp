#include "Plotter.h"
#include <iostream>
#include <fstream>

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
void Plotter::plotMultipleShapes(const std::vector<std::string>& shapeFiles, const std::string& outputName) {
    std::ofstream script("geometry/scripts/" + outputName + ".plt");

    script << "set view equal xyz\n";
    script << "splot ";

    for (size_t i = 0; i < shapeFiles.size(); i++) {
        script << "'geometry/scripts/" << shapeFiles[i] << "' with lines";
        if (i < shapeFiles.size() - 1) script << ", ";
    }
    
    script << "\npause -1\n";
    script.close();

    std::string command = "gnuplot geometry/scripts/" + outputName + ".plt";
    system(command.c_str());
}
