#ifndef GERBERFASTIMAGEPANEL_H
#define GERBERFASTIMAGEPANEL_H

#include "gerberfastimagepanel_global.h"

#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"

class	GerberFastImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	double	FirstMinXonCAD;
	double	FirstMinYonCAD;
	double	FirstMaxXonCAD;
	double	FirstMaxYonCAD;

	double	FirstImageZoomRate;
	double	FirstGToCadZoomRate;
	QImage	BmpData;
	QImage	*BmpDataAlpha;
	QImage	SelectedMap;
	QImage	*SelectedMapAlpha;

	bool	MoveMode;
	int	LastPosX,LastPosY;
	int	MoveStartPosX,MoveStartPosY;

	bool	RotateMode;
	int		RotateCenterXOnData,RotateCenterYOnData;
	int		RotateFirstX,RotateFirstY;

	bool	ExtendMode;
	int		ExtendCenterXOnData,ExtendCenterYOnData;
	int		ExtendFirstX,ExtendFirstY;

	bool	SlopeXMode;
	int		SlopeXCenterXOnData,SlopeXCenterYOnData;
	int		SlopeXFirstX,SlopeXFirstY;

	bool	SlopeYMode;
	int		SlopeYCenterXOnData,SlopeYCenterYOnData;
	int		SlopeYFirstX,SlopeYFirstY;

public:
	bool	AlignmentMode;
	DoublePoint	ImagePoint[MaxGerberPointNumb];
	DoublePoint	CadPoint[MaxGerberPointNumb];	

	bool	AutoMatchingMode;
	DoublePoint	AMImagePoint[100];
	DoublePoint	AMCadPoint[100];

	GerberFastImagePanel(LayersBase *Base ,QWidget *parent);
	~GerberFastImagePanel(void);

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;


	//virtual	void	MouseMoveEvent(int globalX ,int globalY);

	void	PickupColorAndMove(QImage &dst ,QImage &src ,QColor pickcol ,QColor putcol ,int dx,int dy);

	virtual	void	ExecuteMouseLDown(int globalX ,int globalY)	override;
	virtual	void	ExecuteMouseRDown(int globalX ,int globalY)	override;
	virtual	void	ExecuteMouseLDownWithShift(int globalX ,int globalY)	override;
	virtual	void	ButtonExecuteSelectByPage(int globalPage)	override;

	virtual	bool	IsMoveModeButtonDown(void)		const	override;
	virtual	void	MoveStart(int globalX ,int globalY)		override;
	virtual	void	MovingNow(int globalX ,int globalY)		override;
	virtual	void	MoveCancel(void)						override;
	virtual	void	MoveFinish(void)						override;
	virtual	void	SlotMouseLDown(int globalX,int globalY)	override;

	virtual	void	RotateStart(void)							override;
	virtual	void	RotateFixedCenter(int globalX ,int globalY)	override;
	virtual	void	RotateStartAngle(int globalX ,int globalY)	override;
	virtual	void	RotateAngling(int globalX ,int globalY)		override;
	virtual	void	RotateCancel(void)							override;
	virtual	void	RotateFinish(void)							override;

	virtual	void	ExtendStart(void)							override;
	virtual	void	ExtendFixedCenter(int globalX ,int globalY)	override;
	virtual	void	ExtendingStart(int globalX ,int globalY)	override;
	virtual	void	ExtendingNow(int globalX ,int globalY)		override;
	virtual	void	ExtendCancel(void)							override;
	virtual	void	ExtendFinish(void)							override;

	virtual	void	SlopeXStart(void)							override;
	virtual	void	SlopeXFixedCenter(int globalX ,int globalY)	override;
	virtual	void	SlopeXStartAngle(int globalX ,int globalY)	override;
	virtual	void	SlopeXAngling(int globalX ,int globalY)		override;
	virtual	void	SlopeXCancel(void)							override;
	virtual	void	SlopeXFinish(void)							override;

	virtual	void	SlopeYStart(void)							override;
	virtual	void	SlopeYFixedCenter(int globalX ,int globalY)	override;
	virtual	void	SlopeYStartAngle(int globalX ,int globalY)	override;
	virtual	void	SlopeYAngling(int globalX ,int globalY)		override;
	virtual	void	SlopeYCancel(void)							override;
	virtual	void	SlopeYFinish(void)							override;

	void	Set3PointAlignmentMode(void);
	void	AlignmentModeCancel(void);

	void	SetAutoMatchingMode(void);
	void	AutoMatchingCancel(void);

	virtual void	BuildForShow(void)							override;
	virtual void	ShowInEdit(void)							override;
	virtual	void	SelectArea(IntList &LayerList, FlexArea &Area)	override;
	virtual	void	ButtonExecuteCopySelected(bool EnableDup)		override;
	virtual	void	ButtonExecutePasteInSameAlgorithm(void)			override;

	virtual	void	MouseMoveEvent(int globalX ,int globalY)		override;
	virtual	void	ExeSelectItems(FlexArea &Area)					override;

protected:
	virtual	void	DrawBtnDown()		override;
private slots:
	void	ResizeAction();
	virtual	void	MoveItemBtnDown()	override;
protected:
	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage)	override;

private:
	double	GetRotateAngle(void);
	double	GetSlopeXAngle(void);
	double	GetSlopeYAngle(void);
	void	GetExtendRate(double &RateX ,double &RateY);
};

#endif // GERBERFASTIMAGEPANEL_H
