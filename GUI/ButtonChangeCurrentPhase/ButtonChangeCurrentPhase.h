#ifndef BUTTONCHANGECURRENTPHASE_H
#define BUTTONCHANGECURRENTPHASE_H

//#include "buttonchangecurrentphase_global.h"
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "mtToolButtonColored.h"


#define	MaxButtonPhaseNumb	100

class ButtonChangeCurrentPhase : public GUIFormBase
{
	Q_OBJECT

	int	IconSizeW;
	int	IconSizeH;
public:
	QStringList	PhaseTitles;
	QFont		ButtonFont;
	QColor		UncheckedColor;
	QColor		ActiveColor;
	int32		CurrentPhase;
	bool		UsePhaseName;
	QString		OrientationStr;		//Horizontal,Vertical

	mtToolButtonColored	*Buttons[MaxButtonPhaseNumb];

	ButtonChangeCurrentPhase(LayersBase *Base ,QWidget *parent);
	~ButtonChangeCurrentPhase(void);

	virtual void	Prepare(void)	override;
	void	Release(void);
	virtual void	ShowInEdit	(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)override;
private:
	void	ShowButtons(void);
private slots:
	void	ResizeAction();
	void	SlotButtonDown(bool);
	void	SlotChangedPhasePageLayer();
	void	SlotChangeCurrentPhase();
};

class	GUICmdChangeCurrentPhase : public GUICmdPacketBase
{
public:
	int	NewPhase;

	GUICmdChangeCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCHANGECURRENTPHASE_H
