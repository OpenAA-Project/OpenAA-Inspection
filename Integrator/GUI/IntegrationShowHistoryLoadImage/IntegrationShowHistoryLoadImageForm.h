#ifndef INTEGRATIONSHOWHISTORYLOADIMAGEFORM_H
#define INTEGRATIONSHOWHISTORYLOADIMAGEFORM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

namespace Ui {
class IntegrationShowHistoryLoadImageForm;
}

class	InspectionLine : public NPList<InspectionLine>
{
public:
	InspectionList	*InspectionPointer[100];
	int				ID;

	InspectionLine(void);

	XDateTime	GetTime(void);
	bool	IsAllOK(void);
};


class IntegrationShowHistoryLoadImageForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	QLabel	*FileNameLabel[100];	
	ImageBuffer	*Image[100];

	NPListPack<InspectionLine>	Inspections;
	int		labelFileNameS0Height;
public:
	bool	DefaultNGOnly;

    explicit IntegrationShowHistoryLoadImageForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationShowHistoryLoadImageForm();

	virtual void	Prepare(void)		override;
	virtual void	StartLot(void)		override;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
	void	ResizeAction();
    void on_toolButtonOnlyNG_clicked();

private:
    Ui::IntegrationShowHistoryLoadImageForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
};

#endif // INTEGRATIONSHOWHISTORYLOADIMAGEFORM_H
