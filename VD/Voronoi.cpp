#include "Voronoi.h"
#include <QtGui/QPainter>

Voronoi::Voronoi() {
    // Example seed points (you can randomize this or take user input)
    points.push_back(QPointF(100, 100));
    points.push_back(QPointF(300, 200));
    points.push_back(QPointF(200, 400));
}

void Voronoi::draw(QPainter& painter) {
    painter.setPen(Qt::black);
    for (const QPointF& point : points) {
        painter.drawEllipse(point, 4, 4);
    }

    painter.setPen(Qt::blue);
    // Fake Voronoi edges (for display only, not accurate)
    painter.drawLine(points[0], (points[1] + points[2]) / 2);
    painter.drawLine(points[1], (points[0] + points[2]) / 2);
    painter.drawLine(points[2], (points[0] + points[1]) / 2);
}
