#pragma once
#include <boost/polygon/voronoi.hpp>
#include <QDialog>
#include <QVector>
#include <QPointF>
#include <QPainterPath>

class Voronoi : public QDialog {
    Q_OBJECT
public:
    explicit Voronoi(QWidget *parent = nullptr);

    QVector<QPointF> getSeeds() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPointF> seeds;
    QVector<QPainterPath> regions;

    // Add this line:
    boost::polygon::voronoi_diagram<double> vd;

    void computeVoronoi();
};