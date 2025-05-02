#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\Bezier\include\bezierWindow.h"
#include <QVBoxLayout>
#include <QPushButton>

BezierWindow::BezierWindow(QWidget *parent) : QMainWindow(parent) {
    // Create the central widget and layout
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    // Create the BezierWidget and add it to the layout
    BezierWidget *bezierWidget = new BezierWidget(this);
    layout->addWidget(bezierWidget);

    // Add a button to clear the Bézier curve
    QPushButton *clearButton = new QPushButton("Clear", this);
    layout->addWidget(clearButton);

    // Connect the clear button to clear the Bézier curve
    connect(clearButton, &QPushButton::clicked, [bezierWidget]() {
        bezierWidget->clear();
        bezierWidget->update();
    });

    // Set the layout and central widget
    central->setLayout(layout);
    setCentralWidget(central);
}

BezierWindow::~BezierWindow() {}