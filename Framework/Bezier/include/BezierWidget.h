#pragma once
 
#include <QOpenGLWidget>
#include <QVector>
#include <QPointF>
#include <QOpenGLFunctions>
#include <QPushButton>
#include <QMatrix4x4>
 
class BezierWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
 
public:
    BezierWidget(QWidget *parent = nullptr);
    ~BezierWidget();
    void clear();

 
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
 
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
 
private:
    QVector3D computeNormal(const QVector3D &p1, const QVector3D &p2, const QVector3D &p3);
    QVector<QPointF> controlPoints;
    QVector<QPointF> bezierCurve;
    QVector<QPointF> curvePoints;
    QVector<QVector<QVector3D>> revolutionMesh;
 
    QPushButton *revolveButton;
    int draggedPointIndex = -1;
 
    void computeBezierCurve();
    QPointF deCasteljau(float t);
    void computeRevolution();
    QVector3D rotatePointAroundAxis(const QVector3D &point, float angle, const QVector3D &axis);
    void drawRevolutionAxis();
    void handleRightClick();
    QPointF mapToOpenGLCoordinates(const QPoint &mousePos);
};