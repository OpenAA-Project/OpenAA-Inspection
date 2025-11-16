#if	!defined(DisplaySimPanel_h)
#define	DisplaySimPanel_h

#include <QWidget>
#include "NList.h"
#include <QIODevice>
#include "XTypeDef.h"
#include "XDataInLayer.h"
#include "XIntClass.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	DisplaySimPanel : public QWidget,public ServiceForLayers
{
protected:
	int		ItemID;
	bool	ModeShowBlock;
	bool	ModeShowBrightnessNG;

	int		MovX,MovY;
	double	ZoomRate;
	int		GlobalPage;
	int		Layer;

	QString	AlgoRoot;
	QString	AlgoName;
	QString	GUIRoot;
	QString	GUIName;

	ResultInItemRoot	*Result;
	QImage	*ResultImage;
	FlexArea	ItemArea;
	int		LastShitX,LastShitY;

public:
	DisplaySimPanel(LayersBase *base ,QWidget *parent = 0);
	virtual	~DisplaySimPanel(void);

	virtual	void	SetModeShowBlock(bool b);
	virtual	void	SetModeShowBrightnessNG(bool b);
	virtual	void	SetGUI(const QString &_GUIRoot ,const QString &_GUIName)		{	GUIRoot=_GUIRoot;	GUIName=_GUIName;	}
	virtual	void	SetAlgo(const QString	&_AlgoRoot ,const QString &_AlgoName);
	virtual	void	SetGlobalPage(int globalPage)	{	GlobalPage=globalPage;	}
	virtual	void	SetLayer(int layer);
	virtual	void	SetInitial(int ItemID ,FlexArea &InitialArea);

	virtual	void	SetResult(ResultInItemRoot *res);
	virtual	ResultInItemRoot	*GetResult(void)	const	{	return Result;	}
	virtual	void	DrawOther(QPainter &Pnt){}
	virtual	void	SetCenter(int LocalX,int LocalY);
	virtual	void	SetZoomRate(double Z);

protected:
    virtual	void 	paintEvent ( QPaintEvent * event )		override;

	virtual	void	GetDrawInformation(QByteArray &Something){	return;	}

	virtual	void	PaintAfter(QPainter &pnt){}
protected:
	virtual void	mousePressEvent ( QMouseEvent *Ev )		override;
	virtual void	mouseMoveEvent ( QMouseEvent * e )		override;
	virtual void	mouseReleaseEvent ( QMouseEvent * e )	override;
	virtual void	wheelEvent ( QWheelEvent * event )		override;

	virtual	void	ExecuteMousePress	(int GlobalX ,int GlobalY){}
	virtual	void	ExecuteMouseMove	(int GlobalX ,int GlobalY){}
	virtual	void	ExecuteMouseRelease	(int GlobalX ,int GlobalY){}
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
	QString	AlgoRoot;
	QString	AlgoName;
	bool	ModeShowBlock;
	bool	ModeShowBrightnessNG;
	int		Rx,Ry;
	QByteArray	Something;

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
	QByteArray	Something;

	CmdAlgoSimulate(LayersBase *base):GUIDirectMessage(base){}
};

#endif