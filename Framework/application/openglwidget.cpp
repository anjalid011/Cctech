#include "openglwidget.h"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\src\Conversions\FileHandler.cpp"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\include\Shapes\Geometry.h"
#include <QOpenGLFunctions>
#include <QDebug>
#include <QVector3D>
#include <vector>
#include <cmath>
#include <cstdlib> 
// #include <GL/gl.h>
// Constructor for OpenGLWidget
OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
    setMinimumSize(400, 400); // Set a minimum size for the widget
    setFocusPolicy(Qt::StrongFocus); // Ensure the widget can receive focus
    setMouseTracking(true);         // Enable mouse tracking
}

// Initializes OpenGL settings
void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions(); // Initialize OpenGL functions
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
}

// Handles resizing of the OpenGL viewport
void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 
    GLfloat aspect = GLfloat(w) / h;
    GLfloat fovy = 45.0f;
    GLfloat near = 0.1f;
    GLfloat far = 100.0f;
    // GLfloat top = tan(fovy * M_PI / 360.0f) * near;
    // GLfloat bottom = -top;
    // GLfloat right = top * aspect;
    // GLfloat left = -right;
    GLfloat top = near * tan(fovy * M_PI / 360.0);
    GLfloat bottom = -top;
    GLfloat left = bottom * aspect;
    GLfloat right = top * aspect;

    glFrustum(left, right, bottom, top, near, far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Renders the OpenGL scene
void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
    glLoadIdentity(); // Reset transformations

    // Apply transformations for zoom and rotation
    glTranslatef(0.0f, 0.0f, -10.0f + zoom);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    // Render control points
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red for control points
    for (const auto& pt : controlPoints) {
        glVertex3f(pt.x, pt.y, pt.z);
    }
    glEnd();

    // Render the Bezier curve if there are enough control points
    if (controlPoints.size() >= 2) {
        bezierCurve.setControlPoints(controlPoints);
        bezierCurve.generateCurvePoints(interpolationPoints);
        bezierCurve.draw();
    }

    glFlush();
}

void OpenGLWidget::clearControlPoints() {
    controlPoints.clear();
    update(); // Redraw the scene
}

// Method to load and draw a shape from an OBJ file
void OpenGLWidget::loadAndDrawShape(const QString &objFilePath) {
    vertices.clear();
    triangles.clear();

    // Read the OBJ file and populate vertices and triangles
    if (!FileHandler::readOBJFile(objFilePath.toStdString(), vertices, triangles)) {
        qDebug() << "Failed to load OBJ file:" << objFilePath;
        return;
    }

    qDebug() << "Loaded OBJ file with" << vertices.size() << "vertices and" << triangles.size() << "triangles.";
    update(); // Trigger a repaint
}

void OpenGLWidget::setTotalControlPoints(int totalPoints) {
    totalControlPoints = totalPoints;
}

void OpenGLWidget::setInterpolationPoints(int points) {
    interpolationPoints = points;
}

void OpenGLWidget::drawBezier(const std::vector<Point3D>& controlPoints, int interpolationPoints) {
    // Clear any existing data
    vertices.clear();
    triangles.clear();

    // Set the control points and generate the Bezier curve
    bezierCurve.setControlPoints(controlPoints);
    bezierCurve.generateCurvePoints(interpolationPoints);

    qDebug() << "Bezier curve generated with" << controlPoints.size() << "control points and" << interpolationPoints << "interpolation points.";

    // Render the Bezier curve
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
    glLoadIdentity(); // Reset transformations

    // Apply transformations for zoom and rotation
    glTranslatef(0.0f, 0.0f, -10.0f + zoom);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    update(); // Trigger a repaint
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event) {
    QPointF mousePos = event->position();
    float x = (2.0f * mousePos.x() / width()) - 1.0f;
    float y = 1.0f - (2.0f * mousePos.y() / height());

    if (currentControlPoints < totalControlPoints) {
        // Add a new control point
        controlPoints.push_back({x, y, 0.0f});
        currentControlPoints++;
        qDebug() << "Control Point Added: X:" << x << "Y:" << y << "Z: 0.0";
        update();
    } else {
        // Check if the click is near any existing control point
        for (size_t i = 0; i < controlPoints.size(); ++i) {
            float dx = controlPoints[i].x - x;
            float dy = controlPoints[i].y - y;
            if (std::sqrt(dx * dx + dy * dy) < 0.1f) { // Threshold for detecting a click near a point
                draggedPointIndex = i;
                qDebug() << "Dragging control point at index:" << i;
                return;
            }
        }
    }
}
 
void OpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
    if (draggedPointIndex != -1) { // If a control point is being dragged
        QPointF mousePos = event->position();
        float x = (2.0f * mousePos.x() / width()) - 1.0f;
        float y = 1.0f - (2.0f * mousePos.y() / height());

        // Update the position of the dragged control point
        controlPoints[draggedPointIndex].x = x;
        controlPoints[draggedPointIndex].y = y;

        qDebug() << "Control Point Dragged: Index:" << draggedPointIndex << "X:" << x << "Y:" << y;

        // Update the curve
        if (controlPoints.size() >= 2) {
            bezierCurve.setControlPoints(controlPoints);
            bezierCurve.generateCurvePoints(interpolationPoints);
        }

        update(); // Redraw the scene
    }
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && draggedPointIndex != -1) {
        qDebug() << "Stopped dragging control point at index:" << draggedPointIndex;
        draggedPointIndex = -1; // Reset the dragged point index
    }
}
 
void OpenGLWidget::wheelEvent(QWheelEvent* event) {
    zoom += event->angleDelta().y() / 600.0f; // smoother zoom
    update();
}


int OpenGLWidget::binomialCoefficient(int n, int k) {
    if (k == 0 || k == n) return 1;
    return binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
}
