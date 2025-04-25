#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QMouseEvent>
#include "Bezier.h"

class GLWidget : public QOpenGLWidget {
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    void startDrawing(int controlCount, int interpCount);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Bezier bezier;
    int controlPointCount;
    int interpPointCount;
    bool drawingEnabled;
    int draggingIndex;
};

#endif // GLWIDGET_H