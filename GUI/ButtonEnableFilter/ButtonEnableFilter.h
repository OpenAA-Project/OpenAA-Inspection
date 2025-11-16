#pragma once

#include "buttonenablefilter_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIFormBase.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>

class	ButtonEnableFilter : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;


	ButtonEnableFilter(LayersBase *Base ,QWidget *parent);
	~ButtonEnableFilter(void);
	virtual void	Prepare(void)	override;

public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

//============================================================================================

class	GUICmdEnableFilter : public GUICmdPacketBase
{
public:
	bool	EnableFilter;

	GUICmdEnableFilter(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
