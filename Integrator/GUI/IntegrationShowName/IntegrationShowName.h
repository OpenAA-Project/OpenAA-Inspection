#ifndef INTEGRATIONSHOWNAME_H
#define INTEGRATIONSHOWNAME_H

#include "integrationshowname_global.h"
#include "XGUIFormBase.h"
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

class	IntegrationShowName : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	QLabel	LabelTitleNumber;
	QLabel	LabelTitleName	;
	QLabel	LabelTitleRemark;
	QLabel	LabelDataNumber	;
	QLabel	LabelDataName	;
	QLabel	LabelDataRemark	;
public:
	QFont	TitleFont;
	QFont	CharFont;
	QString	TitleMasterNumber;
	QString	TitleMasterName;
	QString	TitleRemark;
	QColor	TitleColor;

	IntegrationShowName(LayersBase *Base ,QWidget *parent = 0);
	~IntegrationShowName();

	virtual void	Prepare(void)	override;
private:
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

private slots:
	void	ResizeAction();
};

class	CmdShowNameInfo : public SpecifiedBroadcaster
{
public:
	QString	MasterNumber;
	QString	MasterName;
	QString	Remark;
};

#endif // INTEGRATIONSHOWNAME_H
