#ifndef BEZIER_H
#define BEZIER_H

#include <QPoint>
#include <QVector>
#include <QPainter>

class Bezier {
public:
    void addControlPoint(const QPoint &pt);
    void updateControlPoint(int index, const QPoint &pt);
    QPoint getControlPoint(int index) const;
    void clear();
    int controlPointCount() const;
    void calculateCurve(int numInterp);
    void drawControlPolygon(QPainter &painter);
    void drawCurve(QPainter &painter);

private:
    QVector<QPoint> controlPoints;
    QVector<QPoint> curvePoints;
    QPoint deCasteljau(double t) const;
};

#endif // BEZIER_H