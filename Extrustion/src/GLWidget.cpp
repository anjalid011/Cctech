#include "Windows.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "GLWidget.h"
GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent), currentSolid(nullptr) {}

void GLWidget::setSolid(Solid* solid) {
    currentSolid = solid;
    update();
}

void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPointSize(8.0f);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, float(w)/h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, zoom); // Move cube into view
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // drawCube();

    if (currentSolid) {
        for (auto face : currentSolid->faces) {
            glBegin(GL_LINE_LOOP);
            for (auto edge : face->edges) {
                glVertex3f(edge->v1->x, edge->v1->y, edge->v1->z);
            }
            glEnd();
        }
    }
    if (!profilePoints.empty()) {
        glColor3f(0.0f, 1.0f, 0.0f); // green for vertices
        glBegin(GL_POINTS);
        for (const QVector3D& pt : profilePoints) {
            glVertex3f(pt.x(), pt.y(), pt.z());
        }
        glEnd();
    
        // 2. Draw lines between them
        if (profilePoints.size() > 1) {
            glColor3f(1.0f, 1.0f, 0.0f); // yellow for edges
            glBegin(GL_LINE_LOOP);
            for (const QVector3D& pt : profilePoints) {
                glVertex3f(pt.x(), pt.y(), pt.z());
            }
            glEnd();
        }
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    lastMousePos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    int dx = event->position().x() - lastMousePos.x();
    int dy = event->position().y() - lastMousePos.y();
    

    if (event->buttons() & Qt::LeftButton) {
        xRot += dy;
        yRot += dx;
        update(); // triggers paintGL()
    }

    lastMousePos = event->position().toPoint();

}

void GLWidget::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0)
        zoom += 0.5f;  // Scroll up: zoom in
    else
        zoom -= 0.5f;  // Scroll down: zoom out

    update(); // Redraw with new zoom
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        float x = (2.0f * event->position().x()) / width() - 1.0f;
        float y = 1.0f - (2.0f * event->position().y()) / height();

        float z = 0.0f;
        QVector3D point(x, y, z);  // multiply with -zoom to stay in visible space
        profilePoints.push_back(point);
        update();
    }
}
#include "Extrusion.h"

void GLWidget::performExtrusion() {
    if (profilePoints.size() < 3) return;  // Need at least 3 points

    // Convert QVector3D to Vertex*
    std::vector<Vertex*> vertices;
    for (const auto& p : profilePoints) {
        vertices.push_back(new Vertex(p.x(), p.y(), p.z()));
    }

    // Create edges
    std::vector<Edge*> edges;
    for (size_t i = 0; i < vertices.size(); ++i) {
        edges.push_back(new Edge(vertices[i], vertices[(i+1)%vertices.size()]));
    }

    Face* baseFace = new Face(edges);
    Solid* solid = Extrusion::Extrude(baseFace, Vertex(0, 0, 1), 1.0f);  // Extrude in +Z

    profilePoints.clear();  // reset input after extrusion
    setSolid(solid);        // update solid to render
}
