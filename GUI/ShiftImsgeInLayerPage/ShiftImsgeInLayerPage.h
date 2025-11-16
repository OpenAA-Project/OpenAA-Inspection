#pragma once

#include "shiftimsgeinlayerpage_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>

class	ShiftImsgeInLayerPage : public GUIFormBase
{
    Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ShiftImsgeInLayerPage(LayersBase *Base ,QWidget *parent = 0);
	~ShiftImsgeInLayerPage();

	virtual void	Prepare(void)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdShiftImsge : public GUICmdPacketBase
{
public:
	int		Phase;
    IntList SelectedLayers;
    bool    ShiftMaster;
    bool    ShiftTarget;
    int     ShiftDx;
    int     ShiftDy;

	GUICmdShiftImsge(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
