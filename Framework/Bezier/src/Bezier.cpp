#include "Bezier.h"

void Bezier::addControlPoint(const QPoint &pt) {
    controlPoints.append(pt);
}

void Bezier::updateControlPoint(int index, const QPoint &pt) {
    if (index >= 0 && index < controlPoints.size())
        controlPoints[index] = pt;
}

QPoint Bezier::getControlPoint(int index) const {
    if (index < 0 || index >= controlPoints.size())
        return QPoint();
    return controlPoints.value(index);
}

void Bezier::clear() {
    controlPoints.clear();
    curvePoints.clear();
}

int Bezier::controlPointCount() const {
    return controlPoints.size();
}

void Bezier::calculateCurve(int numInterp) {
    curvePoints.clear();
    if (controlPoints.size() < 2) return;
    for (int i = 0; i <= numInterp; ++i) {
        double t = double(i) / numInterp;
        curvePoints.append(deCasteljau(t));
    }
}

QVector<QPointF> Bezier::getCurvePoints() const {
    return curvePoints;
}

void Bezier::drawControlPolygon(QPainter &painter) {
    if (controlPoints.size() < 2) return;
    painter.setPen(Qt::gray);
    for (int i = 0; i < controlPoints.size() - 1; ++i) {
        painter.drawLine(controlPoints[i], controlPoints[i + 1]);
    }
    painter.setPen(Qt::red);
    for (const QPoint &pt : controlPoints) {
        painter.drawEllipse(pt, 4, 4);
    }
}

void Bezier::drawCurve(QPainter &painter) {
    if (curvePoints.size() < 2) return;
    painter.setPen(Qt::blue);
    for (int i = 1; i < curvePoints.size(); ++i) {
        painter.drawLine(curvePoints[i - 1], curvePoints[i]);
    }
}

QPointF Bezier::deCasteljau(double t) const {
    QVector<QPointF> pts;
    for (const QPoint &pt : controlPoints)
        pts.append(QPointF(pt));
    int n = pts.size();
    for (int k = 1; k < n; ++k) {
        for (int i = 0; i < n - k; ++i) {
            pts[i] = (1 - t) * pts[i] + t * pts[i + 1];
        }
    }
    return pts[0];
}