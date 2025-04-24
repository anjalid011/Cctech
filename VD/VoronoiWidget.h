#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector2D>
#include <vector>

class VoronoiWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit VoronoiWidget(QWidget* parent = nullptr);
    void setSites(const std::vector<QVector2D>& newSites);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    std::vector<QVector2D> sites;
    std::vector<std::pair<QVector2D, QVector2D>> edges;
    void computeVoronoi();
};
