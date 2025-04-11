#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

OpenGLWidget::~OpenGLWidget()
{
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the background color
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h); // Set the viewport to cover the entire widget
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Example: Draw a simple triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.5f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.5f);
    glEnd();
}