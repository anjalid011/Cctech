#include "Voronoi.h"
#include <boost/polygon/voronoi.hpp>
#include <QPainter>
#include <QMouseEvent>
#include <vector>
#include <random>
#include <QPainterPath>

using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;

struct Point {
    int x, y;
};

namespace boost { namespace polygon {
    template <>
    struct geometry_concept<Point> { typedef point_concept type; };
    template <>
    struct point_traits<Point> {
        typedef int coordinate_type;
        static inline coordinate_type get(const Point& p, orientation_2d o) {
            return (o == HORIZONTAL) ? p.x : p.y;
        }
    };
}}

Voronoi::Voronoi(QWidget *parent) : QDialog(parent) {
    setFixedSize(400, 400);
}

QVector<QPointF> Voronoi::getSeeds() const {
    return seeds;
}

void Voronoi::mousePressEvent(QMouseEvent *event) {
    seeds.append(event->pos());
    computeVoronoi();
    update();
}

void Voronoi::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    
    // Draw Voronoi edges
    painter.setPen(QPen(Qt::black, 1));
    for (const auto& cell : vd.cells()) {
        const auto* edge = cell.incident_edge();
        if (!edge) continue;
        const auto* start = edge;
        do {
            if (edge->is_finite()) {
                auto v0 = edge->vertex0();
                auto v1 = edge->vertex1();
                painter.drawLine(QPointF(v0->x(), v0->y()), QPointF(v1->x(), v1->y()));
            }
            edge = edge->next();
        } while (edge != start);
    }

    // Draw Voronoi regions
    // std::mt19937 rng(42);
    // std::uniform_int_distribution<int> dist(0, 255);
    // for (const QPainterPath &region : regions) {
    //     QColor color(dist(rng), dist(rng), dist(rng));
    //     painter.setBrush(color);
    //     painter.setPen(Qt::NoPen);
    //     painter.drawPath(region);
    // }

    // Draw seeds
    painter.setBrush(Qt::red);
    painter.setPen(Qt::black);
    for (const QPointF &pt : seeds)
        painter.drawEllipse(pt, 4, 4);
}

void Voronoi::computeVoronoi() {
    regions.clear();

    if (seeds.size() < 2)
        return;

    // Convert seeds to Boost points
    std::vector<Point> boostSeeds;
    for (const QPointF& pt : seeds)
        boostSeeds.push_back(Point{static_cast<int>(pt.x()), static_cast<int>(pt.y())});

    // Compute Voronoi diagram
    voronoi_diagram<double> vd;
    construct_voronoi(boostSeeds.begin(), boostSeeds.end(), &vd);

    // For each cell, build a QPainterPath for the region
    for (auto it = vd.cells().begin(); it != vd.cells().end(); ++it) {
        const voronoi_diagram<double>::cell_type& cell = *it;
        const voronoi_diagram<double>::edge_type* edge = cell.incident_edge();
        if (!edge) continue;

        QPainterPath path;
        std::vector<QPointF> polygon;

        const voronoi_diagram<double>::edge_type* start = edge;
        do {
            if (edge->is_finite()) {
                auto v0 = edge->vertex0();
                polygon.push_back(QPointF(v0->x(), v0->y()));
            }
            edge = edge->next();
        } while (edge != start);

        if (!polygon.empty()) {
            path.moveTo(polygon[0]);
            for (size_t i = 1; i < polygon.size(); ++i)
                path.lineTo(polygon[i]);
            path.closeSubpath();
            regions.push_back(path);
        }
    }
}