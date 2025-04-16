#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include <QMouseEvent>
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\include\Conversions\Triangle.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    void loadAndDrawShape(const QString &objFilePath); // Method to load and draw a shape from an OBJ file

protected:
    void initializeGL() override; // Initializes OpenGL settings
    void resizeGL(int w, int h) override; // Handles resizing of the OpenGL viewport
    void paintGL() override; // Renders the OpenGL scene

    // Mouse interaction for rotating the cuboid
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent (QWheelEvent* event) override;

private:
    std::vector<Triangle> triangles; // List of triangles to render
    std::vector<Vec3> vertices; // List of vertices to render
    // QVector<QVector3D> vertices;
    // QVector<unsigned int> indices;
    // QVector<QVector3D> normals;

    QPointF lastMousePos;
 
    QTimer* updateTimer;
    float zoom = -10.0f; // Distance from camera
    float aspectRatio = 1.0f; // Aspect ratio for the viewport
    float fov = 45.0f; // Field of view
    float nearPlane = 0.1f; // Near clipping plane
    float farPlane = 100.0f; // Far clipping plane
    float cameraSpeed = 0.1f; // Speed of camera movement
    float cameraSensitivity = 0.1f; // sensitivity for mouse movement
    float cameraRotationSpeed = 0.1f; // speed of camera rotation
    float cameraZoomSpeed = 0.1f; // speed of camera zooming
    float cameraPanSpeed = 0.1f; // speed of camera panning
    float cameraTiltSpeed = 0.1f; // speed of camera tilting
    float cameraRollSpeed = 0.1f; // speed of camera rolling
    float cameraDollySpeed = 0.1f; // speed of camera dolly
    float cameraTrackSpeed = 0.1f; // speed of camera tracking
    float cameraOrbitSpeed = 0.1f; // speed of camera orbiting
    float cameraPanSensitivity = 0.1f; // sensitivity for camera panning
    float cameraTiltSensitivity = 0.1f; // sensitivity for camera tilting
    float cameraRollSensitivity = 0.1f; // sensitivity for camera rolling
    float cameraDollySensitivity = 0.1f; // sensitivity for camera dolly
    float cameraTrackSensitivity = 0.1f; // sensitivity for camera tracking
    float cameraOrbitSensitivity = 0.1f; // sensitivity for camera orbiting

    float rotationX; // Rotation angle around the X-axis
    float rotationY; // Rotation angle around the Y-axis
    QPoint lastMousePosition; // Last mouse position for tracking movement
};

#endif // OPENGLWIDGET_H

// #pragma once

// #include <QOpenGLWidget>
// #include <QOpenGLFunctions>
// #include <QVector3D>
// #include <vector>

// class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
//     Q_OBJECT

// public:
//     OpenGLWidget(QWidget *parent = nullptr);
//     void addShape(const QString &shapeType);
//     void removeShape(int index);
//     void loadAndDrawShape(const QString &objFilePath);

//     void setTranslation(float x, float y, float z);
//     void setRotation(float x, float y, float z);
//     void setScaling(float x, float y, float z);

// protected:
//     void initializeGL() override;
//     void resizeGL(int w, int h) override;
//     void paintGL() override;

// private:
//     struct Shape {
//         QString type;
//         QVector3D translation;
//         QVector3D rotation;
//         QVector3D scale;
//     };

//     std::vector<Shape> shapes;

//     QVector3D currentTranslation, currentRotation, currentScale;
// };
