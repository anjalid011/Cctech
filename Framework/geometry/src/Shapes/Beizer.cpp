#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\include\Shapes\Geometry.h"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\include\Shapes\Transformations.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <QOpenGLFunctions>

void Bezier3D::generateCurvePoints(int resolution) {
    curvePoints.clear();
    for (int i = 0; i <= resolution; ++i) {
        double t = static_cast<double>(i) / resolution;
        curvePoints.push_back(deCasteljau(t));
    }
}

Point3D Bezier3D::deCasteljau(double t) const {
    std::vector<Point3D> temp = controlPoints;
    int n = temp.size();

    for (int r = 1; r < n; ++r) {
        for (int i = 0; i < n - r; ++i) {
            temp[i].x = (1 - t) * temp[i].x + t * temp[i + 1].x;
            temp[i].y = (1 - t) * temp[i].y + t * temp[i + 1].y;
            temp[i].z = (1 - t) * temp[i].z + t * temp[i + 1].z;
        }
    }

    return temp[0];
}

void Bezier3D::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& pt : curvePoints) {
        file << pt.x << " " << pt.y << " " << pt.z << "\n";
    }
    file.close();
}


void Bezier3D::draw() {
    // Draw control points
    glPointSize(10.0f); // Increase point size
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red for control points
    for (const auto& pt : controlPoints) {
        glVertex3f(pt.x, pt.y, pt.z);
    }
    glEnd();

    // Draw the Bezier curve
    glLineWidth(3.0f); // Increase line width
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 1.0f, 0.0f); // Green for the curve
    for (const auto& pt : curvePoints) {
        glVertex3f(pt.x, pt.y, pt.z);
    }
    glEnd();
}
