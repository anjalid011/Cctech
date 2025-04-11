#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openglwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Replace the QGraphicsView with OpenGLWidget
    openGLWidget = new OpenGLWidget(this);
    openGLWidget->setGeometry(10, 50, 780, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete openGLWidget;
}

void MainWindow::onDrawShapeClicked()
{
    // Example: Clear the OpenGL widget or perform some action
    if (openGLWidget) {
        // You can add logic here to draw shapes using OpenGL
        openGLWidget->update(); // Trigger a repaint of the OpenGL widget
    }
}