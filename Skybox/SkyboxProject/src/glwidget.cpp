#include "glwidget.h"
#include <QOpenGLTexture>
#include <QImage>
#include <QMatrix4x4>
#include <QtMath>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), angleEarth(0.0f), angleMoon(0.0f)
{
    connect(&timer, &QTimer::timeout, this, &GLWidget::updateScene);
    timer.start(16); // ~60 FPS
}

GLWidget::~GLWidget() {}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    backgroundTexture = loadTexture("textures/background.png");
    sunTexture = loadTexture("textures/sun.jfif");
    earthTexture = loadTexture("textures/earth.jpg");
    moonTexture = loadTexture("textures/moon.jfif");
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Manual perspective matrix (similar to gluPerspective)
    float aspect = float(w) / float(h ? h : 1);
    float fovy = 45.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;
    float fH = tan(fovy / 360.0f * M_PI) * zNear;
    float fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -10);

    drawSkybox();

    // Draw Sun
    glPushMatrix();
    drawSphere(1.0f, 40, 40, sunTexture);
    glPopMatrix();

    // Draw Earth
    glPushMatrix();
    glRotatef(angleEarth, 0, 1, 0);
    glTranslatef(3.0f, 0, 0);
    drawSphere(0.5f, 30, 30, earthTexture);

    // Draw Moon
    glRotatef(angleMoon, 0, 1, 0);
    glTranslatef(1.0f, 0, 0);
    drawSphere(0.2f, 20, 20, moonTexture);
    glPopMatrix();
}

void GLWidget::updateScene() {
    angleEarth += 1.0f;
    if (angleEarth > 360.0f) angleEarth -= 360.0f;
    angleMoon += 2.0f;
    if (angleMoon > 360.0f) angleMoon -= 360.0f;
    update();
}

GLuint GLWidget::loadTexture(const QString &fileName) {
    QImage img(fileName);
    if (img.isNull()) return 0;
    img = img.convertToFormat(QImage::Format_RGBA8888);
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tex;
}

void GLWidget::drawSphere(float radius, int lats, int longs, GLuint texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
    for (int i = 0; i <= lats; ++i) {
        float lat0 = M_PI * (-0.5 + float(i - 1) / lats);
        float z0  = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = M_PI * (-0.5 + float(i) / lats);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= longs; ++j) {
            float lng = 2 * M_PI * float(j - 1) / longs;
            float x = cos(lng);
            float y = sin(lng);

            glTexCoord2f(float(j - 1) / longs, float(i - 1) / lats);
            glVertex3f(radius * x * zr0, radius * y * zr0, radius * z0);
            glTexCoord2f(float(j - 1) / longs, float(i) / lats);
            glVertex3f(radius * x * zr1, radius * y * zr1, radius * z1);
        }
        glEnd();
    }
}

void GLWidget::drawSkybox() {
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-10, -10, -9);
    glTexCoord2f(1, 0); glVertex3f( 10, -10, -9);
    glTexCoord2f(1, 1); glVertex3f( 10,  10, -9);
    glTexCoord2f(0, 1); glVertex3f(-10,  10, -9);
    glEnd();
    glEnable(GL_DEPTH_TEST);
}