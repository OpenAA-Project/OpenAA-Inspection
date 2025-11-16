#ifndef AUTOSTARTEACHPARAM_H
#define AUTOSTARTEACHPARAM_H

#include <QDialog>
#include "ui_AutoStartEachParam.h"
#include "XTypeDef.h"

class AutoStartEachParam : public QDialog
{
	Q_OBJECT

public:
	AutoStartEachParam(const QString &_ExeFilePath,const QString &_Parameters,const QString &_WorkingPath,int32	_Location ,int32 _BootingWaitTime
						,QWidget *parent = 0);
	~AutoStartEachParam();

	QString	ExeFilePath;
	QString	Parameters;
	QString	WorkingPath;
	int32	Location;
	int32	BootingWaitTime;

private:
	Ui::AutoStartEachParamClass ui;

private slots:
	void on_pushButtonFile_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // AUTOSTARTEACHPARAM_H
