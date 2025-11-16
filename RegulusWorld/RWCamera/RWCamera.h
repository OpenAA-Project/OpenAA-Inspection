#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RWCamera.h"

class RWCamera : public QMainWindow
{
    Q_OBJECT

public:
    RWCamera(QWidget *parent = nullptr);
    ~RWCamera();

private:
    Ui::RWCameraClass ui;
};
