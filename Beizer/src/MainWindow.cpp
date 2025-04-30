#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();

    QHBoxLayout *inputLayout = new QHBoxLayout();
    controlPointsEdit = new QLineEdit();
    interpPointsEdit = new QLineEdit();
    drawButton = new QPushButton("Draw");
    show3DButton = new QPushButton("Show 3D");

    inputLayout->addWidget(new QLabel("Control Points:"));
    inputLayout->addWidget(controlPointsEdit);
    inputLayout->addWidget(new QLabel("Interpolation Points:"));
    inputLayout->addWidget(interpPointsEdit);
    inputLayout->addWidget(drawButton);
    inputLayout->addWidget(show3DButton);

    glWidget = new GLWidget();

    layout->addLayout(inputLayout);
    layout->addWidget(glWidget);
    central->setLayout(layout);
    setCentralWidget(central);

    connect(drawButton, &QPushButton::clicked, this, &MainWindow::onDrawClicked);
    connect(show3DButton, &QPushButton::clicked, this, &MainWindow::onShow3DClicked);
}

void MainWindow::onDrawClicked() {
    int numControl = controlPointsEdit->text().toInt();
    int numInterp = interpPointsEdit->text().toInt();
    if (numControl >= 2 && numInterp >= 1) {
        glWidget->startDrawing(numControl, numInterp);
    }
}

void MainWindow::onShow3DClicked() {
    glWidget->show3D(true);
}