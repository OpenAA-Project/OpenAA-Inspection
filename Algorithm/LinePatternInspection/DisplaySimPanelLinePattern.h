#if	!defined(DisplaySimPanelLinePatternl_h)
#define	DisplaySimPanelLinePatternl_h

#include <QWidget>
#include "NList.h"
#include <QIODevice>
#include "XTypeDef.h"
#include "XDataInLayer.h"
#include "XIntClass.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ShowOperationalPanel;

class	DisplaySimPanelLinePattern	: public QWidget,public ServiceForLayers
{
protected:
	int		ItemID;
	bool	ModeShowArea	;
	bool	ModeShowInside	;
	bool	ModeShowOutside	;
	bool	ModeShowNGMark	;

	int		MovX,MovY;
	double	ZoomRate;
	int		GlobalPage;
	int		Layer;

	QString	GUIRoot;
	QString	GUIName;

	ResultInItemRoot	*Result;
	QImage	*ResultImage;
	FlexArea	ItemArea;

	ShowOperationalPanel	*ParentWidget;

public:
	DisplaySimPanelLinePattern(LayersBase *base ,ShowOperationalPanel *parentw ,QWidget *parent = 0);
	~DisplaySimPanelLinePattern(void);

	void	SetModeShowArea		(bool b){	ModeShowArea	=b;	}
	void	SetModeShowInside	(bool b){	ModeShowInside	=b;	}
	void	SetModeShowOutside	(bool b){	ModeShowOutside	=b;	}
	void	SetModeShowNGMark	(bool b){	ModeShowNGMark	=b;	}

	void	SetGUI(const QString &_GUIRoot ,const QString &_GUIName)		{	GUIRoot=_GUIRoot;	GUIName=_GUIName;	}
	void	SetAlgo(const QString	&_AlgoRoot ,const QString &_AlgoName);
	void	SetGlobalPage(int globalPage)	{	GlobalPage=globalPage;	}
	void	SetLayer(int layer);
	void	SetInitial(int ItemID ,FlexArea &InitialArea);

	void	SetResult(ResultInItemRoot *res);

	virtual	void	DrawOther(QPainter &Pnt){}

protected:
    virtual	void	paintEvent(QPaintEvent *event)			override;

protected:
	virtual void	mousePressEvent ( QMouseEvent *Ev )		override;
	virtual void	mouseMoveEvent ( QMouseEvent * e )		override;
	virtual void	mouseReleaseEvent ( QMouseEvent * e )	override;
	virtual void	wheelEvent ( QWheelEvent * event )		override;
};

//===============================================

class	GUICmdReqDSimPanelImage: public GUICmdPacketBase
{
public:
	int	ItemID;
	int	ImageWidth;
	int	ImageHeight;
	int	Layer;
	int	MovX,MovY;
	double	ZoomRate;
	bool	ModeShowArea	;
	bool	ModeShowInside	;
	bool	ModeShowOutside	;
	bool	ModeShowNGMark	;
	int		Rx,Ry;
	int		ResultAngleNumber;
	int32	ShiftBySelfX;
	int32	ShiftBySelfY;

	GUICmdReqDSimPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckDSimPanelImage: public GUICmdPacketBase
{
public:
	QImage	AckImage;

	GUICmdAckDSimPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}

	void	MakeImage(int LocalPage ,int Layer
					,int movx ,int movy ,double ZoomRate);

};

class	CmdAlgoSimulate : public GUIDirectMessage
{
public:
	int		ItemID;
	int		Layer;
	QImage	*Image;
	int	MovX,MovY;
	double	ZoomRate;
	bool	ModeShowArea	;
	bool	ModeShowInside	;
	bool	ModeShowOutside	;
	int		ResultAngleNumber;
	int32	ResultGlobalShiftX;
	int32	ResultGlobalShiftY;
	int32	ShiftBySelfX;
	int32	ShiftBySelfY;

	CmdAlgoSimulate(LayersBase *base):GUIDirectMessage(base){}
};

#endif

