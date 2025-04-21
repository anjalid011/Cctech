#include "mainwindow.h"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\include\Shapes\Geometry.h"
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
    shapeComboBox->addItems({"Cuboid", "Sphere", "Cone", "Cylinder", "Bezier"});
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

    QVBoxLayout *leftPanelLayout = new QVBoxLayout;
    leftPanelLayout->addWidget(new QLabel("Choose A Shape To Draw"));
    leftPanelLayout->addWidget(shapeComboBox);
    leftPanelLayout->addWidget(formStack);
    leftPanelLayout->addWidget(drawButton);
    leftPanelLayout->addWidget(new QLabel("List Of Shapes On the screen"));
    leftPanelLayout->addWidget(shapeList);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftPanelLayout);
    mainLayout->addWidget(glWidget);

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
    } else {
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