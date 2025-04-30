#include "GLWidget.h"
#include "Bezier.h"
#include <QPainter>
#include <QOpenGLFunctions>
#include <cmath>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), controlPointCount(0), interpPointCount(0),
      drawingEnabled(false), draggingIndex(-1), show3DView(false) {}

void GLWidget::initializeGL() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark background
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!show3DView) {
        QPainter painter(this);
        drawAxes2D(painter);
        bezier.drawControlPolygon(painter);
        if (bezier.controlPointCount() == controlPointCount) {
            bezier.calculateCurve(interpPointCount);
            bezier.drawCurve(painter);
        }
    } else {
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glEnable(GL_DEPTH_TEST);

        // Lighting setup
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        GLfloat light_pos[] = {0, 0, -400, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-width()/2, width()/2, height()/2, -height()/2, -1000, 1000);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, -400);
        glRotatef(30, 1, 0, 0);
        glRotatef(30, 0, 1, 0);

        drawAxes3D();

        // Draw filled mesh
        glColor3f(0.7f, 0.7f, 0.7f);
        int seg = 64;
        int curvePts = bezier.getCurvePoints().size();
        for (int i = 0; i < curvePts - 1; ++i) {
            for (int j = 0; j < seg; ++j) {
                int nextJ = (j + 1) % seg;
                int idx0 = i * seg + j;
                int idx1 = i * seg + nextJ;
                int idx2 = (i + 1) * seg + nextJ;
                int idx3 = (i + 1) * seg + j;
                glBegin(GL_QUADS);
                QVector3D v0 = meshVertices[idx0];
                QVector3D v1 = meshVertices[idx1];
                QVector3D v2 = meshVertices[idx2];
                QVector3D v3 = meshVertices[idx3];
                // Compute normals for lighting
                QVector3D n = QVector3D::normal(v0, v1, v2);
                glNormal3f(n.x(), n.y(), n.z());
                glVertex3f(v0.x(), v0.y(), v0.z());
                glVertex3f(v1.x(), v1.y(), v1.z());
                glVertex3f(v2.x(), v2.y(), v2.z());
                glVertex3f(v3.x(), v3.y(), v3.z());
                glEnd();
            }
        }
        glDisable(GL_LIGHTING);
    }
    // Draw 3D control polygon (lines between control points)
    glColor3f(1.0f, 0.0f, 0.0f); // Red lines
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < bezier.controlPointCount(); ++i) {
        QPointF pt = bezier.getControlPoint(i);
        float x = pt.x() - width() / 2.0f;
        float y = pt.y() - height() / 2.0f;
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    // Draw 3D control points (as small spheres or cubes)
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < bezier.controlPointCount(); ++i) {
        QPointF pt = bezier.getControlPoint(i);
        float x = pt.x() - width() / 2.0f;
        float y = pt.y() - height() / 2.0f;
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
    }

void GLWidget::startDrawing(int controlCount, int interpCount) {
    bezier.clear();
    controlPointCount = controlCount;
    interpPointCount = interpCount;
    drawingEnabled = true;
    draggingIndex = -1;
    show3DView = false;
    update();
}

void GLWidget::show3D(bool enable) {
    if (enable && bezier.controlPointCount() == controlPointCount) {
        bezier.calculateCurve(interpPointCount);
        generateRevolutionMesh();
        show3DView = true;
        update();
    } else {
        show3DView = false;
        update();
    }
}

void GLWidget::generateRevolutionMesh(int segments) {
    meshVertices.clear();
    meshEdges.clear();
    QVector<QPointF> curve = bezier.getCurvePoints();
    if (curve.isEmpty()) return;

    // Center X axis at 0 for revolution
    float cx = width() / 2.0f;
    for (int i = 0; i < curve.size(); ++i) {
        float x = curve[i].x() - cx;
        float y = curve[i].y() - height() / 2.0f;
        for (int j = 0; j < segments; ++j) {
            double theta = 2.0 * M_PI * j / segments;
            float px = x * cos(theta);
            float pz = x * sin(theta);
            meshVertices.push_back(QVector3D(px, y, pz));
            // Edges along ring
            if (j > 0)
                meshEdges.push_back({i * segments + j - 1, i * segments + j});
        }
        // Close the ring
        meshEdges.push_back({i * segments, i * segments + segments - 1});
    }
    // Connect rings
    for (int i = 1; i < curve.size(); ++i) {
        for (int j = 0; j < segments; ++j) {
            int curr = i * segments + j;
            int prev = (i - 1) * segments + j;
            meshEdges.push_back({prev, curr});
        }
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    if (drawingEnabled && !show3DView && bezier.controlPointCount() < controlPointCount) {
        bezier.addControlPoint(event->pos());
        update();
    }
    
}


void GLWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    // if (!show3DView) {
        for (int i = 0; i < bezier.controlPointCount(); ++i) {
            if ((bezier.getControlPoint(i) - event->pos()).manhattanLength() < 10) {
                draggingIndex = i;
                break;
            }
        }
    // } else {
        int segments = 64;
        if (meshVertices.empty()) return;
        for (int i = 0; i < bezier.controlPointCount(); ++i) {
            for (int j = 0; j < segments; ++j) {
                int idx = i * segments + j;
                if (idx >= meshVertices.size()) continue;
                QPointF pt = projectToScreen(meshVertices[idx]);
                if ((pt - event->pos()).manhattanLength() < 10) {
                    draggingIndex = i;
                    return;
                }
            }
        }
    // }
}

QPointF GLWidget::projectToScreen(const QVector3D& point)
{
    // Simple orthographic projection matching your glOrtho
    float sx = point.x() + width() / 2.0f;
    float sy = height() / 2.0f - point.y();
    return QPointF(sx, sy);
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    if (draggingIndex != -1) {
        if (!show3DView) {
            bezier.updateControlPoint(draggingIndex, event->pos());
        } else {
            // In 3D, update only X (radius) and Y (height) based on mouse
            QPoint pt = event->pos();
            // Convert screen X to model X (radius)
            float modelX = pt.x() - width()/2;
            float modelY = pt.y() - height()/2;
            bezier.updateControlPoint(draggingIndex, QPoint(modelX + width()/2, modelY + height()/2));
            bezier.calculateCurve(interpPointCount);
            generateRevolutionMesh();
        }
        update();
    }
}
void GLWidget:: drawAxes2D(QPainter &painter) {
    painter.setPen(QPen(Qt::white, 1));
    painter.drawLine(width()/2, 0, width()/2, height());
    painter.drawLine(0, height()/2, width(), height()/2);
}

void GLWidget::drawAxes3D() {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    // X axis - Red
    glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(100,0,0);
    // Y axis - Green
    glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,100,0);
    // Z axis - Blue
    glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,100);
    glEnd();
}