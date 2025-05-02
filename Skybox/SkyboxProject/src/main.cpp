#include <QApplication>
#include "glwidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    GLWidget window;
    window.resize(800, 600);
    window.setWindowTitle("Skybox with Rotating Spheres");
    window.show();
    
    return app.exec();
}