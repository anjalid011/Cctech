#include "SketchGLWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <vector>
#include <cmath>
#include "polygon_boolean.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

SketchGLWidget::SketchGLWidget(QWidget* parent)
    : QOpenGLWidget(parent), selectedRegionIndex(-1), resultColor(Qt::transparent), drawingBezier(false) {
    resultRegions.clear();
}

void SketchGLWidget::initializeGL() {
    glClearColor(1, 1, 1, 1);  // White background
}

void SketchGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void SketchGLWidget::paintGL() {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw polygons
    QPen polygonPen(Qt::black, 2);
    painter.setPen(polygonPen);
    for (const auto& shape : shapes) {
        for (size_t i = 0; i < shape.size(); ++i) {
            painter.drawLine(shape[i], shape[(i + 1) % shape.size()]);
        }
    }

    // Draw Bézier curves
    QPen bezierPen(Qt::blue, 2);
    painter.setPen(bezierPen);
    for (const auto& curve : bezierCurves) {
        for (int i = 0; i < 100; ++i) {
            double t1 = static_cast<double>(i) / 100;
            double t2 = static_cast<double>(i + 1) / 100;
            QPointF p1 = evaluateBezier(curve, t1);
            QPointF p2 = evaluateBezier(curve, t2);
            painter.drawLine(p1, p2);
        }
    }

    // // Draw intersection points
    // QPen intersectionPen(Qt::red, 5);
    // painter.setPen(intersectionPen);
    // for (const auto& point : intersectionPoints) {
    //     painter.drawPoint(point);
    // }

    painter.setPen(QPen(Qt::red, 2));
    for (size_t i = 0; i + 1 < currentPoints.size(); ++i) {
        painter.drawLine(currentPoints[i], currentPoints[i + 1]);
    }

    for (int i = 0; i < resultRegions.size(); ++i) {
        QBrush brush(i == selectedRegionIndex ? QColor(255, 255, 0, 120) : QColor(100, 100, 255, 100));
        painter.setBrush(brush);
        QPolygonF poly;
        for (const auto& pt : resultRegions[i])
            poly << pt;
        painter.drawPolygon(poly);
    }

    QPen intersectionPen(Qt::red);
    intersectionPen.setWidth(2);
    painter.setPen(intersectionPen);
    painter.setBrush(Qt::red);

    for (const auto& point : intersectionPoints) {
        painter.drawEllipse(point, 4, 4); // A visible 4-pixel radius dot
    }
        painter.end();
}

bool pointFuzzyEqual(const QPointF& a, const QPointF& b, double eps) {
    return std::abs(a.x() - b.x()) < eps && std::abs(a.y() - b.y()) < eps;
}

void SketchGLWidget::mousePressEvent(QMouseEvent* event) {
    QPointF clicked = event->pos();

    if (drawingBezier) {
        currentPoints.push_back(clicked);
        update();
    } else {
        // Existing polygon logic
        selectedRegionIndex = -1;
        for (int i = 0; i < resultRegions.size(); ++i) {
            if (pointInPolygon(clicked, resultRegions[i])) {
                selectedRegionIndex = i;
                update();
                return;
            }
        }

        if (!currentPoints.empty() && pointFuzzyEqual(clicked, currentPoints.front())) {
            finishCurrentShape();
        } else {
            currentPoints.push_back(clicked);
        }
        update();
    }
}

void SketchGLWidget::finishCurrentShape() {
    if (currentPoints.size() < 2) return;

    if (drawingBezier) {
        bezierCurves.push_back(currentPoints);
    } else {
        if (currentPoints.size() < 3) return;
        shapes.push_back(currentPoints);
        qDebug() << "Added shape with" << currentPoints.size()-1 << "points.";
    }

    currentPoints.clear();
    update();
}

void SketchGLWidget::applyUnion() {
    if (shapes.size() < 2) return;
    const auto& poly1 = shapes[0];
    const auto& poly2 = shapes[1];
    auto result = PolygonBoolean::unionPolygons(poly1, poly2);
    if (!result.empty()) {
        resultRegions.clear();
        resultRegions.push_back(result);
        selectedRegionIndex = 0;
        update();
    }
}

void SketchGLWidget::applyIntersection() {
    if (shapes.size() < 2) return;
    const auto& poly1 = shapes[0];
    const auto& poly2 = shapes[1];
    auto result = PolygonBoolean::intersect(poly1, poly2);
    if (!result.empty()) {
        resultRegions.clear();
        resultRegions.push_back(result);
        selectedRegionIndex = 0;
        update();
    }
}

void SketchGLWidget::applySubtraction(bool isAB) {
    if (shapes.size() < 2) return;
    const auto& poly1 = isAB ? shapes[0] : shapes[1];
    const auto& poly2 = isAB ? shapes[1] : shapes[0];
    auto result = PolygonBoolean::subtractPolygons(poly1, poly2);
    if (!result.empty()) {
        shapes = { result };
        resultRegions.clear();
        selectedRegionIndex = -1;
        update();
    }
}

void SketchGLWidget::clearResult() {
    resultRegions.clear();
    selectedRegionIndex = -1;
    resultColor = Qt::transparent;
    update();
}

std::vector<std::vector<QPointF>> SketchGLWidget::getPolygons() const {
    return shapes;
}

std::vector<QPointF> SketchGLWidget::getSelectedPolygon() const {
    if (selectedRegionIndex >= 0 && selectedRegionIndex < resultRegions.size())
        return resultRegions[selectedRegionIndex];
    return {};
}

QPointF SketchGLWidget::evaluateBezier(const std::vector<QPointF>& controlPoints, double t) {
    std::vector<QPointF> points = controlPoints;

    while (points.size() > 1) {
        std::vector<QPointF> nextPoints;
        for (size_t i = 0; i + 1 < points.size(); ++i) {
            double x = (1 - t) * points[i].x() + t * points[i + 1].x();
            double y = (1 - t) * points[i].y() + t * points[i + 1].y();
            nextPoints.push_back(QPointF(x, y));
        }
        points = nextPoints;
    }

    return points[0];
}

void SketchGLWidget::findBezierIntersections() {
    if (bezierCurves.size() < 2) return;

    const auto& curve1 = bezierCurves[0];
    const auto& curve2 = bezierCurves[1];

    intersectionPoints.clear();

    const int samples = 300; // More points = more accurate
    const double epsilon = 3.0; // Distance threshold in pixels

    std::vector<QPointF> points1, points2;

    for (int i = 0; i <= samples; ++i) {
        double t = static_cast<double>(i) / samples;
        points1.push_back(evaluateBezier(curve1, t));
        points2.push_back(evaluateBezier(curve2, t));
    }

    for (const QPointF& p1 : points1) {
        for (const QPointF& p2 : points2) {
            if (QLineF(p1, p2).length() < epsilon) {
                intersectionPoints.push_back((p1 + p2) / 2); // Store mid-point
                break; // avoid duplicates
            }
        }
    }

    qDebug() << "Found" << intersectionPoints.size() << "intersections.";
    update(); // Repaint widget
}


// void SketchGLWidget::findIntersectionsRecursive(const std::vector<QPointF>& curve1, const std::vector<QPointF>& curve2,
//                                                 double t1Start, double t1End, double t2Start, double t2End, double tolerance) {
//     // Evaluate the bounding boxes of the curve segments
//     QRectF bbox1 = bezierBoundingBox(curve1, t1Start, t1End);
//     QRectF bbox2 = bezierBoundingBox(curve2, t2Start, t2End);

//     // Check if the bounding boxes overlap
//     if (!bbox1.intersects(bbox2)) return;

//     // If the bounding boxes are small enough, consider it an intersection
//     if (bbox1.width() < tolerance && bbox1.height() < tolerance &&
//         bbox2.width() < tolerance && bbox2.height() < tolerance) {
//         QPointF intersection = (bbox1.center() + bbox2.center()) / 2;
//         if (std::find(intersectionPoints.begin(), intersectionPoints.end(), intersection) == intersectionPoints.end()) {
//             intersectionPoints.push_back(intersection);
//         }
//         return;
//     }

//     // Subdivide the curve segments and check recursively
//     double t1Mid = (t1Start + t1End) / 2;
//     double t2Mid = (t2Start + t2End) / 2;

//     findIntersectionsRecursive(curve1, curve2, t1Start, t1Mid, t2Start, t2Mid, tolerance);
//     findIntersectionsRecursive(curve1, curve2, t1Start, t1Mid, t2Mid, t2End, tolerance);
//     findIntersectionsRecursive(curve1, curve2, t1Mid, t1End, t2Start, t2Mid, tolerance);
//     findIntersectionsRecursive(curve1, curve2, t1Mid, t1End, t2Mid, t2End, tolerance);
// }

// QRectF SketchGLWidget::bezierBoundingBox(const std::vector<QPointF>& controlPoints, double tStart, double tEnd) {
//     QPointF pStart = evaluateBezier(controlPoints, tStart);
//     QPointF pEnd = evaluateBezier(controlPoints, tEnd);

//     double minX = std::min(pStart.x(), pEnd.x());
//     double minY = std::min(pStart.y(), pEnd.y());
//     double maxX = std::max(pStart.x(), pEnd.x());
//     double maxY = std::max(pStart.y(), pEnd.y());

//     return QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
// }