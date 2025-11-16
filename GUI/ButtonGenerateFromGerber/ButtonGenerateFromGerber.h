#ifndef BUTTONGENERATEFROMGERBER_H
#define BUTTONGENERATEFROMGERBER_H

#include "buttongeneratefromgerber_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonGenerateFromGerber : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	int32	GenLibType;
	int32	GenLibID;
	int32	GenGerberLayerNo;
	int32	GerberAlgoType;
	int32	GenGerberLib;

public:
	ButtonGenerateFromGerber(LayersBase *Base ,QWidget *parent);
	~ButtonGenerateFromGerber();

	virtual void	Prepare(void)	override;

public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

class	GUICmdGenerate : public GUICmdPacketBase
{
public:
	GUICmdGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONGENERATEFROMGERBER_H
