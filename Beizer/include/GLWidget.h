#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QVector3D>
#include "Bezier.h"

class GLWidget : public QOpenGLWidget {
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    void startDrawing(int controlCount, int interpCount);
    void show3D(bool enable);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void drawAxes2D(QPainter &painter);
    void drawAxes3D();

private:
    void generateRevolutionMesh(int segments = 64);

    Bezier bezier;
    int controlPointCount;
    int interpPointCount;
    bool drawingEnabled;
    int draggingIndex = -1;
    bool show3DView;
    
    QPointF projectToScreen(const QVector3D& point);

    // 3D mesh data
    std::vector<QVector3D> meshVertices;
    std::vector<std::pair<int, int>> meshEdges;
};

#endif // GLWIDGET_H