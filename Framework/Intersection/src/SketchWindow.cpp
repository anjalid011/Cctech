#include "SketchWindow.h"
#include "SketchGLWidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>

SketchWindow::SketchWindow(QWidget* parent)
    : QMainWindow(parent) {
    sketchGLWidget = new SketchGLWidget(this);

    toggleModeBtn = new QPushButton("Switch to Bézier Mode");
    finishShapeBtn = new QPushButton("Finish Shape");
    unionBtn = new QPushButton("Union");
    intersectBtn = new QPushButton("Intersection");
    subtractBtn = new QPushButton("Subtraction");
    clearResultBtn = new QPushButton("Clear Result");

    connect(toggleModeBtn, &QPushButton::clicked, this, &SketchWindow::toggleDrawingMode);
    connect(finishShapeBtn, &QPushButton::clicked, this, &SketchWindow::onFinishShape);
    connect(unionBtn, &QPushButton::clicked, this, &SketchWindow::onUnion);
    connect(intersectBtn, &QPushButton::clicked, this, &SketchWindow::onIntersection);
    connect(subtractBtn, &QPushButton::clicked, this, &SketchWindow::onSubtraction);
    connect(clearResultBtn, &QPushButton::clicked, sketchGLWidget, &SketchGLWidget::clearResult);

    QHBoxLayout* buttons = new QHBoxLayout;
    buttons->addWidget(toggleModeBtn);
    buttons->addWidget(finishShapeBtn);
    buttons->addWidget(unionBtn);
    buttons->addWidget(intersectBtn);
    buttons->addWidget(subtractBtn);
    buttons->addWidget(clearResultBtn);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(sketchGLWidget);
    layout->addLayout(buttons);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    setWindowTitle("2D Sketch Editor");
    resize(800, 600);

    updateButtonVisibility(); // Ensure correct button visibility on startup
}

void SketchWindow::toggleDrawingMode() {
    isDrawingBezier = !isDrawingBezier;
    sketchGLWidget->setDrawingBezier(isDrawingBezier); // Inform the widget about the mode change
    toggleModeBtn->setText(isDrawingBezier ? "Switch to Polygon Mode" : "Switch to Bézier Mode");
    updateButtonVisibility(); // Update button visibility based on the mode
}

void SketchWindow::updateButtonVisibility() {
    if (isDrawingBezier) {
        // Show only "Finish Shape" and "Intersection" buttons in Bézier mode
        finishShapeBtn->setVisible(true);
        intersectBtn->setVisible(true);
        unionBtn->setVisible(false);
        subtractBtn->setVisible(false);
        clearResultBtn->setVisible(false);
    } else {
        // Show all buttons in Polygon mode
        finishShapeBtn->setVisible(true);
        intersectBtn->setVisible(true);
        unionBtn->setVisible(true);
        subtractBtn->setVisible(true);
        clearResultBtn->setVisible(true);
    }
}

void SketchWindow::onFinishShape() { sketchGLWidget->finishCurrentShape(); }
void SketchWindow::onUnion() { sketchGLWidget->applyUnion(); }
void SketchWindow::onIntersection() { 
    if (isDrawingBezier) {
        sketchGLWidget->findBezierIntersections(); // Highlight Bézier intersections
    } else {
        sketchGLWidget->applyIntersection(); // Perform polygon intersection
    }
}

void SketchWindow::onSubtraction() {
    QStringList options = { "A - B", "B - A" };
    bool ok;
    QString choice = QInputDialog::getItem(this, "Subtraction Operation", 
                                           "Choose operation:", options, 0, false, &ok);
    if (ok && !choice.isEmpty()) {
        if (choice == "A - B") {
            sketchGLWidget->applySubtraction(true);  // A - B
        } else if (choice == "B - A") {
            sketchGLWidget->applySubtraction(false); // B - A
        }
    }
}

