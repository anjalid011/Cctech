#include "intersectionWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDockWidget>

IntersectionWindow::IntersectionWindow(QWidget* parent)
    : QMainWindow(parent) {
    m_intersectionWidget = new IntersectionWidget(this);
    setCentralWidget(m_intersectionWidget);

    QDockWidget* dockWidget = new QDockWidget("Control Panel", this);
    QWidget* controlPanel = new QWidget(dockWidget);
    QVBoxLayout* layout = new QVBoxLayout(controlPanel);
    dockWidget->setWidget(controlPanel);

    m_shapeSelector = new QComboBox(controlPanel);
    m_shapeSelector->addItems({"Line", "Rectangle", "Cuboid", "Circle", "Sphere", "Cone", "Cylinder", "Bezier3D"});
    layout->addWidget(m_shapeSelector);

    // Input fields for shape parameters
    QFormLayout* formLayout = new QFormLayout();
    m_param1 = new QLineEdit(controlPanel);
    m_param2 = new QLineEdit(controlPanel);
    m_param3 = new QLineEdit(controlPanel);
    m_param4 = new QLineEdit(controlPanel);
    formLayout->addRow("Param 1:", m_param1);
    formLayout->addRow("Param 2:", m_param2);
    formLayout->addRow("Param 3:", m_param3);
    formLayout->addRow("Param 4:", m_param4);
    layout->addLayout(formLayout);

    m_shapeList = new QListWidget(controlPanel);
    layout->addWidget(m_shapeList);

    m_addShapeButton = new QPushButton("Add Shape", controlPanel);
    layout->addWidget(m_addShapeButton);
    connect(m_addShapeButton, &QPushButton::clicked, this, &IntersectionWindow::addShape);

    m_deleteShapeButton = new QPushButton("Delete Shape", controlPanel);
    layout->addWidget(m_deleteShapeButton);
    connect(m_deleteShapeButton, &QPushButton::clicked, this, &IntersectionWindow::deleteShape);

    m_intersectionButton = new QPushButton("Intersection", controlPanel);
    layout->addWidget(m_intersectionButton);
    // connect(m_intersectionButton, &QPushButton::clicked, this, &IntersectionWindow::performIntersection);

    m_unionButton = new QPushButton("Union", controlPanel);
    layout->addWidget(m_unionButton);
    // connect(m_unionButton, &QPushButton::clicked, this, &IntersectionWindow::performUnion);

    m_subtractionButton = new QPushButton("Subtraction", controlPanel);
    layout->addWidget(m_subtractionButton);
    // connect(m_subtractionButton, &QPushButton::clicked, this, &IntersectionWindow::performSubtraction);

    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}

void IntersectionWindow::addShape() {
    QString shape = m_shapeSelector->currentText();
    std::vector<double> params = {
        m_param1->text().toDouble(),
        m_param2->text().toDouble(),
        m_param3->text().toDouble(),
        m_param4->text().toDouble()
    };

    m_shapeList->addItem(shape);
    m_intersectionWidget->addShape(shape, params);
}

void IntersectionWindow::deleteShape() {
    QListWidgetItem* item = m_shapeList->currentItem();
    if (item) {
        m_intersectionWidget->deleteShape(item->text());
        delete item;
    }
}

// void IntersectionWindow::performIntersection() {
//     m_intersectionWidget->performIntersection();
// }

// void IntersectionWindow::performUnion() {
//     m_intersectionWidget->performUnion();
// }

// void IntersectionWindow::performSubtraction() {
//     m_intersectionWidget->performSubtraction();
// }