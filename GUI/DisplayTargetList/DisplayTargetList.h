#pragma once

#include "displaytargetlist_global.h"
#include <QLabel>
#include <QColor>
#include <QFont>
#include <QWidget>
#include <QScrollArea>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"

class   DisplayTargetList;
class TargetPanelInList;

class TargetImageWindow : public QWidget,public ServiceForLayers
{
	TargetPanelInList	*Parent;
	QImage				Image;
public:
	TargetImageWindow(TargetPanelInList *p);
	~TargetImageWindow();

private:
	virtual	void paintEvent(QPaintEvent *event)			override;
	virtual	void mouseReleaseEvent(QMouseEvent *event)	override;
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

#define	TitleHeightTarget	30

class TargetPanelInList : public QWidget ,public NPList<TargetPanelInList>,public ServiceForLayers
{
	DisplayTargetList	*Parent;
public:
	int					Page;

	TargetImageWindow	ImageWindow;
	QLabel				Title;
public:
	TargetPanelInList(DisplayTargetList *p ,QWidget *parent,int page);
	~TargetPanelInList(void){}

	void	SetPage(int page);
	bool	IsBlickON(void);
	void	SetResult(bool3 ResultOK,bool MaxError,bool TimeOver);
	void	MouseReleased(QMouseEvent *event);
	void	DoubleClickEvent(QMouseEvent *event);

protected:
	void	resizeEvent(QResizeEvent *event);
};

class   DisplayTargetList: public GUIFormBase
{
	Q_OBJECT

	QTimer	Timer;
public:
	bool	BlinkNG;

	QStringList	RelatedInst;
	NPListPack<TargetPanelInList>	TargetPaneStocker;
	int32	PanelSizeX;
	int32	PanelSizeY;
	QScrollArea	ScrollArea;
	QWidget		*ScrollWidget;

    DisplayTargetList(LayersBase *Base ,QWidget *parent);

	virtual void	BuildForShow(void)	override;
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)				override;
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)override;
	virtual	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	virtual	bool	RemovePage(int IndexPage);

	void	MouseReleased(int Page,QMouseEvent *event);
	void	DoubleClickEvent(int Page,int X,int Y);

private slots:
    void	ResizeAction();
	void	SlotTimeOut();
};

//=====================================================================================

class	GUICmdReqImageForList : public GUICmdPacketBase
{
public:
	int		Phase;
	int		GWidth ;
	int		GHeight;
	bool	ShowNGMark;

	GUICmdReqImageForList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckImageForList : public GUICmdPacketBase
{
	QImage	TmpImage;
public:
	int		GWidth ;
	int		GHeight;
	BYTE	*ImageData;
	bool3	ResultOK;
	bool	MaxError;
	bool	TimeOver;

	GUICmdAckImageForList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckImageForList(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeImage(DataInPage *Pd,double ZoomRate,int tGWidth ,int tGHeight,bool ShowNGMark);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
