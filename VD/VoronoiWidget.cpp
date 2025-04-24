#include "VoronoiWidget.h"
#include <QPainter>

VoronoiWidget::VoronoiWidget(QWidget* parent)
    : QOpenGLWidget(parent) {}

void VoronoiWidget::setSites(const std::vector<QVector2D>& newSites) {
    sites = newSites;
    computeVoronoi();
    update();  // trigger paintGL
}

void VoronoiWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void VoronoiWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1); // 2D view: top-left (0,0)
    glMatrixMode(GL_MODELVIEW);
}

void VoronoiWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw sites (points)
    glPointSize(5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for (const auto& pt : sites) {
        glVertex2f(pt.x(), pt.y());
    }
    glEnd();

    // Draw Voronoi edges
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    for (const auto& edge : edges) {
        glVertex2f(edge.first.x(), edge.first.y());
        glVertex2f(edge.second.x(), edge.second.y());
    }
    glEnd();
}

void VoronoiWidget::computeVoronoi() {
    edges.clear();
    computeVoronoiEdges(sites, edges); // Call helper in Voronoi.cpp
}
