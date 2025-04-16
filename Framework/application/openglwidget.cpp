#include "openglwidget.h"
#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\geometry\src\Conversions\FileHandler.cpp"
#include <QOpenGLFunctions>
#include <QDebug>

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
    GLfloat fovy = 100.0f;
    GLfloat near = 0.1f;
    GLfloat far = 100.0f;
    GLfloat top = tan(fovy * M_PI / 360.0f) * near;
    GLfloat bottom = -top;
    GLfloat right = top * aspect;
    GLfloat left = -right;
 
    glFrustum(left, right, bottom, top, near, far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Renders the OpenGL scene
void OpenGLWidget::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
    glLoadIdentity(); // Reset transformations

    // Apply transformations to center the cuboid
    glTranslatef(0.0f, 0.0f, -5.0f + zoom);// Move the cuboid back along the Z-axis
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f); // Rotate around the X-axis
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f); // Rotate around the Y-axis

    // Enable wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

void OpenGLWidget::mousePressEvent(QMouseEvent* event) {
    lastMousePos = event->position();
}
 
void OpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
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
 
void OpenGLWidget::wheelEvent(QWheelEvent* event) {
    zoom += event->angleDelta().y() / 600.0f; // smoother zoom
    update();
}

