#ifndef CONFIRMFORM_H
#define CONFIRMFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XIntegrationPacketComm.h"
#include "XPasswordQWidget.h"
#include "mtGraphicUnit.h"
#include "XAlgorithmLibrary.h"
#include "IntegrationImageBank.h"
#include "XConfirmPacket.h"
#include <QTimer>

namespace Ui {
class ConfirmForm;
}
class  ButtonShowConfirm;
class ConfirmPropAlignmentForm;
class ConfirmPropBCRInspectionForm;
class ConfirmPropColorDifferenceForm;
class ConfirmPropDotColorMatchingForm;
class ConfirmPropMeasureLineMoveForm;
class ConfirmAlgorithm;
class ConfirmItemListForm;

extern	const	char	*sRoot;
extern	const	char	*sName;


class ConfirmForm : public QWidget,public ServiceForLayers,public PasswordInQWodget
{
    Q_OBJECT

	friend	class  ButtonShowConfirm;
	friend	class ConfirmAlgorithm;
	friend	class ConfirmItemListForm;

	ButtonShowConfirm	*Parent;
	bool	OnChanging;
	mtGraphicUnit	ImagePanel;
	bool	ReEntrant;
	FlexArea	SelectedArea;
	QTimer		TM;
	bool		DrawModeSelectedArea;
	QImage		ImageSelectedArea;
	ResultForConfirmListContainer	ResultContainer;

	ConfirmAlgorithm	*AlgoList[5];
	QToolButton			*AlgoButton[5];
	ListImageBankPointerContainerContainer  ImageBankGridList;
	ConfirmItemListForm	*ConfirmItemListWindow;
public:
    explicit ConfirmForm(LayersBase *Base ,ButtonShowConfirm *p,QWidget *parent = 0);
    ~ConfirmForm();
    
	void	ZoomArea(int ux1,int uy1,int ux2,int uy2);
	void	SetSelectedArea(FlexArea &_SelectedArea);
	bool	GetDrawModeSelectedArea(void);
	void	ShowNGList(void);
	void	UpdateAgain(void);
	void	ClearRegisterComponent(void);
	void	ShowItemList(void);
	void	ShowConfirmItem(ConfirmAlgorithm *Algo,ConfirmItemList *Item);
private slots:
    void on_toolButtonImageBankOnlyNG_clicked();
    void on_tableWidgetImageBank_itemSelectionChanged();
    void on_pushButtonWhole_clicked();
    void on_tableWidgetResult_itemSelectionChanged();
    void on_pushButtonClose_clicked();

	void	CanvasSlotDrawEnd(void);
	void	CanvasSlotOnPaint(QPainter &);
	void	SlotMouseMove(int ux ,int uy);
	void	SlotMouseLDownWithShift(int ux ,int uy);
	void	SlotMouseLDown(int ux ,int uy);
	void	SlotMouseRDown(int ux ,int uy);
	void	SlotMouseWheel(int,int,int);
	void	SlotTimeOut();
	void	SlotButtonClicked();

    void on_pushButtonSetting_clicked();
    void on_toolButtonImageBankRetryAll_clicked();
    void on_pushButtonMasterImage_clicked();
public slots:
    void on_toolButtonImageBankUpdate_clicked();
private slots:
    void on_listWidgetPhase_itemSelectionChanged();
    void on_tableWidgetResult_clicked(const QModelIndex &index);
    void on_tableWidgetImageBank_clicked(const QModelIndex &index);
    void on_tableWidgetImageBank_doubleClicked(const QModelIndex &index);

private:
    Ui::ConfirmForm *ui;

	double	GetZoomRate(void)			;
	mtGraphicUnit	*GetCanvas(void)	;
	int		GetMovx(void)				;
	int		GetMovy(void)				;
	int		GetCanvasWidth(void)		;
	int		GetCanvasHeight(void)		;
	void	SetMovXY(int mx,int my)		;
	double	GetZoomRateForWhole(void)	;
	double	GetZoomRateForFit(void)		;
	void	SetZoomRate(double ZoomRate);
	double	GetMaxZoomValue(void)		;
	double	GetMinZoomValue(void)		;
	void	SetMaxZoomValue(double d)	;
	void	SetMinZoomValue(double d)	;
	void	ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy);
	void	ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy);

	void	UpdateImageBank(void);

	virtual	void showEvent(QShowEvent *event)		override;
	virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // CONFIRMFORM_H
