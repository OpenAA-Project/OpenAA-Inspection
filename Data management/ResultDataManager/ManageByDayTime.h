#ifndef MANAGEBYDAYTIME_H
#define MANAGEBYDAYTIME_H

#include <QDialog>
#include "XResultDataManager.h"
#include "XServiceForLayers.h"
#include "NList.h"
#include "XMLClient.h"
#include "XDatabaseLoader.h"

namespace Ui {
    class ManageByDayTime;
}

class ManageByDayTime : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ResultDataManagerParam	*SParam;

	XMLServerHandle	*XMLServer;
	std::shared_ptr<DatabaseLoader>	SQLDatabase;
	RServerParam	ServerParam;

	QStringList		EnumResultList;

public:
    explicit ManageByDayTime(LayersBase *Base ,ResultDataManagerParam *Param ,QWidget *parent = 0);
    ~ManageByDayTime();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButtonExecuteDelete_clicked();

private:
    Ui::ManageByDayTime *ui;
};

#endif // MANAGEBYDAYTIME_H
