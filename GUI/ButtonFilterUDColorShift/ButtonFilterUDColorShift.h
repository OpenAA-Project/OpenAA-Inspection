#ifndef BUTTONFILTERUDCOLORSHIFT_H
#define BUTTONFILTERUDCOLORSHIFT_H

#include "buttonfilterudcolorshift_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XDateTime.h"

class	SignalOperandBit;
class	SignalOperandInt;

class	ButtonFilterUDColorShift : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	SyncMode;
	int		VShift;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;
	int32	SystemRegisterNo;
	int32	SystemRegisterIntNo;

	ButtonFilterUDColorShift(LayersBase *Base ,QWidget *parent);
	~ButtonFilterUDColorShift(void);
	
	virtual void	Prepare(void)			override;
	virtual	void	RxSync(QByteArray &f)	override;
	void	SetButtonColor(bool mode);
private:
	SignalOperandBit	*ioMode;
	SignalOperandInt	*ioShift;
	SignalOperandBit	*ioEveryTime;

	void	SendClicked(int	VShift);

private slots:
	void	SlotClicked();
	void	ResizeAction();
	void	OperandChanged();
	void	OperandChangedShift();
	void	ioEveryTimeOperandChanged();
};

class	GUICmdFilterUDColorShift : public GUICmdPacketBase
{
public:
	XDateTime	MasterTime;
	int		VShift;
	GUICmdFilterUDColorShift(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdFilterClearUDColorShift : public GUICmdPacketBase
{
public:
	XDateTime	MasterTime;
	int		VShift;

	GUICmdFilterClearUDColorShift(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdFilterUDColorShiftEveryTime : public GUICmdPacketBase
{
public:
	XDateTime	MasterTime;
	GUICmdFilterUDColorShiftEveryTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdFilterClearUDColorShiftEveryTime : public GUICmdPacketBase
{
public:
	XDateTime	MasterTime;

	GUICmdFilterClearUDColorShiftEveryTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // BUTTONFILTERUDCOLORSHIFT_H
