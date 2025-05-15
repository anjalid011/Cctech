#pragma once
#include <QMainWindow>
#include "IntersectionWidget.h"
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>

class IntersectionWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit IntersectionWindow(QWidget* parent = nullptr);

private slots:
    void addShape();
    void deleteShape();
    // void performIntersection();
    // void performUnion();
    // void performSubtraction();

private:
    IntersectionWidget* m_intersectionWidget;
    QComboBox* m_shapeSelector;
    QListWidget* m_shapeList;
    QPushButton* m_addShapeButton;
    QPushButton* m_deleteShapeButton;
    QPushButton* m_intersectionButton;
    QPushButton* m_unionButton;
    QPushButton* m_subtractionButton;

    // Input fields for shape parameters
    QLineEdit* m_param1;
    QLineEdit* m_param2;
    QLineEdit* m_param3;
    QLineEdit* m_param4;
};