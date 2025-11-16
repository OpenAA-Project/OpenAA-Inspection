#ifndef SHOWINSPECTIONNUMBERFROM_H
#define SHOWINSPECTIONNUMBERFROM_H

#include "XGUIFormBase.h"
#include "ui_ShowInspectionNumberFrom.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowInspectionNumberFrom : public GUIFormBase
{
	Q_OBJECT

public:
	QString	TitleMessage;

	ShowInspectionNumberFrom(LayersBase *Base ,QWidget *parent = 0);
	~ShowInspectionNumberFrom();

	virtual	void	Prepare(void)			override;
	virtual	void	ShowInPlayer(int64 N)	override;

private:
	Ui::ShowInspectionNumberFromClass ui;
};

#endif // SHOWINSPECTIONNUMBERFROM_H
