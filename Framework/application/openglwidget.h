#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

protected:
    void initializeGL() override; // Called once to initialize OpenGL
    void resizeGL(int w, int h) override; // Called when the widget is resized
    void paintGL() override; // Called to render the OpenGL scene
};

#endif // OPENGLWIDGET_H