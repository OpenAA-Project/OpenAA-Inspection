#ifndef BUTTONSHRINKIMAGE_H
#define BUTTONSHRINKIMAGE_H

#include "buttonshrinkimage_global.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonShrinkImage : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonShrinkImage(LayersBase *Base ,QWidget *parent);
	~ButtonShrinkImage(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdReqShrinkImage : public GUICmdPacketBase
{
public:
	double	Rate;
	bool	ExeMaster;
	bool	ExeTarget;

	GUICmdReqShrinkImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONSHRINKIMAGE_H
