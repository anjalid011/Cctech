#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class VoronoiWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    VoronoiWidget *voronoiWidget;
};

#endif // MAINWINDOW_H
