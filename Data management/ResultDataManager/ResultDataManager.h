#ifndef RESULTDATAMANAGER_H
#define RESULTDATAMANAGER_H

#include <QMainWindow>
#include "ui_ResultDataManager.h"
#include "XResultDataManager.h"
#include "XMLClient.h"
#include "DeleteThread.h"
#include "XServiceForLayers.h"

class	LocalDatabaseBasicClass;

class ResultDataManager : public QMainWindow ,public ServiceForLayers
{
	Q_OBJECT

	QStringList	EnumResultList;
	ResultDataManagerParam	RParam;

	LocalDatabaseBasicClass	*KDatabase;

public:
	ResultDataManager(LayersBase *base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ResultDataManager();

	bool	ConnectXML(void);
	bool	ConnectDatabase(void);

private slots:
        void on_pushButtonByLot_clicked();

        void on_pushButtonByDayTime_clicked();

        void on_pushButtonSetting_clicked();

        void on_pushButtonClose_clicked();

private:
	Ui::ResultDataManagerClass ui;
};

#endif // RESULTDATAMANAGER_H
