#pragma once

#include "buttoncalibratecamera_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonCalibrateCamera : public GUIFormBase
{
    Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	Mastered;

	ButtonCalibrateCamera(LayersBase *Base ,QWidget *parent = 0);
	~ButtonCalibrateCamera();

	virtual void	Prepare(void)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};
class	GUICmdCalibrateCamera: public GUICmdPacketBase
{
public:
	GUICmdCalibrateCamera(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override	{	return true;	}
	virtual	bool	Save(QIODevice *f)	override	{	return true;	}

	virtual	void	Receive(int32 LocalPage,int cmd,QString &EmitterRoot,QString &EmitterName)	override;
};
