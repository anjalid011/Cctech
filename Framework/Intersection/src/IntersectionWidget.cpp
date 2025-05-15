#include "IntersectionWidget.h"
#include "intersection.h"
#include <QDebug>
#include <cmath>
#include "Geometry.h"

IntersectionWidget::IntersectionWidget(QWidget* parent)
    : QOpenGLWidget(parent), m_solid1(nullptr), m_solid2(nullptr) {}

void IntersectionWidget::setSolids(Shape* solid1, Shape* solid2) {
    m_solid1 = solid1;
    m_solid2 = solid2;
}

// Initializes OpenGL settings
void IntersectionWidget::initializeGL() {
    initializeOpenGLFunctions(); // Initialize OpenGL functions
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
}

// Handles resizing of the OpenGL viewport
void IntersectionWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspect = GLfloat(w) / h;
    GLfloat fovy = 45.0f;
    GLfloat near = 0.1f;
    GLfloat far = 100.0f;
    GLfloat top = near * tan(fovy * M_PI / 360.0);
    GLfloat bottom = -top;
    GLfloat left = bottom * aspect;
    GLfloat right = top * aspect;

    glFrustum(left, right, bottom, top, near, far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Renders the OpenGL scene
void IntersectionWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
    glLoadIdentity(); // Reset transformations

    // Apply transformations for zoom and rotation
    glTranslatef(0.0f, 0.0f, -10.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Render the loaded shapes
    for (Shape* shape : m_shapes) {
        shape->draw(); // Call the draw method of each shape
    }

    glFlush();
}

void IntersectionWidget::addShape(const QString& shape, const std::vector<double>& params) {
    Shape* newShape = nullptr;

    if (shape == "Line") {
        if (params.size() == 4) {
            newShape = new Line(params[0], params[1], params[2], params[3]); // 2D Line
        } else if (params.size() == 6) {
            newShape = new Line(params[0], params[1], params[2], params[3], params[4], params[5]); // 3D Line
        }
    } else if (shape == "Rectangle") {
        newShape = new Rectangle(params[0], params[1], params[2], params[3]); // x, y, width, height
    } else if (shape == "Cuboid") {
        newShape = new Cuboid(params[0], params[1], params[2], params[3], params[4], params[5]); // x, y, z, width, height, depth
    } else if (shape == "Circle") {
        newShape = new Circle(params[0]); // Radius
    } else if (shape == "Sphere") {
        newShape = new Sphere(params[0], params[1], params[2], params[3]); // Radius, centerX, centerY, centerZ
    } else if (shape == "Cone") {
        newShape = new Cone(params[0], params[1], params[2], params[3], params[4]); // Radius, height, centerX, centerY, centerZ
    } else if (shape == "Cylinder") {
        newShape = new Cylinder(params[0], params[1], params[2], params[3], params[4]); // Radius, height, centerX, centerY, centerZ
    } else if (shape == "Bezier3D") {
        Bezier3D* bezier = new Bezier3D();
        std::vector<Point3D> controlPoints;
        for (size_t i = 0; i < params.size(); i += 3) {
            controlPoints.push_back({params[i], params[i + 1], params[i + 2]});
        }
        bezier->setControlPoints(controlPoints);
        newShape = bezier;
    }

    if (newShape) {
        m_shapes.push_back(newShape);
    }
}

void IntersectionWidget::deleteShape(const QString& shape) {
    // Logic to delete a shape
    for (auto it = m_shapes.begin(); it != m_shapes.end(); ++it) {
        // Match and delete the shape
        m_shapes.erase(it);
        break;
    }
}

// void IntersectionWidget::performIntersection() {
//     if (m_shapes.size() >= 2) {
//         Shape* result = Intersection::intersect(m_shapes[0], m_shapes[1]);
//         emit operationPerformed(result);
//     }
// }

// void IntersectionWidget::performUnion() {
//     if (m_shapes.size() >= 2) {
//         Shape* result = Intersection::unite(m_shapes[0], m_shapes[1]);
//         emit operationPerformed(result);
//     }
// }

// void IntersectionWidget::performSubtraction() {
//     if (m_shapes.size() >= 2) {
//         Shape* result = Intersection::subtract(m_shapes[0], m_shapes[1]);
//         emit operationPerformed(result);
//     }
// }