#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RobotRegulusWorld.h"
#include "XRegulusWorld.h"
#include <QSplitter>

class RobotRegulusWorld : public QMainWindow
{
    Q_OBJECT

    RegulusWorld    *WorldBase;
	QSplitter			*SplitterH;
	QSplitter			*SplitterV;
public:
    RobotRegulusWorld(QWidget *parent = nullptr);
    ~RobotRegulusWorld();

private slots:
    void on_toolButtonExecute_clicked();

    void on_toolButtonOrigin_clicked();

private:
    Ui::RobotRegulusWorldClass ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};
