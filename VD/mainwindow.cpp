#include "mainwindow.h"
#include "VoronoiWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    voronoiWidget = new VoronoiWidget(this);
    setCentralWidget(voronoiWidget);
    setWindowTitle("Voronoi Diagram Viewer");
    resize(800, 600);
}

MainWindow::~MainWindow()
{
    // Qt handles deletion of child widgets, no need to delete voronoiWidget manually
}
