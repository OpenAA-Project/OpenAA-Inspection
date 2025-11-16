#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WorldServer.h"
#include "XRegulusWorld.h"


class WorldServer : public QMainWindow
{
    Q_OBJECT

    RegulusWorld    *WorldBase;
public:
    WorldServer(QWidget *parent = nullptr);
    ~WorldServer();

private:
    Ui::WorldServerClass ui;
};
