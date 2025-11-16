#ifndef BUTTONINITIALIZE_H
#define BUTTONINITIALIZE_H

#include "buttoninitialize_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandBit;

class	ButtonInitialize : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	SystemRegisterNo;

	ButtonInitialize(LayersBase *Base ,QWidget *parent);
	~ButtonInitialize(void);
	
	virtual void	Prepare(void)	override;

	void	CommandInitialize(void);
private:
	SignalOperandBit	*ioMode;
private slots:
	void	SlotClicked();
	void	ResizeAction();
};

class	GUICmdReqInitialize : public GUICmdPacketBase
{
public:

	GUICmdReqInitialize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONINITIALIZE_H
