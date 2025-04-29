#pragma once
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include "Structure.h"

class GLWidget : public QOpenGLWidget {
    Q_OBJECT

public:
    GLWidget(QWidget* parent = nullptr);
    void setSolid(Solid* solid);
    void performExtrusion();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event);
    // void keyPressEvent(QKeyEvent *event) override;

private:
    Solid* currentSolid;
    float xRot = 0.0f;
    float yRot = 0.0f;
    float zoom = -5.0f;
    QPoint lastMousePos;
    bool inputMode = true;            // Enable/disable point input mode
    std::vector<QVector3D> profilePoints;  // stores clicked points
};
