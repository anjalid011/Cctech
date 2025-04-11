#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "openglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDrawShapeClicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    OpenGLWidget *openGLWidget; // Declare the OpenGLWidget here
};

#endif // MAINWINDOW_H