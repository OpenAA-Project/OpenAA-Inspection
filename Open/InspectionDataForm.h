#ifndef INSPECTIONDATAFORM_H
#define INSPECTIONDATAFORM_H

#include <QDialog>
#include <QTimer>
#include "ui_InspectionDataForm.h"

class InspectionDataForm : public QDialog
{
	Q_OBJECT

public:
	InspectionDataForm();
	~InspectionDataForm();

	void SetDialog(int Type,QList<QByteArray> *XMLFData,QList<QByteArray> *XMLBData,int MCount,int Flg);

	void			   SetRetXMLDataList(int Type,QList<QByteArray> *XMLData)	{	XMLDataList[Type]=*XMLData;	}
	QList<QByteArray> *GetRetXMLDataList(int Type)								{	return &XMLDataList[Type];	}

protected:
	virtual	void closeEvent(QCloseEvent *event)	override;

private slots:
	void pbEnterClicked();
	void update();

private:
	Ui::InspectionDataFormClass ui;

	QList<QByteArray>	XMLDataList[2];

	QTimer *timer;
	QPalette PaletteDefault;
	QPalette PaletteAlarm[2];
	char	Index;
};

#endif // INSPECTIONDATAFORM_H
