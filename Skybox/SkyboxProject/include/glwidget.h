#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private slots:
    void updateScene();

private:
    QTimer timer;
    float angleEarth, angleMoon;
    GLuint backgroundTexture, sunTexture, earthTexture, moonTexture;

    void drawSphere(float radius, int lats, int longs, GLuint texture);
    void drawSkybox();
    GLuint loadTexture(const QString &fileName);
};