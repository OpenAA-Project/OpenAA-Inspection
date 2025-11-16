#pragma once

#include "setalignmentlargeheadline_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	AlignmentLargeBase;

class	SetAlignmentLargeHeadLine : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	SetAlignmentLargeHeadLine(LayersBase *Base ,QWidget *parent);
	~SetAlignmentLargeHeadLine(void);
	virtual void	Prepare(void)	override;

private:
	AlignmentLargeBase	*GetAlignmentLargeBase(void);
private slots:
	void	SlotClicked();
	void	ResizeAction();
};

class	GUICmdSetAlignmentLargeHeadLine : public GUICmdPacketBase
{
public:
	bool		UseHeadAlignment		;
	int			MaxHeadAlignmentX		;
	int			MaxHeadAlignmentY		;
	int			SkipHeadAlignmentX		;
	int			SkipHeadAlignmentY		;
	int			HeadAlignmentDifColor	;
	int			HeadAlignmentMinSize	;
	int			HeadAlignmentStep		;

	GUICmdSetAlignmentLargeHeadLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
