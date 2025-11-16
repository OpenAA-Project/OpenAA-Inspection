#ifndef INTEGRATIONSHOWRELATIONINFOFORM_H
#define INTEGRATIONSHOWRELATIONINFOFORM_H

#include "XGUIFormBase.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"

namespace Ui {
class IntegrationShowRelationInfoForm;
}

class IntegrationShowRelationInfoForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

public:
	QFont	TitleFont;
	QFont	DataFont;
	bool	ShowMasterID;
	bool	ShowMasterName;
	bool	ShowLotName;
	bool	ShowWorkerID;
	bool	ShowWorkerName;

	QString	TitleMasterID;
	QString	TitleMasterName;
	QString	TitleLotName;
	QString	TitleWorkerID;
	QString	TitleWorkerName;

    IntegrationShowRelationInfoForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationShowRelationInfoForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
private:
    Ui::IntegrationShowRelationInfoForm *ui;

private slots:
	void	ResizeAction();
};


#endif // INTEGRATIONSHOWRELATIONINFOFORM_H
