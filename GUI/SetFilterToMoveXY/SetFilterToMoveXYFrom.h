#ifndef SETFILTERTOMOVEXYFROM_H
#define SETFILTERTOMOVEXYFROM_H

#include "XGUIFormBase.h"
#include <QPushButton>

namespace Ui {
class SetFilterToMoveXYFrom;
}
class	MoveXYDialog;

class SetFilterToMoveXYFrom : public GUIFormBase
{
    Q_OBJECT

	MoveXYDialog	*D;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;

    explicit SetFilterToMoveXYFrom(LayersBase *Base ,QWidget *parent = 0);
    ~SetFilterToMoveXYFrom();

	virtual	void	Prepare(void)	override;

private slots:
    void on_pushButtonSetShftFilter_clicked();
	void	ResizeAction();

private:
    Ui::SetFilterToMoveXYFrom *ui;
};

class	GUICmdReqShiftMove : public GUICmdPacketBase
{
public:

	GUICmdReqShiftMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckShiftMove : public GUICmdPacketBase
{
public:
	int		MovX,MovY;

	GUICmdAckShiftMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetShiftMove : public GUICmdPacketBase
{
public:
	int		MovX,MovY;

	GUICmdSetShiftMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SETFILTERTOMOVEXYFROM_H
