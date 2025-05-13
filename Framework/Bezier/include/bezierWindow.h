#pragma once

#include <QMainWindow>
#include "BezierWidget.h"

class BezierWindow : public QMainWindow {
    Q_OBJECT

public:
    BezierWindow(QWidget *parent = nullptr);
    ~BezierWindow();
};