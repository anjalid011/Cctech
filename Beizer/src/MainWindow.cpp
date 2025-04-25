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

    inputLayout->addWidget(new QLabel("Control Points:"));
    inputLayout->addWidget(controlPointsEdit);
    inputLayout->addWidget(new QLabel("Interpolation Points:"));
    inputLayout->addWidget(interpPointsEdit);
    inputLayout->addWidget(drawButton);

    glWidget = new GLWidget();

    layout->addLayout(inputLayout);
    layout->addWidget(glWidget);
    central->setLayout(layout);
    setCentralWidget(central);

    connect(drawButton, &QPushButton::clicked, this, &MainWindow::onDrawClicked);
}

void MainWindow::onDrawClicked() {
    int numControl = controlPointsEdit->text().toInt();
    int numInterp = interpPointsEdit->text().toInt();
    if (numControl >= 2 && numInterp >= 1) {
        glWidget->startDrawing(numControl, numInterp);
    }
}