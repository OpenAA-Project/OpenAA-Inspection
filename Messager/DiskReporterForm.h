#ifndef DISKREPORTERFORM_H
#define DISKREPORTERFORM_H

#include <QWidget>
#include "ui_DiskReporterForm.h"
#include "NList.h"
#include "XDateTime.h"
#include <QString>
#include "XFileRegistry.h"

class	DiskReportList:public NPList<DiskReportList>
{
public:
	XDateTime	FTime;
	QString		Tag;
	QString		Data;
};


class DiskReporterForm : public QWidget
{
	Q_OBJECT

	NPListPack<DiskReportList>	DiskReportData;
	FileRegistry	FRegistry;
public:
	DiskReporterForm(QWidget *parent = 0);
	~DiskReporterForm();

	void	SetList(QString Str);

private:
	Ui::DiskReporterFormClass ui;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
	void	ShowList(void);

};

#endif // DISKREPORTERFORM_H
