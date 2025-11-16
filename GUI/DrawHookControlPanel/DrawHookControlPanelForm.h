#ifndef DRAWHookCONTROLPANELFORM_H
#define DRAWHookCONTROLPANELFORM_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "mtPushButtonColored.h"
#include<QColor>
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"
#include "NListComp.h"
#include "XYCross.h"
#include<QIODevice>
#include<QPainter>
#include "XFlexArea.h"

namespace Ui {
class DrawHookControlPanelForm;
}

class DrawHookControlPanelForm;


class	DrawerItemBase :public NPList<DrawerItemBase>
{
	DrawHookControlPanelForm	*Parent;
public:
	int		ID;
	bool	Selected;
	bool	OnCreating;
	bool	CreatingNew;
	int		OffsetX, OffsetY;

	DrawerItemBase(DrawHookControlPanelForm *p):Parent(p)
	{
		Selected = false;		OnCreating = true;	CreatingNew=true;	OffsetX = OffsetY = 0;	
	}
	virtual	~DrawerItemBase(void){}

	virtual	bool	GetXY(int &x1 ,int &y1 , int &x2 ,int &y2)	=0;
	virtual	bool	IsNear(DisplayImage *Target ,int GlobalX ,int GlobalY)			=0;
	virtual	void	Draw(DisplayImage *Target ,QPainter &pnt,double ZoomRate,int movx ,int movy ,bool DrawFrame=true)		=0;
	virtual	void	MoveTo(int dx, int dy)	=0;
	virtual	int		GetClassType(void)	=0;
	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;
	virtual	void	Transform(double m[6])	=0;
	virtual	FlexArea	MakeArea(void)		=0;

	virtual	void	CopyToLast(void)		=0;
	virtual	void	RestoreFromLast(void)	=0;

	void	SetOffset(int hx, int hy) {		OffsetX = hx;	OffsetY = hy;	}

	bool	GetWindowArea(DisplayImage *Target ,int &Width ,int &Height);
	double	GetWindowZoomRate(DisplayImage *Target);

};

class	DrawerItemContainer :public NPListPack<DrawerItemBase>
{
	DrawHookControlPanelForm	*Parent;
public:
	int		CurrentMaxID;
	DrawerItemContainer(DrawHookControlPanelForm *p):Parent(p){	CurrentMaxID=0;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	DrawerItemContainer	&operator=(DrawerItemContainer &src);

	DrawerItemBase	*NewClass(int ClassType);

	void	ReleaseSelect(void);
	void	RemoveCreating(void);
	DrawerItemBase	*GetCreating(void);
	DrawerItemBase	*GetSelected(void);
	DrawerItemBase	*GetSelectedOnCreating(void);
};

class	DrawItemLine : public DrawerItemBase
{
	int		lastx1,lasty1,lastx2,lasty2;
public:
	int		x1,y1,x2,y2;

	int		LineWidth;
	int		LineType;	//0:Solid	1:Dot	2:Double
	QColor	LineColor;
	int		LineStartType;	//0:Closed	1:Open	2:Arrow	3:Round	4:Bar
	int		LineEndType;	//0:Closed	1:Open	2:Arrow	3:Round	4:Bar

	DrawItemLine(DrawHookControlPanelForm *p);
	virtual	int		GetClassType(void)		override{	return 1;	}

	virtual	bool	GetXY(int &x1 ,int &y1 , int &x2 ,int &y2)				override;
	virtual	bool	IsNear(DisplayImage *Target ,int GlobalX ,int GlobalY)	override;
	virtual	void	Draw(DisplayImage *Target ,QPainter &pnt,double ZoomRate,int movx ,int movy ,bool DrawFrame=true)	override;
	virtual	void	MoveTo(int dx, int dy)	override;
	virtual	void	CopyToLast(void)		override;
	virtual	void	RestoreFromLast(void)	override;
	bool	operator==(DrawItemLine &src);
	virtual	void	Transform(double m[6])	override;
	virtual	FlexArea	MakeArea(void)		override;

	virtual	bool	Save(QIODevice *f)		override;
	virtual	bool	Load(QIODevice *f)		override;
};


class	DrawItemDraw : public DrawerItemBase
{
	XYClassContainer	LastPoints;
public:
	XYClassContainer	Points;

	int		DrawType;		//0:Rectangle	1:Round	2:Polygon
	int		LineType;		//0:Solid	1:Dot	2:Double
	int		DrawLineWidth;
	QColor	DrawLineColor;
	int		DrawInsideType;	//0:No draw	1:Solid	2:Hatch
	QColor	DrawInsideColor;

	DrawItemDraw(DrawHookControlPanelForm *p);

	virtual	bool	GetXY(int &x1 ,int &y1 , int &x2 ,int &y2)				override;
	virtual	bool	IsNear(DisplayImage *Target ,int GlobalX ,int GlobalY)	override;
	virtual	void	Draw(DisplayImage *Target ,QPainter &pnt,double ZoomRate,int movx ,int movy ,bool DrawFrame=true)	override;
	virtual	void	MoveTo(int dx, int dy)	override;
	virtual	void	CopyToLast(void)		override;
	virtual	void	RestoreFromLast(void)	override;
	bool	operator==(DrawItemDraw &src);
	virtual	void	Transform(double m[6])	override;
	virtual	FlexArea	MakeArea(void)			override;

	virtual	int		GetClassType(void)		override{	return 2;	}
	virtual	bool	Save(QIODevice *f)		override;
	virtual	bool	Load(QIODevice *f)		override;
};


class	DrawItemText : public DrawerItemBase
{
	int	LastX,LastY;
public:
	int		X,Y;
	QString	Text;

	int		TextHeight;
	QFont	TextFont;
	QColor	TextColor;

	DrawItemText(DrawHookControlPanelForm *p);

	virtual	bool	GetXY(int &x1 ,int &y1 , int &x2 ,int &y2)				override;
	virtual	bool	IsNear(DisplayImage *Target ,int GlobalX ,int GlobalY)	override;
	virtual	void	Draw(DisplayImage *Target ,QPainter &pnt,double ZoomRate,int movx ,int movy ,bool DrawFrame=true)	override;
	virtual	void	MoveTo(int dx, int dy)	override;
	virtual	void	CopyToLast(void)		override;
	virtual	void	RestoreFromLast(void)	override;
	bool	operator==(DrawItemText &src);
	virtual	void	Transform(double m[6])	override;
	virtual	FlexArea	MakeArea(void)			override;

	virtual	int		GetClassType(void)		override{	return 3;	}
	virtual	bool	Save(QIODevice *f)		override;
	virtual	bool	Load(QIODevice *f)		override;
};



class DrawHookControlPanelForm : public GUIFormBase,public FunctionServerClass
{
    Q_OBJECT

	mtPushButtonColored	*ButtonLineColor;
	mtPushButtonColored	*ButtonDrawLineColor;
	mtPushButtonColored	*ButtonDrawInsideColor;
	mtPushButtonColored	*ButtonTextColor;

	DrawerItemContainer	DrawerItemDatas;
	DisplayImagePointerContainer		TargetPanels;
	QFont				CurrentFont;
	int					CurrentStepNo;
public:
	QStringList	HookedPanelListName;
	int		MoveStep;	//0:Normal	1:Select items	2:FirstPoint	3:Done
	int		GlobalMovX1,GlobalMovY1;
	int		GlobalMovX2,GlobalMovY2;
	bool	Active;
	enum EnumOperationMode
	{
		Mode_None		=0
		,Mode_Delete	=1
		,Mode_Edit		=2
		,Mode_Move		=3
		,Mode_Append	=4
	};
	EnumOperationMode	OperationMode;

    explicit DrawHookControlPanelForm(LayersBase *Base,QWidget *parent = 0);
    ~DrawHookControlPanelForm();

	virtual	void	Prepare(void)		override;
	virtual	void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QStringList	GetRelatedForm(void)	override	{	return HookedPanelListName;	}

	void	Draw						(DisplayImage *Target ,QPainter &pnt					,double ZoomRate,int movx ,int movy);
	void	MouseMove					(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy);
	void	MouseLClickNew				(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy);
	bool	MouseLClickSelect			(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy);
	bool	MouseLClickSelectForMove	(DisplayImage* Target, int GlobalPosX, int GlobalPosY	,double ZoomRate,int movx, int movy);
	bool	MouseLClickSelectedOnCreating(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy);
	bool	MouseLClickDelete			(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy);
	void	MouseLDoubleClickNew		(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy);
	void	MouseLDoubleClickSelect		(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy);
	void	MouseRClick					(DisplayImage *Target ,int GlobalPosX,int GlobalPosY	,double ZoomRate,int movx ,int movy);

	bool	IsModeNew(void);
	bool	IsModeSelect(void);
	bool	IsModeSelectedOnCreating(void);

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

	void	MoveItems(int dx ,int dy);
	void	MoveItemsTmp(int dx, int dy);
	bool	MouseFinishEdit(void);
	bool	MouseFinishMove(void);

	void	UndoAddItem(QIODevice *f);
	void	RedoAddItem(QIODevice *f);
	void	UndoMoveItem(QIODevice *f);
	void	RedoMoveItem(QIODevice *f);
	void	UndoDeleteItem(QIODevice *f);
	void	RedoDeleteItem(QIODevice *f);

signals:
	void	SignalSelectedItem(const QString &ClassName ,int ItemID);
	void	SignalAddItem(const QString &ClassName ,int ItemID);
	void	SignalMoveItem(const QString &ClassName ,int ItemID);
	void	SignalDeleteItem();
	void	SignalReleaseAllSelection();
private slots:
    void on_spinBoxLineWidth_valueChanged(int arg1);
    void on_comboBoxLineType_currentIndexChanged(int index);
    void on_toolButtonLineColor_clicked();
    void on_comboBoxLineStartType_currentIndexChanged(int index);
    void on_comboBoxLineEndType_currentIndexChanged(int index);
    void on_comboBoxDrawType_currentIndexChanged(int index);
    void on_spinBoxDrawLineWidth_valueChanged(int arg1);
    void on_toolButtonDrawLineColor_clicked();
    void on_comboBoxDrawInsideType_currentIndexChanged(int index);
    void on_toolButtonDrawInsideColor_clicked();
    void on_spinBoxTextSize_valueChanged(int arg1);
    void on_pushButtonTextFont_clicked();
    void on_toolButtonTextColor_clicked();
    
	void	ResizeAction();

    void on_toolButtonNew_clicked();
    void on_toolButtonSelect_clicked();
    void on_toolButtonDelete_clicked();
    void on_toolBox_currentChanged(int index);

	void	CancelPolyAction();
	void	DonePolyAction();
public slots:
	void	SlotReleaseAllSelection();
private:
    Ui::DrawHookControlPanelForm *ui;
};
class	CmdDrawHookControlPanel : public GUIDirectMessage
{
public:
	QPainter	*Pnt;
	int		movx,movy;
	double	ZoomRate;

	CmdDrawHookControlPanel(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookControlPanel_Save : public GUIDirectMessage
{
public:
	QByteArray	Data;

	CmdHookControlPanel_Save(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookControlPanel_Load : public GUIDirectMessage
{
public:
	QByteArray	Data;

	CmdHookControlPanel_Load(LayersBase *base):GUIDirectMessage(base){}
};


class	CmdHookControlPanel_SetActivate : public GUIDirectMessage
{
public:
	bool	Active;

	CmdHookControlPanel_SetActivate(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookControlPanel_SetDeleteMode : public GUIDirectMessage
{
public:
	CmdHookControlPanel_SetDeleteMode(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookControlPanel_SetDeleteOff : public GUIDirectMessage
{
public:
	CmdHookControlPanel_SetDeleteOff(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookControlPanel_SetEditMode : public GUIDirectMessage
{
public:
	bool	EditMode;

	CmdHookControlPanel_SetEditMode(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookControlPanel_SetAppendMode : public GUIDirectMessage
{
public:
	bool	AppendMode;

	CmdHookControlPanel_SetAppendMode(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdHookControlPanel_SetMoveMode : public GUIDirectMessage
{
public:
	bool	MoveMode;

	CmdHookControlPanel_SetMoveMode(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdHookControlPanel_GetLineProperty : public GUIDirectMessage
{
public:
	int		ID;

	int		LineWidth;
	int		LineType;	//0:Solid	1:Dot	2:Double
	QColor	LineColor;
	int		LineStartType;	//0:Closed	1:Open	2:Arrow	3:Round	4:Bar
	int		LineEndType;	//0:Closed	1:Open	2:Arrow	3:Round	4:Bar
	bool	Found;

	CmdHookControlPanel_GetLineProperty(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookControlPanel_GetDrawInfo : public GUIDirectMessage
{
public:
	int		ID;

	int		DrawType;		//0:Rectangle	1:Round	2:Polygon
	int		LineType;		//0:Solid	1:Dot	2:Double
	int		DrawLineWidth;
	QColor	DrawLineColor;
	int		DrawInsideType;	//0:No draw	1:Solid	2:Hatch
	QColor	DrawInsideColor;
	bool	Found;

	CmdHookControlPanel_GetDrawInfo(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookControlPanel_GetTextInfo : public GUIDirectMessage
{
public:
	int		ID;

	QString	Text;

	int		TextHeight;
	QFont	TextFont;
	QColor	TextColor;
	bool	Found;

	CmdHookControlPanel_GetTextInfo(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookControlPanel_GetSelectedItemCount : public GUIDirectMessage
{
public:
	int		SelectedItemCount;

	CmdHookControlPanel_GetSelectedItemCount(LayersBase *base):GUIDirectMessage(base){}
};


#endif // DRAWHookCONTROLPANELFORM_H
