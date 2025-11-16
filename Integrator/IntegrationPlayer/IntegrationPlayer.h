#ifndef INTEGRATIONPLAYER_H
#define INTEGRATIONPLAYER_H

#include <QMainWindow>
#include "ui_IntegrationPlayer.h"

class IntegrationPlayer : public QMainWindow
{
	Q_OBJECT

public:
	IntegrationPlayer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~IntegrationPlayer();

private:
	Ui::IntegrationPlayerClass ui;
};

#endif // INTEGRATIONPLAYER_H
