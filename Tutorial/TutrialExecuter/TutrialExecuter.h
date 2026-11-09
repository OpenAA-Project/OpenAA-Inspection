#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TutrialExecuter.h"

class TutrialExecuter : public QMainWindow
{
    Q_OBJECT

public:
    TutrialExecuter(QWidget *parent = nullptr);
    ~TutrialExecuter();

private slots:
    void onBrowseConfigDir();
    void onStart();

private:
    Ui::TutrialExecuterClass ui;

    void populateGuiFiles();
    void initDefaultConfigDir();
};
