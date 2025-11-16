#pragma once

#include "splitter_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QSplitter>

class Splitter :public GUIFormBase
{
	Q_OBJECT

	QSplitter	SplitterInst;
	bool		FirstMode;
	GUIFormBase	*Child1;
	GUIFormBase	*Child2;
public:
	QString		Direction;
	QString		ChildInst1;
	QString		ChildInst2;

	Splitter(LayersBase *Base ,QWidget *parent = 0);

	virtual void	ReadyParam(void)override;

private:
private slots:
	void	ResizeAction();
};

