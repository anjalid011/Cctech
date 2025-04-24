#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include "VoronoiWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Voronoi Diagram - Qt + OpenGL");
    QVBoxLayout* layout = new QVBoxLayout(&window);

    VoronoiWidget* vWidget = new VoronoiWidget();
    layout->addWidget(vWidget);

    std::vector<QVector2D> points = {
        {100, 150}, {200, 100}, {300, 300}, {400, 200}, {250, 400}
    };
    vWidget->setSites(points);

    window.resize(600, 600);
    window.show();
    return app.exec();
}
