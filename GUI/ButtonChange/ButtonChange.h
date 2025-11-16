#ifndef BUTTONCHANGE_H
#define BUTTONCHANGE_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonChange : public GUIFormBase
{
    Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonChange(LayersBase *Base ,QWidget *parent = 0);
	~ButtonChange();

	virtual void	Prepare(void)	override;

	void	SetChange(int PhaseCount,int PageCount,int LayerCount,int LineCount);
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdChangeCount : public GUICmdPacketBase
{
public:
	int		NewPhaseCount;
	int		NewLayerCount;
	int		NewLineCount;

	GUICmdChangeCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCHANGE_H
