#pragma once

#include "buttonshadowtoshow_global.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"

class ShadowButton : public QToolButton
{
	Q_OBJECT
public:
	int	Number;

	ShadowButton(int n);
	~ShadowButton();

signals:
	void	SignalClicked(int ButtonNumber);
private slots:
	void SlotClicked (bool checked);
};


class  ButtonShadowToShow: public GUIFormBase
{
	Q_OBJECT

	ShadowButton	**ButtonDim;
	int				AllocatedButtonCount;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonShadowToShow(LayersBase *Base ,QWidget *parent);
	~ButtonShadowToShow(void);

	virtual	void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit	(void)	override;
private slots:
	void SlotClicked (int ButtonNumber);
	void	ResizeAction();

private:
	void	ShowButtons(void);
};

class	GUICmdSetCurrentShadow: public GUICmdPacketBase
{
public:
	int	Shadow;

	GUICmdSetCurrentShadow(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};