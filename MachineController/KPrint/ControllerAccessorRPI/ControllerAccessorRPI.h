#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ControllerAccessorRPI.h"

class ControllerAccessorRPI : public QMainWindow
{
    Q_OBJECT

public:
    ControllerAccessorRPI(QWidget *parent = Q_NULLPTR);

private slots:
    void on_pushButtonSend_clicked();

private:
    Ui::ControllerAccessorRPIClass ui;
};
