#include "mainwindow.h"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\include\Shapes\Geometry.h"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\application\Voronoi.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    glWidget = new OpenGLWidget(this);
    glWidget->setMinimumSize(600, 400);

    shapeComboBox = new QComboBox(this);
    shapeComboBox->addItems({"Cuboid", "Sphere", "Cone", "Cylinder", "Bezier", "Voronoi Diagram"});
    connect(shapeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onShapeChanged);

    drawButton = new QPushButton("Draw Shape", this);
    connect(drawButton, &QPushButton::clicked, this, &MainWindow::onDrawButtonClicked);

    shapeList = new QListWidget(this);

    formStack = new QStackedWidget(this);
    formStack->addWidget(createCuboidForm());
    formStack->addWidget(createSphereForm());
    formStack->addWidget(createConeForm());
    formStack->addWidget(createCylinderForm());
    formStack->addWidget(createBezierForm());
    formStack->addWidget(createVoronoiForm());


    // Add sliders for transformations
    translateXSlider = new QSlider(Qt::Horizontal, this);
    translateYSlider = new QSlider(Qt::Horizontal, this);
    translateZSlider = new QSlider(Qt::Horizontal, this);
 
    rotateXSlider = new QSlider(Qt::Horizontal, this);
    rotateYSlider = new QSlider(Qt::Horizontal, this);
    rotateZSlider = new QSlider(Qt::Horizontal, this);
 
    scaleXSlider = new QSlider(Qt::Horizontal, this);
    scaleYSlider = new QSlider(Qt::Horizontal, this);
    scaleZSlider = new QSlider(Qt::Horizontal, this);
 
    // Set slider ranges
    translateXSlider->setRange(-100, 100);
    translateYSlider->setRange(-100, 100);
    translateZSlider->setRange(-100, 100);
 
    rotateXSlider->setRange(0, 360);
    rotateYSlider->setRange(0, 360);
    rotateZSlider->setRange(0, 360);
 
    scaleXSlider->setRange(1, 200);
    scaleYSlider->setRange(1, 200);
    scaleZSlider->setRange(1, 200);
 
    // Connect sliders to slots
    connect(translateXSlider, &QSlider::valueChanged, this, &MainWindow::onTranslateXChanged);
    connect(translateYSlider, &QSlider::valueChanged, this, &MainWindow::onTranslateYChanged);
    connect(translateZSlider, &QSlider::valueChanged, this, &MainWindow::onTranslateZChanged);
 
    connect(rotateXSlider, &QSlider::valueChanged, this, &MainWindow::onRotateXChanged);
    connect(rotateYSlider, &QSlider::valueChanged, this, &MainWindow::onRotateYChanged);
    connect(rotateZSlider, &QSlider::valueChanged, this, &MainWindow::onRotateZChanged);
 
    connect(scaleXSlider, &QSlider::valueChanged, this, &MainWindow::onScaleXChanged);
    connect(scaleYSlider, &QSlider::valueChanged, this, &MainWindow::onScaleYChanged);
    connect(scaleZSlider, &QSlider::valueChanged, this, &MainWindow::onScaleZChanged);

    QVBoxLayout *leftPanelLayout = new QVBoxLayout;
    leftPanelLayout->addWidget(new QLabel("Choose A Shape To Draw"));
    leftPanelLayout->addWidget(shapeComboBox);
    leftPanelLayout->addWidget(formStack);
    leftPanelLayout->addWidget(drawButton);
    leftPanelLayout->addWidget(new QLabel("List Of Shapes On the screen"));
    leftPanelLayout->addWidget(shapeList);

    // Add sliders to the layout
    leftPanelLayout->addWidget(new QLabel("Translate X:"));
    leftPanelLayout->addWidget(translateXSlider);
    leftPanelLayout->addWidget(new QLabel("Translate Y:"));
    leftPanelLayout->addWidget(translateYSlider);
    leftPanelLayout->addWidget(new QLabel("Translate Z:"));
    leftPanelLayout->addWidget(translateZSlider);

    leftPanelLayout->addWidget(new QLabel("Rotate X:"));
    leftPanelLayout->addWidget(rotateXSlider);
    leftPanelLayout->addWidget(new QLabel("Rotate Y:"));
    leftPanelLayout->addWidget(rotateYSlider);
    leftPanelLayout->addWidget(new QLabel("Rotate Z:"));
    leftPanelLayout->addWidget(rotateZSlider);

    leftPanelLayout->addWidget(new QLabel("Scale X:"));
    leftPanelLayout->addWidget(scaleXSlider);
    leftPanelLayout->addWidget(new QLabel("Scale Y:"));
    leftPanelLayout->addWidget(scaleYSlider);
    leftPanelLayout->addWidget(new QLabel("Scale Z:"));
    leftPanelLayout->addWidget(scaleZSlider);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftPanelLayout, 2);
    mainLayout->addWidget(glWidget, 8);

    centralWidget->setLayout(mainLayout);
}

void MainWindow::onShapeChanged(int index) {
    formStack->setCurrentIndex(index);
}

void MainWindow::onDrawButtonClicked() {
    QString selectedShape = shapeComboBox->currentText();

    if (selectedShape == "Bezier") {
        // Ensure the Bezier settings are valid
        int totalPoints = bezierControlPoints->text().toInt();
        int interpolationPoints = bezierInterpolationPoints->text().toInt();

        if (totalPoints > 0 && interpolationPoints > 0) {
            glWidget->setTotalControlPoints(totalPoints);
            glWidget->setInterpolationPoints(interpolationPoints);
            glWidget->clearControlPoints();
            qDebug() << "Bezier settings applied: Total Control Points:" << totalPoints
                     << "Interpolation Points:" << interpolationPoints;
        } else {
            qDebug() << "Invalid Bezier settings.";
        }
    } 
    else if(selectedShape == "Cuboid") {
        double x = cuboidX->text().toDouble();
        double y = cuboidY->text().toDouble();
        double z = cuboidZ->text().toDouble();
        double width = cuboidWidth->text().toDouble();
        double height = cuboidHeight->text().toDouble();
        double depth = cuboidDepth->text().toDouble();

        Cuboid cuboid(x, y, z, width, height, depth);
        cuboid.draw();
        glWidget->loadAndDrawShape("../geometry/scripts/cuboid.obj");

        shapeList->addItem("Cuboid: " + QString::number(x) + ", " + QString::number(y) + ", " + QString::number(z) +
                           ", " + QString::number(width) + ", " + QString::number(height) + ", " + QString::number(depth));
    } 
    else if(selectedShape == "Sphere") {
        double radius = sphereRadius->text().toDouble();
        double x = sphereX->text().toDouble();
        double y = sphereY->text().toDouble();
        double z = sphereZ->text().toDouble();

        Sphere sphere(radius, x, y, z);
        sphere.draw();
        glWidget->loadAndDrawShape("../geometry/scripts/sphere.obj");
        shapeList->addItem("Sphere: " + QString::number(radius) + ", " + QString::number(x) +
                           ", " + QString::number(y) + ", " + QString::number(z));
    } 
    else if(selectedShape == "Cone") {
        double radius = coneRadius->text().toDouble();
        double height = coneHeight->text().toDouble();
        double x = coneX->text().toDouble();
        double y = coneY->text().toDouble();
        double z = coneZ->text().toDouble();

        Cone cone(radius, height, x, y, z);
        cone.draw();
        glWidget->loadAndDrawShape("../geometry/scripts/cone.obj");
        shapeList->addItem("Cone: " + QString::number(radius) + ", " + QString::number(height) +
                           ", " + QString::number(x) + ", " + QString::number(y) + ", " + QString::number(z));
    } 
    else if(selectedShape == "Cylinder") {
        double radius = cylinderRadius->text().toDouble();
        double height = cylinderHeight->text().toDouble();
        double x = cylinderX->text().toDouble();
        double y = cylinderY->text().toDouble();
        double z = cylinderZ->text().toDouble();

        Cylinder cylinder(radius, height, x, y, z);
        cylinder.draw();
        glWidget->loadAndDrawShape("../geometry/scripts/cylinder.obj");
        shapeList->addItem("Cylinder: " + QString::number(radius) + ", " + QString::number(height) +
                           ", " + QString::number(x) + ", " + QString::number(y) + ", " + QString::number(z));
    }
    else {
        qDebug() << "Drawing shape:" << selectedShape;
        // Add logic for other shapes if needed
    }
}

QWidget* MainWindow::createCuboidForm() {
    QWidget *form = new QWidget;
    QFormLayout *layout = new QFormLayout(form);
    cuboidX = new QLineEdit; cuboidY = new QLineEdit; cuboidZ = new QLineEdit;
    cuboidWidth = new QLineEdit; cuboidHeight = new QLineEdit; cuboidDepth = new QLineEdit;
    layout->addRow("X:", cuboidX); layout->addRow("Y:", cuboidY); layout->addRow("Z:", cuboidZ);
    layout->addRow("Width:", cuboidWidth); layout->addRow("Height:", cuboidHeight); layout->addRow("Depth:", cuboidDepth);
    return form;
}

QWidget* MainWindow::createSphereForm() {
    QWidget *form = new QWidget;
    QFormLayout *layout = new QFormLayout(form);
    sphereRadius = new QLineEdit; sphereX = new QLineEdit; sphereY = new QLineEdit; sphereZ = new QLineEdit;
    layout->addRow("Radius:", sphereRadius);
    layout->addRow("Center X:", sphereX); layout->addRow("Center Y:", sphereY); layout->addRow("Center Z:", sphereZ);
    return form;
}

QWidget* MainWindow::createConeForm() {
    QWidget *form = new QWidget;
    QFormLayout *layout = new QFormLayout(form);
    coneRadius = new QLineEdit; coneHeight = new QLineEdit;
    coneX = new QLineEdit; coneY = new QLineEdit; coneZ = new QLineEdit;
    layout->addRow("Radius:", coneRadius); layout->addRow("Height:", coneHeight);
    layout->addRow("Base X:", coneX); layout->addRow("Base Y:", coneY); layout->addRow("Base Z:", coneZ);
    return form;
}

QWidget* MainWindow::createCylinderForm() {
    QWidget *form = new QWidget;
    QFormLayout *layout = new QFormLayout(form);
    cylinderRadius = new QLineEdit; cylinderHeight = new QLineEdit;
    cylinderX = new QLineEdit; cylinderY = new QLineEdit; cylinderZ = new QLineEdit;
    layout->addRow("Radius:", cylinderRadius); layout->addRow("Height:", cylinderHeight);
    layout->addRow("Base X:", cylinderX); layout->addRow("Base Y:", cylinderY); layout->addRow("Base Z:", cylinderZ);
    return form;
}

QWidget* MainWindow::createBezierForm() {
    QWidget *form = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(form);

    // Input for number of control points
    bezierControlPoints = new QLineEdit;
    bezierInterpolationPoints = new QLineEdit;

    layout->addWidget(new QLabel("Number of Control Points:"));
    layout->addWidget(bezierControlPoints);

    layout->addWidget(new QLabel("Number of Interpolation Points:"));
    layout->addWidget(bezierInterpolationPoints);

    QPushButton *setButton = new QPushButton("Set Points");
    layout->addWidget(setButton);

    connect(setButton, &QPushButton::clicked, [=]() {
        int totalPoints = bezierControlPoints->text().toInt();
        int interpolationPoints = bezierInterpolationPoints->text().toInt();

        if (totalPoints > 0 && interpolationPoints > 0) {
            glWidget->setTotalControlPoints(totalPoints);
            glWidget->setInterpolationPoints(interpolationPoints);
            glWidget->clearControlPoints();
            qDebug() << "Bezier settings updated: Total Control Points:" << totalPoints
                     << "Interpolation Points:" << interpolationPoints;
        } else {
            qDebug() << "Invalid input for Bezier settings.";
        }
    });

    return form;
}

QWidget* MainWindow::createVoronoiForm() {
    QWidget *form = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(form);

    QPushButton *addSeedsButton = new QPushButton("Add Seeds", form);
    layout->addWidget(addSeedsButton);

    connect(addSeedsButton, &QPushButton::clicked, this, &MainWindow::openVoronoiWindow);

    form->setLayout(layout);
    return form;
}

void MainWindow::openVoronoiWindow() {
    Voronoi dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        QVector<QPointF> seeds = dlg.getSeeds();
        // Pass seeds to your Voronoi diagram logic and render
    }
}

// Slots for transformations
void MainWindow::onTranslateXChanged(int value) {
    glWidget->translateShape(value, 0, 0);
}

void MainWindow::onTranslateYChanged(int value) {
    glWidget->translateShape(0, value, 0);
}

void MainWindow::onTranslateZChanged(int value) {
    glWidget->translateShape(0, 0, value);
}

void MainWindow::onRotateXChanged(int value) {
    glWidget->rotateShape(value, 0, 0);
}

void MainWindow::onRotateYChanged(int value) {
    glWidget->rotateShape(0, value, 0);
}

void MainWindow::onRotateZChanged(int value) {
    glWidget->rotateShape(0, 0, value);
}

void MainWindow::onScaleXChanged(int value) {
    glWidget->scaleShape(value / 100.0f, 1.0f, 1.0f);
}

void MainWindow::onScaleYChanged(int value) {
    glWidget->scaleShape(1.0f, value / 100.0f, 1.0f);
}

void MainWindow::onScaleZChanged(int value) {
    glWidget->scaleShape(1.0f, 1.0f, value / 100.0f);
}

