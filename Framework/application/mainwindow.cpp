#include "mainwindow.h"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\include\Shapes\Geometry.h"
#include <QVBoxLayout>
#include <QLabel>

// Constructor: Initializes the main window
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI(); // Set up the UI
}

// Destructor: Clean up resources if needed
MainWindow::~MainWindow() {}

// Function to set up the entire UI layout and widgets
void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create the OpenGL widget
    glWidget = new OpenGLWidget(this);
    glWidget->setMinimumSize(600, 400); // Larger OpenGL widget

    // Create the dropdown to select shapes
    shapeComboBox = new QComboBox(this);
    shapeComboBox->addItems({"Cuboid", "Sphere", "Cone", "Cylinder"}); // Add shapes to the dropdown

    // Create the "Draw" button
    drawButton = new QPushButton("Draw Shape", this);
    connect(drawButton, &QPushButton::clicked, this, &MainWindow::onDrawButtonClicked);

    // Create the list to display drawn shapes
    shapeList = new QListWidget(this);

    // Create the left panel layout
    QVBoxLayout *leftPanelLayout = new QVBoxLayout;
    leftPanelLayout->addWidget(new QLabel("Choose A Shape To Draw"));
    leftPanelLayout->addWidget(shapeComboBox);
    leftPanelLayout->addWidget(drawButton);
    leftPanelLayout->addWidget(new QLabel("List Of Shapes On the screen"));
    leftPanelLayout->addWidget(shapeList);

    // Create the main layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftPanelLayout);
    mainLayout->addWidget(glWidget);

    // Set the layout for the central widget
    centralWidget->setLayout(mainLayout);
}

// Slot to handle the "Draw" button click
void MainWindow::onDrawButtonClicked() {
    QString selectedShape = shapeComboBox->currentText(); // Get the selected shape
    QString objFilePath;

    if (selectedShape == "Cuboid") {
        Cuboid cuboid(0, 0, 0, 10, 10, 10); // Example dimensions
        cuboid.draw();
        objFilePath = "../geometry/scripts/cuboid.obj";
    } else if (selectedShape == "Sphere") {
        Sphere sphere(5); // Example radius
        sphere.draw();
        objFilePath = "../geometry/scripts/sphere.obj";
    } else if (selectedShape == "Cone") {
        Cone cone(5, 10); // Example radius and height
        cone.draw();
        objFilePath = "../geometry/scripts/cone.obj";
    } else if (selectedShape == "Cylinder") {
        Cylinder cylinder(5, 10); // Example radius and height
        cylinder.draw();
        objFilePath = "../geometry/scripts/cylinder.obj";
    }

    // Load the generated .obj file into the OpenGL widget
    glWidget->loadAndDrawShape(objFilePath);

    // Add the shape to the list
    shapeList->addItem(selectedShape);
}

