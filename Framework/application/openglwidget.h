#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include <QMouseEvent>
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\include\Conversions\Triangle.h"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\include\Shapes\Geometry.h"


class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    void loadAndDrawShape(const QString &objFilePath); // Method to load and draw a shape from an OBJ file
    void drawBezier(const std::vector<Point3D>& controlPoints, int interpolationPoints);
    void clearControlPoints();
    int binomialCoefficient(int n, int k);
    void setTotalControlPoints(int totalPoints);
    void setInterpolationPoints(int points);

protected:
    void initializeGL() override; // Initializes OpenGL settings
    void resizeGL(int w, int h) override; // Handles resizing of the OpenGL viewport
    void paintGL() override; // Renders the OpenGL scene
    
    // Mouse interaction for rotating the cuboid
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent (QWheelEvent* event) override;

private:
    std::vector<Triangle> triangles; // List of triangles to render
    std::vector<Vec3> vertices; // List of vertices to render
    std::vector<Point3D> controlPoints;
    int totalControlPoints = 0; // Total number of control points specified by the user
    int currentControlPoints = 0; // Number of control points added so far
    int interpolationPoints = 20; // Number of interpolation points
    int draggedPointIndex = -1; 
    QPointF lastMousePos;
    Bezier3D bezierCurve;
    QTimer* updateTimer;
    float zoom = -5.0f; // Distance from camer

    float rotationX= 0.0f; // Rotation angle around the X-axis
    float rotationY= 0.0f; // Rotation angle around the Y-axis
    QPoint lastMousePosition; // Last mouse position for tracking movement
};

#endif // OPENGLWIDGET_H

