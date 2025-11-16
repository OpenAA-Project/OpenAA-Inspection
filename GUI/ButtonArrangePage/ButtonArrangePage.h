#ifndef BUTTONARRANGEPAGE_H
#define BUTTONARRANGEPAGE_H

#include "buttonarrangepage_global.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandBit;

class	ButtonArrangePage : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	ArrangeMethod;

	ButtonArrangePage(LayersBase *Base ,QWidget *parent);
	~ButtonArrangePage(void);
	
	virtual void	Prepare(void)	override;

private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
};

class	GUICmdReqArrangePage : public GUICmdPacketBase
{
public:
	QString	ArrangeMethod;

	GUICmdReqArrangePage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONARRANGEPAGE_H
