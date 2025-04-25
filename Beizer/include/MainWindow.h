#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include "GLWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onDrawClicked();

private:
    QLineEdit *controlPointsEdit;
    QLineEdit *interpPointsEdit;
    QPushButton *drawButton;
    GLWidget *glWidget;
};

#endif // MAINWINDOW_H