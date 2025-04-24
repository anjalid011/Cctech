#ifndef VORONOI_H
#define VORONOI_H

#include <QPointF>
#include <QVector>
#include <QPainter>

class Voronoi {
public:
    Voronoi();
    void draw(QPainter& painter);

private:
    QVector<QPointF> points;
};

#endif // VORONOI_H
