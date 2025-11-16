#pragma once

#include "buttonresetcamera_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XYCross.h"
#include <QString>
#include <QColor>
#include <QFont>

class BUTTONRESETCAMERA_EXPORT ButtonResetCamera : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
public:
	bool	RestartPC;


	ButtonResetCamera(LayersBase *Base ,QWidget *parent);
	~ButtonResetCamera(void);

	virtual	void	Prepare(void)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};
//--------------------------------------------------------------------------

class	GUICmdResetCamera : public GUICmdPacketBase
{
public:
	int		Cmd;
	bool	RestartPC;

	GUICmdResetCamera(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
