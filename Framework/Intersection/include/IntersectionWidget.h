#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include "Structure.h"
#include "Shape.h"
#include <QString>

class IntersectionWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit IntersectionWidget(QWidget* parent = nullptr);

    // Add or delete shapes
    void addShape(const QString& shape, const std::vector<double>& params);
    void deleteShape(const QString& shape);

    // Set the solids to perform operations on
    void setSolids(Shape* solid1, Shape* solid2);
    

signals:
    void operationPerformed(Solid* result);

protected:
    void initializeGL() override; // Initializes OpenGL settings
    void resizeGL(int w, int h) override; // Handles resizing of the OpenGL viewport
    void paintGL() override; // Renders the OpenGL scene

public slots:
    // void performIntersection();
    // void performUnion();
    // void performSubtraction();

private:
    Shape* m_solid1;
    Shape* m_solid2;
    std::vector<Shape*> m_shapes;
};