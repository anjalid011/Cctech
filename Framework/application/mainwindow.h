#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QStackedWidget>
#include <QLineEdit>
#include <QFormLayout>
#include "openglwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDrawButtonClicked();
    void onShapeChanged(int index);
    void deleteShape(); // New method for deleting shapes
    void openExtrusionWindow();
    void openBezierWindow();
    void openFile();
    void openSketchWindow();

private:
    void setupUI();
    QWidget* createCuboidForm();
    QWidget* createSphereForm();
    QWidget* createConeForm();
    QWidget* createCylinderForm();
    QWidget* createBezierForm();
    void generateControlPointInputs();

    OpenGLWidget *glWidget;
    QPushButton *drawButton;
    QPushButton *deleteShapeButton; // Button to delete selected shape
    QComboBox *shapeComboBox;
    QListWidget *shapeList; // List of shapes
    QStackedWidget *formStack;

    // Cuboid Inputs
    QLineEdit *cuboidX, *cuboidY, *cuboidZ;
    QLineEdit *cuboidWidth, *cuboidHeight, *cuboidDepth;

    // Sphere Inputs
    QLineEdit *sphereRadius;
    QLineEdit *sphereX, *sphereY, *sphereZ;

    // Cone Inputs
    QLineEdit *coneRadius, *coneHeight;
    QLineEdit *coneX, *coneY, *coneZ;

    // Cylinder Inputs
    QLineEdit *cylinderRadius, *cylinderHeight;
    QLineEdit *cylinderX, *cylinderY, *cylinderZ;

    // Bezier Inputs
    QVBoxLayout *controlPointInputs; // Layout for control point input fields
    std::vector<std::array<QLineEdit *, 3>> controlPointEdits; // Stores input fields for control points
    QLineEdit *bezierControlPoints;
    QLineEdit *bezierInterpolationPoints;
};

#endif // MAINWINDOW_H