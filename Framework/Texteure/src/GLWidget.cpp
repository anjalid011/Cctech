#include "glwidget.h"
#include <QMatrix4x4>
#include <QImage>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <cmath>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), texture(nullptr) {}
GLWidget::~GLWidget() {
    makeCurrent();
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
    delete texture;
    delete texture2;
    delete texture3;
    delete skyboxTexture;
    doneCurrent();
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    initSphere(1.0f, 72, 36); // Initialize the first sphere
    setupShaders();

    texture = new QOpenGLTexture(QImage("../textures/sun.jfif").flipped(Qt::Vertical));
    texture2 = new QOpenGLTexture(QImage("../textures/earth.jpg").flipped(Qt::Vertical));
    texture3 = new QOpenGLTexture(QImage("../textures/moon.jfif").flipped(Qt::Vertical));

    view.lookAt(QVector3D(0, 0, 3), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

    // Initialize and start the animation timer
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, [this]() {
        revolutionAngle += 0.50f; // Earth around Sun
        moonRevolutionAngle += 1.5f; // Moon around Earth (faster)
        if (revolutionAngle >= 360.0f) revolutionAngle -= 360.0f;
        if (moonRevolutionAngle >= 360.0f) moonRevolutionAngle -= 360.0f;
        update();
    });
    animationTimer->start(16); // Update every 16ms (~60 FPS)

    // --- SKYBOX SETUP ---
    QStringList faces = {
        "../textures/right.png",
        "../textures/left.png",
        "../textures/top.png",
        "../textures/bottom.png",
        "../textures/front.png",
        "../textures/back.png"
    };
    skyboxTexture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    skyboxTexture->create();
    skyboxTexture->allocateStorage(QOpenGLTexture::RGBA, QOpenGLTexture::UInt8); // <-- ADD THIS LINE
    skyboxTexture->bind();
    for (int i = 0; i < 6; ++i) {
        QImage img(faces[i]);
        if (img.isNull()) qDebug() << "Failed to load" << faces[i];
        img = img.convertToFormat(QImage::Format_RGBA8888).mirrored();
        skyboxTexture->setData(0, 0, static_cast<QOpenGLTexture::CubeMapFace>(QOpenGLTexture::CubeMapPositiveX + i),
                               QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, img.constBits(), nullptr);
    }
    skyboxTexture->setWrapMode(QOpenGLTexture::ClampToEdge);
    skyboxTexture->setMinificationFilter(QOpenGLTexture::Linear);
    skyboxTexture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Skybox cube vertices (positions only)
    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    // Skybox shaders
    skyboxProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        out vec3 TexCoord;
        uniform mat4 view;
        uniform mat4 projection;
        void main() {
            TexCoord = aPos;
            vec4 pos = projection * view * vec4(aPos * 50.0, 1.0); // Large cube
            gl_Position = pos.xyww;
        }
    )");
    skyboxProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, R"(
        #version 330 core
        in vec3 TexCoord;
        out vec4 FragColor;
        uniform samplerCube skybox;
        void main() {
            FragColor = texture(skybox, TexCoord);
        }
    )");
    skyboxProgram.link();
}

void GLWidget::resizeGL(int w, int h) {
    projection.setToIdentity();
    projection.perspective(45.0f, float(w) / h, 0.1f, 100.0f);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw skybox first (disable depth write and culling)
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
    skyboxProgram.bind();
    QMatrix4x4 skyboxView = view;
    skyboxView.setColumn(3, QVector4D(0,0,0,skyboxView.column(3).w())); // Remove translation
    skyboxProgram.setUniformValue("view", skyboxView);
    skyboxProgram.setUniformValue("projection", projection);
    skyboxTexture->bind(0);
    skyboxProgram.setUniformValue("skybox", 0);
    glBindVertexArray(skyboxVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    skyboxProgram.release();
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);

    program.bind();
    texture->bind();

    // Render the first sphere (Sun)
    QMatrix4x4 model1;
    model1.translate(translationOffset);
    model1.rotate(rotationX, 1.0f, 0.0f, 0.0f);
    model1.rotate(rotationY, 0.0f, 1.0f, 0.0f);
    model1.scale(1.0f + zoom * 0.1f);

    program.setUniformValue("model", model1);
    program.setUniformValue("view", view);
    program.setUniformValue("projection", projection);
    program.setUniformValue("lightDir", QVector3D(0.0f, 0.0f, -3.0f));
    program.setUniformValue("lightColor", QVector3D(1.0f, 1.0f, 1.0f));
    program.setUniformValue("viewPos", QVector3D(0, 0, 3));

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

    // Render the second sphere (Earth)
    texture2->bind();
    QMatrix4x4 model2;
    model2.translate(translationOffset);
    model2.rotate(revolutionAngle, 0.0f, 1.0f, 0.0f);
    model2.translate(1.5f, 0.0f, 0.0f);
    model2.scale(0.5f + zoom * 0.05f);

    program.setUniformValue("model", model2);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

    // Render the moon
    texture3->bind();
    QMatrix4x4 model3;
    model3.translate(translationOffset);
    model3.rotate(revolutionAngle, 0.0f, 1.0f, 0.0f);
    model3.translate(2.0f, 0.0f, 0.0f);

    QMatrix4x4 moonModel = model3;
    moonModel.rotate(moonRevolutionAngle, 0.0f, 1.0f, 0.0f);
    moonModel.translate(1.0f, 0.0f, 0.0f);
    moonModel.scale(0.1f);

    program.setUniformValue("model", moonModel);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    program.release();
}

void GLWidget::initSphere(float radius, int sectors, int stacks) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = M_PI / 2 - i * M_PI / stacks;
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j) {
            float sectorAngle = j * 2 * M_PI / sectors;

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);
            float s = (float)j / sectors;
            float t = (float)i / stacks;

            // Vertex: position, normal, texcoord
            vertices.insert(vertices.end(), {x, y, z, x, y, z, s, t});
        }
    }

    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.insert(indices.end(), {static_cast<unsigned int>(k1), static_cast<unsigned int>(k2), static_cast<unsigned int>(k1 + 1)});
            }
            if (i != (stacks - 1)) {
                indices.insert(indices.end(), {static_cast<unsigned int>(k1 + 1), static_cast<unsigned int>(k2), static_cast<unsigned int>(k2 + 1)});
            }
        }
    }

    indexCount = indices.size();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    int stride = 8 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);          // position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float))); // normal
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float))); // texcoord

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void GLWidget::setupShaders() {
    program.addShaderFromSourceCode(QOpenGLShader::Vertex, R"(#version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec3 aNormal;
    layout(location = 2) in vec2 aTex;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    out vec3 FragPos;
    out vec3 Normal;
    out vec2 TexCoord;

    void main() {
        FragPos = vec3(model * vec4(aPos, 1.0));
        Normal = mat3(transpose(inverse(model))) * aNormal;
        TexCoord = aTex;
        gl_Position = projection * view * vec4(FragPos, 1.0);
    })");

    program.addShaderFromSourceCode(QOpenGLShader::Fragment, R"(#version 330 core
    in vec3 FragPos;
    in vec3 Normal;
    in vec2 TexCoord;

    uniform sampler2D texture1;
    uniform vec3 lightDir;
    uniform vec3 lightColor;
    uniform vec3 viewPos;

    out vec4 FragColor;

    void main() {
        vec3 norm = normalize(Normal);
        vec3 light = normalize(-lightDir);
        float diff = max(dot(norm, light), 0.0);

        vec3 color = texture(texture1, TexCoord).rgb;
        vec3 ambient = 0.2 * color;
        vec3 diffuse = diff * color * lightColor;

        FragColor = vec4(ambient + diffuse, 1.0);
    })");

    program.link();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    lastMousePos = event->pos(); // Store the last mouse position
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // Rotate the scene
        float dx = event->pos().x() - lastMousePos.x();
        float dy = event->pos().y() - lastMousePos.y();

        rotationX += dy * 0.5f; // Adjust sensitivity as needed
        rotationY += dx * 0.5f; // Adjust sensitivity as needed
    } else if (event->buttons() & Qt::MiddleButton) {
        // Translate the scene
        float dx = (event->pos().x() - lastMousePos.x()) / width();
        float dy = (event->pos().y() - lastMousePos.y()) / height();

        translationOffset += QVector3D(dx * 10.0f, -dy * 10.0f, 0.0f); // Scale translation
    }

    lastMousePos = event->pos(); // Update the last mouse position
    update(); // Request re-render
}

void GLWidget::wheelEvent(QWheelEvent *event) {
    float delta = event->angleDelta().y() / 120.0f; // Each wheel step is 120 units
    zoom += delta * 0.5f; // Adjust zoom sensitivity
    update(); // Request re-render
}