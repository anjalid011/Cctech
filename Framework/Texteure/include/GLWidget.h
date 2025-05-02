#ifndef GLWIDGET_H
#define GLWIDGET_H
#pragma once
 
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
 
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();
 
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
 
private:
    void initSphere(float radius, int sectors, int stacks);
    void setupShaders();

    // ...existing code...
    QOpenGLTexture* skyboxTexture = nullptr;
    GLuint skyboxVAO = 0, skyboxVBO = 0;
    QOpenGLShaderProgram skyboxProgram;
 
    QOpenGLShaderProgram program;
    QOpenGLTexture *texture;
    QOpenGLTexture *texture2;
    QOpenGLTexture *texture3; // for the moon

    float moonRevolutionAngle = 0.0f;
 
    GLuint vao, vbo, ebo;
    int indexCount;
 
    QMatrix4x4 projection, view;

    float rotationX = 0.0f; // Rotation angle around the X-axis
    float rotationY = 0.0f; // Rotation angle around the Y-axis
    float zoom = -5.0f;     // Zoom level
    QVector3D translationOffset = QVector3D(0.0f, 0.0f, 0.0f); // Translation offset
    QPoint lastMousePos;    // To track the last mouse position for rotation and translation

    float revolutionAngle = 0.0f; // Angle for revolution around the Y-axis
    QTimer *animationTimer; // Timer for animation
};
 
#endif // GLWIDGET_H