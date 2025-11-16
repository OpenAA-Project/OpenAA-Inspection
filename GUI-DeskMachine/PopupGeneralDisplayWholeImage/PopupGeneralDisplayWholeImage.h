#ifndef POPUPGENERALDISPLAYWHOLEIMAGE_H
#define POPUPGENERALDISPLAYWHOLEIMAGE_H

#include "popupgeneraldisplaywholeimage_global.h"
#include "mtFrameDraw.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImageHook.h"
#include "GeneralDisplayWholeImageForm.h"
#include <QPushButton>
#include <QRect>
#include <QTimer>
#include <QColor>
#include <QStringList>
#include <QFont>
#include <QPainter>
#include <QIODevice>
#include <QImage>
#include "XResult.h"

class PopupGeneralDisplayWholeImage : public GUIFormBase,public DisplayImageHooked
{
	Q_OBJECT

	QPushButton		Button;
	mtFrameDraw		MainCanvas;
	QRect			RealPos;
	bool			BlinkOn;
	QTimer			TM;

	GeneralDisplayWholeImageForm	*PopupForm;

public:
	QColor		FrameColor;
	QColor		ZoneColor;
	QStringList	RelatedPanel;
	bool		Mastered;
	bool		ShowNG;
	bool		BlinkNG;
	QString		Msg;
	QColor		CharColor;
	QColor		BackColor;
	QFont		CFont;
	int32		PopupFormX;
	int32		PopupFormY;
	int32		PopupFormWidth;
	int32		PopupFormHeight;
	bool		VisibleButton;
	bool		AnytimeShow;
	bool		LocationInForm;
	int32		ShowFixedPhase;

    PopupGeneralDisplayWholeImage(LayersBase *Base ,QWidget *parent);
    ~PopupGeneralDisplayWholeImage();

	virtual void	Prepare(void)	override;
	void	ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy);
	void	ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy);
	virtual	void	ReceiveFromRelated(int32 cmd ,void *data);
	
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)		override;
	double	GetZoomRate(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void	SlotClicked(bool checked);
	void	SlotDrawEnd(void);
	void	SlotOnPaint(QPainter &pnt);
	void	ResizeAction();
	void	SlotTimeout();
};

//---------------------------------------------------------
class	GUICmdReqWholeBmp : public GUICmdPacketBase
{
public:
	double	ZoomRate;
	bool	Mastered;
	bool	ShowNG;
	int32	ShowFixedPhase;

	GUICmdReqWholeBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendWholeBmp : public GUICmdPacketBase
{
public:
	QImage		*IData;

	GUICmdSendWholeBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendWholeBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

	void	MakeImage(bool Mastered ,double ZoomRate
					 ,int localPage
					 ,LayersBase &LocalLBase
					 ,bool ShowNG
					 ,int32 ShowFixedPhase);
};

class	CmdGetZoomRate	:public GUIDirectMessage
{
public:
	double	ZoomRate;
};

//---------------------------------------------------------

class	GUICmdReqOkNG : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;

	GUICmdReqOkNG(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendOkNG : public GUICmdPacketBase
{
public:
	ResultInspection::CriticalErrorMode	CriticalError;
	bool	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;

	GUICmdSendOkNG(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // POPUPGENERALDISPLAYWHOLEIMAGE_H
