#include "openglwidget.h"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\src\Conversions\FileHandler.cpp"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\include\Shapes\Geometry.h"
#include <QOpenGLFunctions>
#include <QDebug>
#include <QVector3D>
#include <vector>
#include <cmath>
#include <cstdlib> 
// #include <GL/glu.h>

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
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black

    glEnable(GL_LIGHTING);          // Enable lighting
    glEnable(GL_LIGHT0);            // Enable light source 0
    glEnable(GL_COLOR_MATERIAL);    // Use glColor as material property

    // Set light properties
    GLfloat lightPos[] = { 50.0f, 50.0f, 100.0f, 1.0f }; // Position of light
    GLfloat lightAmbient[]  = { 0.2f, 0.2f, 0.2f, 1.0f }; // Ambient light color
    GLfloat lightDiffuse[]  = { 0.8f, 0.8f, 0.8f, 1.0f }; // Diffuse light color
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Specular light color

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);  // Set ambient light
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);  // Set diffuse light
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular); // Set specular light

    glShadeModel(GL_SMOOTH); // Smooth shading
    glEnable(GL_NORMALIZE);  // Normalize normals for proper lighting
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Position camera
    // gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);


    glPushMatrix();

    // Apply transformations for zoom and rotation
    glTranslatef(0.0f, 0.0f, -10.0f + zoom);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    // Set material properties
    GLfloat matAmbient[]  = { 0.2f, 0.2f, 0.2f, 1.0f }; // Ambient color
    GLfloat matDiffuse[]  = { 0.5f, 0.5f, 0.9f, 1.0f }; // Diffuse color
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Specular color
    GLfloat matShininess[] = { 50.0f };                 // Shininess

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

    addAxis();

     // Render the transformed shape
     const auto& points = transformations.getTransformedPoints();
     if (!points.empty()) {
         glBegin(GL_QUADS); // Assuming the shape is a cuboid
         for (const auto& point : points) {
             glVertex3f(point[0], point[1], point[2]);
         }
         glEnd();
     }

    // Render the loaded triangles
    glBegin(GL_TRIANGLES);
    for (const auto &triangle : triangles) {
        const Vec3 &v1 = vertices[triangle.v1];
        const Vec3 &v2 = vertices[triangle.v2];
        const Vec3 &v3 = vertices[triangle.v3];

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();

    // Restore default polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

void OpenGLWidget::loadShapePoints(const std::vector<std::vector<double>>& points) {
    transformations.loadPoints(points);
    update(); // Trigger a repaint
}

void OpenGLWidget::translateShape(float dx, float dy, float dz) {
    transformations.applyTranslation(dx, dy, dz);
    update(); // Redraw the scene with updated points
}

void OpenGLWidget::rotateShape(float angleX, float angleY, float angleZ) {
    if (angleX != 0) transformations.applyRotation(angleX, 'x');
    if (angleY != 0) transformations.applyRotation(angleY, 'y');
    if (angleZ != 0) transformations.applyRotation(angleZ, 'z');
    update(); // Redraw the scene with updated points
}

void OpenGLWidget::scaleShape(float scaleX, float scaleY, float scaleZ) {
    transformations.applyScaling(scaleX, scaleY, scaleZ);
    update(); // Redraw the scene with updated points
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
    lastMousePos = event->position();
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
    QPointF currentPos = event->position();
     int dx = currentPos.x() - lastMousePos.x();
     int dy = currentPos.y() - lastMousePos.y();
  
     if (event->buttons() & Qt::LeftButton) {
         rotationX += dy * 0.5f;
         rotationY += dx * 0.5f;
         update();
     }
     lastMousePos = currentPos;
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

void OpenGLWidget::addAxis() {
    // Scale the axis length based on the object radius
    // float axisLength = objectRadius * 1.5f; // Adjust the multiplier as needed
 
    // Draw the axis lines
    glBegin(GL_LINES);
 
    // X-axis (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
 
    // Y-axis (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
 
    // Z-axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
 
    glEnd();
 
    // Reset color to white
    glColor3f(1.0f, 1.0f, 1.0f);
}

