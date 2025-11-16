#ifndef HOOKMEASUREFORM_H
#define HOOKMEASUREFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"
#include "NListComp.h"

namespace Ui {
class HookMeasureForm;
}

class	ItemButton : public QToolButton
{
    Q_OBJECT
public:
	ItemButton ( QWidget * parent = 0);

signals:
	void	SignalRightButton();
protected:
	void	mouseReleaseEvent ( QMouseEvent * e );
};

class	HookMeasureForm;

class HookMeasureForm : public GUIFormBase,public FunctionServerClass
{
    Q_OBJECT
	DisplayImagePointerContainer		TargetPanels;

public:
	QStringList	HookTargetListInst;

	enum	__SelectionMode
	{
		__S_Addmode
		,__S_ModifyMode
		,__S_SelectMode
		,__S_MoveMode
		,__S_DeleteMode
	}SelectionMode;

	enum	__LineType
	{
		__LT_Solid			=0
		,__LT_DashLine		=1
		,__LT_DotLine		=2
		,__LT_DashDotLine	=3
		,__LT_DashDotDotLine=4
	};
	
	QColor	LineColor;
	QColor	CircleColor;
	QFont	TextFont;
	int		LineWidth;
	int		CircleSize;
	int		TextSize;
	int		ArrowSize;
	int		DistanceSelection;
	__LineType	LineType;
	bool	Active;

    explicit HookMeasureForm(LayersBase *Base ,QWidget *parent = 0);
    ~HookMeasureForm();

	virtual void	ReadyParam(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet) override;

	void	Draw	(QPainter &pnt	,double ZoomRate,int movx ,int movy);
	virtual	QStringList	GetRelatedForm(void)	override	{	return HookTargetListInst;	}

	bool	IsModeEnable(void);
    void	MouseLClick(int GlobalPosX,int GlobalPosY);
	void	MouseRClick(int GlobalPosX,int GlobalPosY);
	void	MouseLDblClick(int GlobalPosX,int GlobalPosY);

	bool	MouseMove(int GlobalPosX,int GlobalPosY);
	bool	EditSelection	(DisplayImage *TargetPanel ,int GlobalPosX,int GlobalPosY ,double ZoomRate);
	bool	EditModification(DisplayImage *TargetPanel ,int GlobalPosX,int GlobalPosY ,double ZoomRate);
	bool	DeleteSelection	(DisplayImage *TargetPanel ,int GlobalPosX,int GlobalPosY ,double ZoomRate);
	bool	EditMove		(DisplayImage *TargetPanel ,int GlobalPosX,int GlobalPosY ,double ZoomRate);
private:
    Ui::HookMeasureForm *ui;

	virtual	void	showEvent (QShowEvent * event)	override;

public:
	class	MeasuredList : public NPList<MeasuredList>
	{
	public:
		HookMeasureForm	*Parent;
		int	Step;
		int	ID;

		QColor	LineColor;
		QColor	CircleColor;
		int32	LineWidth;
		int32	ArrowSize;
		__LineType	LineType;
		int		TextSize;
		QFont	TextFont;

		QPoint	P2PA,P2PB;
		QList<QPoint>	PN;
		QPoint	P2PC,P2PD;
		QPoint	P2PE,P2PF;
		enum	MLA_Action
		{
			 _MLA_Nothing		=0
			,_MLA_Point2Point	=1
			,_MLA_FoldedLines	=2
			,_MLA_Arc			=3
			,_MLA_CenterCircle	=9
			,_MLA_Angle			=4
			,_MLA_Rectangle		=5
			,_MLA_PolyLine		=6
			,_MLA_Circle		=7
			,_MLA_Isolation		=8
			,_MLA_Circle3		=10
		};
		MLA_Action	Action;

		enum	MLA_Status
		{
			_MLA_Normal			=0
			,_MLA_Selected		=1
			,_M_A_Modify		=3
			,_MLA_Active		=2
		};
		MLA_Status	Status;

		MeasuredList(HookMeasureForm *P);
		MeasuredList(HookMeasureForm *P,const MeasuredList &src);
		void	Draw	(QPainter &pnt	,double ZoomRate,int movx ,int movy);
		void	MoveTo(int dx ,int dy);

		HookMeasureForm::MeasuredList	&operator=(const HookMeasureForm::MeasuredList &src);
		bool	operator==(MeasuredList &src);
		void	Swap(MeasuredList &s);
		void	Transform(double m[6]);

		bool	EditSelection(int GlobalPosX,int GlobalPosY ,int Distance);

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
private:
	int	CurrentMaxID;
	NPListPack<MeasuredList>	MeasuredData;
	MeasuredList	CurrentData;
	MeasuredList	LastLine;

	void	UndoAddItem(QIODevice *f);
	void	RedoAddItem(QIODevice *f);
	void	UndoMoveItem(QIODevice *f);
	void	RedoMoveItem(QIODevice *f);
	void	UndoDeleteItem(QIODevice *f);
	void	RedoDeleteItem(QIODevice *f);
public:
	int				MoveStep;
	int				GlobalMovX1,GlobalMovY1;
	int				GlobalMovX2,GlobalMovY2;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	void	MoveItems(int gdx ,int gdy);
	void	ReleaseAllMoveMode(void);
	void	ReleaseAllSelectMode(void);
	void	FinishAllMoveMode(void);

	int		GetSelectedCount(void);
	void	MouseLDblClickForModification(MeasuredList *m);

	HookMeasureForm::MeasuredList *GetModified(void);
	HookMeasureForm::MeasuredList *GetSelected(void);
	bool	MouseModify				(HookMeasureForm::MeasuredList *m ,int GlobalPosX,int GlobalPosY);
	void	MouseLClickModification	(HookMeasureForm::MeasuredList *m ,int GlobalPosX,int GlobalPosY);
	void	MouseRClickModification(HookMeasureForm::MeasuredList *m,int GlobalPosX,int GlobalPosY);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

private slots:
	void	ResizeAction();
    void on_toolButtonPoint2Point_clicked();
    void on_toolButtonFoldedLines_clicked();
    void on_toolButtonCenterCircle_clicked();
    void on_toolButtonArc_clicked();
    void on_toolButtonAngle_clicked();
    void on_toolButtonRectangle_clicked();
    void on_toolButtonPolyLine_clicked();
    void on_toolButtonCircle_clicked();
    void on_toolButtonIsolation_clicked();
    void on_toolButtonCircle3_clicked();
	void	SlotRClicked();
	void	CancelPolyAction();
	void	CancelPolyPointAction();
	void	DonePolyAction();
	void	MCancelPolyAction();
	void	MCancelPolyPointAction();
	void	MDonePolyAction();
	void	SlotReleaseAllSelection();
signals:
	void	SignalChangeAction();
	void	SignalSelectedItem(int MLA_ActionID ,int ItemID);
	void	SignalAddItem(int MLA_ActionID,int ItemID);
	void	SignalMoveItem(int MLA_ActionID,int ItemID);
	void	SignalDeleteItem();
	void	SignalReleaseAllSelection();
};

class	CmdSelectHookMeasure : public GUIDirectMessage
{
public:
	CmdSelectHookMeasure(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdShowHookMeasure : public GUIDirectMessage
{
public:
	bool	Showing;
	CmdShowHookMeasure(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdMoveModeHookMeasure : public GUIDirectMessage
{
public:
	bool	MoveMode;
	CmdMoveModeHookMeasure(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdDeleteHookMeasure : public GUIDirectMessage
{
public:
	CmdDeleteHookMeasure(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdDrawMeasure : public GUIDirectMessage
{
public:
	QPainter	*Pnt;
	int		movx,movy;
	double	ZoomRate;

	CmdDrawMeasure(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetHookMeasureLineColor: public GUIDirectMessage
{
public:
	QColor	LineColor;
	bool	ChangeSelection;
	CmdSetHookMeasureLineColor(LayersBase *base):GUIDirectMessage(base){	ChangeSelection=false;	}
};

class	CmdSetHookMeasureFont: public GUIDirectMessage
{
public:
	QFont	TextFont;
	bool	ChangeSelection;
	CmdSetHookMeasureFont(LayersBase *base):GUIDirectMessage(base){	ChangeSelection=false;	}
};

class	CmdGetHookMeasureLineColor: public GUIDirectMessage
{
public:
	QColor	LineColor;
	CmdGetHookMeasureLineColor(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetHookMeasureFont: public GUIDirectMessage
{
public:
	QFont	TextFont;
	CmdGetHookMeasureFont(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetCurrentHookMeasureType : public GUIDirectMessage
{
public:
	HookMeasureForm::MeasuredList::MLA_Action	CurrentIndex;

	CmdSetCurrentHookMeasureType(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetCurrentHookMeasureType : public GUIDirectMessage
{
public:
	HookMeasureForm::MeasuredList::MLA_Action	CurrentIndex;

	CmdGetCurrentHookMeasureType(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetHookMeasureLineWidth: public GUIDirectMessage
{
public:
	int	LineWidth;
	bool	ChangeSelection;
	CmdSetHookMeasureLineWidth(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetHookMeasureLineWidth: public GUIDirectMessage
{
public:
	int	LineWidth;

	CmdGetHookMeasureLineWidth(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetHookMeasureLineType: public GUIDirectMessage
{
public:
	HookMeasureForm::__LineType	LineType;
	bool	ChangeSelection;
	CmdSetHookMeasureLineType(LayersBase *base):GUIDirectMessage(base){	ChangeSelection=false;}
};

class	CmdGetHookMeasureLineType: public GUIDirectMessage
{
public:
	HookMeasureForm::__LineType	LineType;

	CmdGetHookMeasureLineType(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookMeasure_Save: public GUIDirectMessage
{
public:
	QByteArray	Data;

	CmdHookMeasure_Save(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookMeasure_Load: public GUIDirectMessage
{
public:
	QByteArray	Data;

	CmdHookMeasure_Load(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookMeasure_SetActivate: public GUIDirectMessage
{
public:
	bool	Active;

	CmdHookMeasure_SetActivate(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookMeasure_SetDeleteMode: public GUIDirectMessage
{
public:
	CmdHookMeasure_SetDeleteMode(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookMeasure_Transform: public GUIDirectMessage
{
public:
	double	m[6];
	CmdHookMeasure_Transform(LayersBase *base):GUIDirectMessage(base){}
};

class	GetHookMeasure_ReqLineProperty: public GUIDirectMessage
{
public:
	int		MLA_ActionID;
	int		ID;

	int		LineWidth;
	QColor	LineColor;
	QColor	CircleColor;
	int		TextSize;
	QFont	TextFont;
	int32	ArrowSize;
	HookMeasureForm::__LineType	LineType;
	bool	Found;
					
	GetHookMeasure_ReqLineProperty(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdHookMeasure_GetSelectedItemCount :public GUIDirectMessage
{
public:
	int		SelectedItemCount;

	CmdHookMeasure_GetSelectedItemCount(LayersBase *base):GUIDirectMessage(base){}
};

#endif // HOOKMEASUREFORM_H
