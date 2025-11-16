#pragma once

#include <QString>
#include <QAbstractButton>
#include <QWidget>
#include "XIntClass.h"
#include "XAlgorithmLibrary.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include "XGUIComponent.h"
#include "XConfirmPacket.h"
#include "XDataAlgorithmConfirm.h"

class FlexArea;
class AlgorithmLibTypeWithAttrDataContainer;
class ConfirmForm;
class mtGraphicUnit;

class ConfirmAlgorithm : public QWidget
{
	Q_OBJECT
	friend	class ConfirmForm;

	NPListPack<MemberComponentList>	MemberComponentContainer;
	bool	EnableChangeMode;
protected:
	ConfirmForm	*Parent;
	AlgorithmLibraryList		SelectedLib;
	ListPhasePageLayerItemPack	SelectedItems;
	QAbstractButton				*Button;
public:
	ConfirmItemListContainer	ConfirmItemInst;
protected:
	bool	OnChanging;

public:
	ConfirmAlgorithm(ConfirmForm *p);

	virtual	int		GetLibType(void)				=0;
	virtual	QString	GetButtonName(void)				=0;
	void	SetButton(QAbstractButton *btn)	{	Button=btn;		}
	QAbstractButton *GetButton(void)		{	return Button;	}
	virtual	QWidget	*GetPropertyWidget(void)		=0;
	virtual	void	InitialShow(void)				=0;
	void	MakeConfirmItemList(void);
	void	PushButton(void);
	virtual	void	SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)	=0;
	virtual	void	AlgoMouseMove(int ux ,int uy);
	virtual	void	AlgoMouseLDownWithShift(int ux ,int uy)	{}
	virtual	void	AlgoMouseLDown(int ux ,int uy)			{}
	virtual	void	AlgoMouseRDown(int ux ,int uy)	;
	virtual	void	CanvasSlotDrawEnd(FlexArea &Area);
	virtual	void	CanvasSlotOnPaint(mtGraphicUnit	&ImagePanel,int page,QImage &Pnt){};
	virtual	void	SetProperty(void)				=0;
	virtual	void	ForceDraw(void)					=0;
	virtual	void	ShowConfirmItem(ConfirmItemList *Item)=0;

	int	GetSlaveNo(void);
	void	ZoomArea(int ux1,int uy1,int ux2,int uy2);

	virtual	void	GetItemsByArea(int LibID,FlexArea &GlobalArea);
	virtual	void	GetItemsByPoint(int GlobalX, int GlobalY);
	virtual	void	SetSelectItemsByGroupID(int ErrorGroupID);
	virtual	void	GetAllItems(int LibID);
	virtual	void	SetSelectItems(void);
	virtual	void	ClearSelectItems(void);
	virtual	void    ShowItemData(void){}
	virtual	void    ShowResult(void){}

	void	ClearRegisterComponent(void);
	void	RegisterComponent(int MemberID ,QSpinBox *e);
	void	RegisterComponent(int MemberID ,QDoubleSpinBox *e);
	void	RegisterComponent(int MemberID ,QLineEdit *e);
	void	RegisterComponent(int MemberID ,QCheckBox *e);
	void	RegisterComponent(int MemberID ,QComboBox *e);

	void	GetEdittedList(IntList &EdittedMemberID);
	void	SetEnableChangeMode(bool b)	{	EnableChangeMode=b;	}

private slots:
	void	SlotValueChangedInt(int n);
	void	SlotValueChangedDouble(double n);
	void	SlotTextChanged(const QString &text);
	void	SlotStateChanged(int state);
	void	SlotCurrentIndexChanged(int index);
};

