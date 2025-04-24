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
    void openVoronoiWindow();

    // Slots for transformations
    void onTranslateXChanged(int value);
    void onTranslateYChanged(int value);
    void onTranslateZChanged(int value);

    void onRotateXChanged(int value);
    void onRotateYChanged(int value);
    void onRotateZChanged(int value);

    void onScaleXChanged(int value);
    void onScaleYChanged(int value);
    void onScaleZChanged(int value);

private:
    void setupUI();
    QWidget* createCuboidForm();
    QWidget* createSphereForm();
    QWidget* createConeForm();
    QWidget* createCylinderForm();
    QWidget* createBezierForm();
    QWidget* createVoronoiForm();

    void generateControlPointInputs(); // Method to generate control point input fields

    OpenGLWidget *glWidget;
    QPushButton *drawButton;
    QComboBox *shapeComboBox;
    QListWidget *shapeList;
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

    //Beizer Inputs
    QVBoxLayout *controlPointInputs; // Layout for control point input fields
    std::vector<std::array<QLineEdit *, 3>> controlPointEdits; // Stores input fields for control points
    QLineEdit *bezierControlPoints; // Number of control points
    QLineEdit *bezierInterpolationPoints; // Number of interpolation points

    // Sliders for transformations
    QSlider *translateXSlider, *translateYSlider, *translateZSlider;
    QSlider *rotateXSlider, *rotateYSlider, *rotateZSlider;
    QSlider *scaleXSlider, *scaleYSlider, *scaleZSlider;
};

#endif // MAINWINDOW_H