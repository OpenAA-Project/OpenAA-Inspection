#ifndef BUTTONRESETTHRESHOLDDOTCOLORMATCHING_H
#define BUTTONRESETTHRESHOLDDOTCOLORMATCHING_H

#include "buttonresetthresholddotcolormatching_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonResetThresholdDotColorMatching : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

public:
	ButtonResetThresholdDotColorMatching(LayersBase *Base ,QWidget *parent);
	~ButtonResetThresholdDotColorMatching();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

class	GUICmdResetThresholdDotColorMatching : public GUICmdPacketBase
{
public:
	GUICmdResetThresholdDotColorMatching(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONRESETTHRESHOLDDOTCOLORMATCHING_H
