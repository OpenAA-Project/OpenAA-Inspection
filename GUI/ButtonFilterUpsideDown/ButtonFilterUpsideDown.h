#ifndef BUTTONFILTERUPSIDEDOWN_H
#define BUTTONFILTERUPSIDEDOWN_H

#include "buttonfilterupsidedown_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandBit;

class	ButtonFilterUpsideDown : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;
	int32	SystemRegisterNo;

	ButtonFilterUpsideDown(LayersBase *Base ,QWidget *parent);
	~ButtonFilterUpsideDown(void);
	
	virtual void	Prepare(void)	override;

private:
	SignalOperandBit	*ioMode;
private slots:
	void	SlotClicked();
	void	ResizeAction();
	void	OperandChanged();
};

class	GUICmdFilterUpsideDown : public GUICmdPacketBase
{
public:

	GUICmdFilterUpsideDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdFilterClearUpsideDown : public GUICmdPacketBase
{
public:

	GUICmdFilterClearUpsideDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // BUTTONFILTERUPSIDEDOWN_H
