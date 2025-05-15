#pragma once
#include <QMainWindow>
#include "ExtWidget.h"

class ExtrusionWindow : public QMainWindow {
    Q_OBJECT

public:
    ExtrusionWindow(QWidget* parent = nullptr);
    virtual ~ExtrusionWindow();
};
