#include "mainwindow.h"
#include "Extrusion.h"
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    GLWidget* glWidget = new GLWidget(this);
    layout->addWidget(glWidget);

    QPushButton *extrudeButton = new QPushButton("Extrude", this);
    layout->addWidget(extrudeButton);

    connect(extrudeButton, &QPushButton::clicked, glWidget, &GLWidget::performExtrusion);

    central->setLayout(layout);
    setCentralWidget(central);
}

