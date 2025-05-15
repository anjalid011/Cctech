#ifndef SKETCHGLWIDGET_H
#define SKETCHGLWIDGET_H

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QColor>
#include <QVector3D>
#include <vector>
#include <QPointF>
#include <array>

class SketchGLWidget : public QOpenGLWidget {
    Q_OBJECT

public:
    explicit SketchGLWidget(QWidget* parent = nullptr);

    void finishCurrentShape();
    void applyUnion();
    void applyIntersection();
    void applySubtraction(bool isAB);
    void clearResult();

    void setDrawingBezier(bool isBezier) { drawingBezier = isBezier; } // Toggle between polygons and Bézier curves

    std::vector<std::vector<QPointF>> getPolygons() const; // Declare getPolygons()
    std::vector<QPointF> getSelectedPolygon() const;       // Declare getSelectedPolygon()
    void findBezierIntersections(); // Find intersections between Bézier curves
    // QRectF bezierBoundingBox(const std::vector<QPointF>& controlPoints, double tStart, double tEnd);
    // void findIntersectionsRecursive(const std::vector<QPointF>& curve1, const std::vector<QPointF>& curve2,
    //                                             double t1Start, double t1End, double t2Start, double t2End, double tolerance);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    bool drawingBezier = false; // Track whether we are drawing Bézier curves
    std::vector<QPointF> currentPoints;
    std::vector<std::vector<QPointF>> shapes; // Polygons
    std::vector<std::vector<QPointF>> bezierCurves; // Bézier curves
    std::vector<QPointF> intersectionPoints; // Intersection points
    std::vector<std::vector<QPointF>> resultRegions;

    int selectedRegionIndex = -1; // Index of the selected region
    QColor resultColor = Qt::transparent; // Color for the result region

    QPointF evaluateBezier(const std::vector<QPointF>& controlPoints, double t); // Evaluate Bézier curve
    
};

bool pointFuzzyEqual(const QPointF& a, const QPointF& b, double eps = 1e-3);

#endif // SKETCHGLWIDGET_H
