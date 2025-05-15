#ifndef SKETCHWINDOW_H
#define SKETCHWINDOW_H

#include <QMainWindow>

class SketchGLWidget;
class QPushButton;

class SketchWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit SketchWindow(QWidget* parent = nullptr);

private slots:
    void onFinishShape();
    void onUnion();
    void onIntersection();
    void onSubtraction();
    void toggleDrawingMode();

private:
    void updateButtonVisibility(); // New method to update button visibility

    SketchGLWidget* sketchGLWidget;
    bool isDrawingBezier = false;

    QPushButton* toggleModeBtn;
    QPushButton* finishShapeBtn;
    QPushButton* unionBtn;
    QPushButton* intersectBtn;
    QPushButton* subtractBtn;
    QPushButton* clearResultBtn;
};

#endif // SKETCHWINDOW_H
