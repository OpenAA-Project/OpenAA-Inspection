#ifndef INTEGRATIONUPDATEHISTORYLIST_H
#define INTEGRATIONUPDATEHISTORYLIST_H

#include "integrationupdatehistorylist_global.h"
#include "XGUIFormBase.h"
#include <QTranslator>
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"

class	IntegrationUpdateHistoryList: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	NormalColor;
	QColor	PushedColor;
	QFont	CFont;

	IntegrationUpdateHistoryList(LayersBase *Base ,QWidget *parent);

	virtual	void	Prepare(void)	override;
private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
	void	SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK);
};

#endif // INTEGRATIONUPDATEHISTORYLIST_H
