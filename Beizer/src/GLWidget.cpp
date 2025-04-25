#include "GLWidget.h"
#include "Bezier.h"
#include <QPainter>
#include <QOpenGLFunctions>
#include <cmath>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), controlPointCount(0), interpPointCount(0), drawingEnabled(false), draggingIndex(-1) {}

void GLWidget::initializeGL() {
    // You can set up OpenGL state here if needed
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use QPainter for 2D drawing over OpenGL context
    QPainter painter(this);
    bezier.drawControlPolygon(painter);
    if (bezier.controlPointCount() == controlPointCount) {
        bezier.calculateCurve(interpPointCount);
        bezier.drawCurve(painter);
    }
}

void GLWidget::startDrawing(int controlCount, int interpCount) {
    bezier.clear();
    controlPointCount = controlCount;
    interpPointCount = interpCount;
    drawingEnabled = true;
    draggingIndex = -1;
    update();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    if (drawingEnabled && bezier.controlPointCount() < controlPointCount) {
        bezier.addControlPoint(event->pos());
        update();
    }
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    for (int i = 0; i < bezier.controlPointCount(); ++i) {
        if ((bezier.getControlPoint(i) - event->pos()).manhattanLength() < 10) {
            draggingIndex = i;
            break;
        }
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    if (draggingIndex != -1) {
        bezier.updateControlPoint(draggingIndex, event->pos());
        update();
    }
}