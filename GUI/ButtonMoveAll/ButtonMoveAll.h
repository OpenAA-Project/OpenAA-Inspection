#ifndef BUTTONMOVEALL_H
#define BUTTONMOVEALL_H

#include "buttonmoveall_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"

class	ButtonMoveAll : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonMoveAll(LayersBase *Base ,QWidget *parent);
	~ButtonMoveAll(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;
	
	void	ExecuteMove(IntList &AppliedPages,bool MoveMasterImage ,bool MoveTargetImage ,int Dx,int Dy);

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

class	GUICmdMoveAll: public GUICmdPacketBase
{
public:
	int	MovX;
	int	MovY;
	bool	MoveMasterImage;
	bool	MoveTargetImage;

	GUICmdMoveAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // BUTTONMOVEALL_H
