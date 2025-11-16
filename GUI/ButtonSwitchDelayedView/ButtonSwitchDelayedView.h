#ifndef BUTTONSWITCHDELAYEDVIEW_H
#define BUTTONSWITCHDELAYEDVIEW_H

#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	ButtonSwitchDelayedView : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	NormalColor;
	QColor	PushedColor;
	QFont	CFont;

	ButtonSwitchDelayedView(LayersBase *Base ,QWidget *parent);
	virtual void	Prepare(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

public slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdSendSwitchDelayedView : public GUICmdPacketBase
{
public:

	GUICmdSendSwitchDelayedView(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONSWITCHDELAYEDVIEW_H
