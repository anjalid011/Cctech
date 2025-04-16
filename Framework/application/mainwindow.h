#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include "openglwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    
    ~MainWindow();

private slots:
    void onDrawButtonClicked(); // Slot to handle the "Draw" button click

private:
    void setupUI(); // Sets up the UI layout and widgets

    OpenGLWidget *glWidget; // OpenGL widget for rendering
    QPushButton *drawButton; // Button to draw the cuboid
    QComboBox *shapeComboBox; // Dropdown to select shapes
    QListWidget *shapeList;   // List to display drawn shapes
    // QList<QString> drawnShapes; // List of drawn shapes
    // QList<QString> objFilePaths; // List of corresponding .obj file paths
};

#endif // MAINWINDOW_H
