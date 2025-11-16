#ifndef PROPERTYRASTERFORM_H
#define PROPERTYRASTERFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include <QDialog>
#include <QScrollArea>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"
#include "XRaster.h"
#include "XRasterPacket.h"
#include "XGUIRasterPacket.h"
#include "PropertyRasterLine.h"

namespace Ui {
class PropertyRasterForm;
}

class DisplayImageWithAlgorithm;


class PropertyRasterForm : public GUIFormBase
{
    Q_OBJECT

	RasterFileLayerLine			*Child[RasterMaxPhaseNumb][MaxRasterLayer];
	mtFrameDraw::DrawingMode	PanelModeAlignment[RasterMaxPhaseNumb];

	//int		tTransDot;
	//int		tDataIsolation;
	//int		tNearByPattern;
	bool	LoadedRaster;

	RasterElementListContainer		Elements[RasterMaxPhaseNumb];
	PageElementIDClassContainer		ElementIDList[RasterMaxPhaseNumb];
	IntList		MaskIDList;
public:
	//bool	EnableAlgorithm;

    explicit PropertyRasterForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyRasterForm();

	virtual	void	Prepare(void)		override;
	RasterBase	*GetRasterBase(void);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit	(void)	override;
    virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

	void	LoadPDF(const QString &FileName);

	void	CommandMoveItems(double Dx,double Dy);
	void	CommandRotateItems(double Angle);
	void	CommandRotateItems(double Angle ,double Cx ,double Cy);
	void	CommandShearXItems(double Angle);
	void	CommandShearYItems(double Angle);
	void	CommandZoomItems(double ZoomX,double ZoomY);
	void	CommandZoomItems(double ZoomX,double ZoomY ,double Cx ,double Cy);
	
	void	CommandMoveByMouse(void);
	void	CommandRotateByMouse(void);
	void	CommandZoomByMouse(void);
	void	CommandMirrorX(void);
	void	CommandMirrorY(void);
	void	CommandMakeImageToMaster(IntList &LayerLineNo,IntList &CompoLineNo);
	void	CommandMakeImageToMaster(void);
	void	CommandMakeBitImageToMaster(IntList &LayerLineNo,IntList &CompoLineNo);
	void	CommandMakeImageToMasterInMask(int RasterLibID);

	void	SendShowingState(void);
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	virtual	void	StartInitial(void)	override;
private slots:
    void on_pushButtonLoadRaster_clicked();
    void on_listWidgetRasterList_itemSelectionChanged();
    void on_pushButtonMove_clicked();
    void on_pushButtonRotate_clicked();
    void on_pushButtonZoom_clicked();
    void on_pushButtonShear_clicked();
    void on_pushButtonMirrorX_clicked();
    void on_pushButtonMirrorY_clicked();
    void on_pushButtonCenterize_clicked();
    void on_toolButtonMove_clicked();
    void on_toolButtonRotate_clicked();
    void on_toolButtonShearX_clicked();
    void on_toolButtonShearY_clicked();
    void on_toolButtonZoom_clicked();
    void on_toolButtonDraw_clicked();
    void on_pushButtonClearMatchPoints_clicked();
    void on_pushButtonStartMoveToMatch_clicked();
    void on_pushButtonToImage_clicked();
    void on_pushButtonToBitImage_clicked();
    void on_pushButtonToAlgorithm_clicked();
    void on_tableWidgetAlignments_clicked(const QModelIndex &index);
    void on_tableWidgetAllocation_itemSelectionChanged();
    void on_tableWidgetAllocation_doubleClicked(const QModelIndex &index);
    void on_tabWidgetOperation_currentChanged(int index);
    void on_toolButtonPickupByColor_clicked();
    void on_toolButtonPickupByEdge_clicked();

	void	SlotCenterizeFit();
	void	SlotCenterizeOnly();

    void on_toolButtonPickupByColorReference_clicked();
    void on_toolButtonPickupByEdgeReference_clicked();
    void on_pushButtonEditLibrary_clicked();
    void on_toolButtonPickColor_clicked();
    void on_toolButtonMoveElement_clicked();
    void on_pushButtonToDispatchImage_clicked();
    void on_pushButtonShowPDF_clicked();
    void on_pushButtonShowColorProfile_clicked();
    void on_toolButtonPickColorProfile_clicked();
    void on_pushButtonConvertColor_clicked();
    void on_toolButtonPartial_clicked();
    void on_toolButtonMask_clicked();
    void on_listWidgetRasterMask_itemSelectionChanged();
    void on_listWidgetRasterMask_clicked(const QModelIndex &index);
    void on_listWidgetRasterMask_doubleClicked(const QModelIndex &index);
    void on_toolButtonDrawMask_clicked();
    void on_pushButtonSaveTransform_clicked();
    void on_pushButtonLoadTransform_clicked();
    void on_pushButtonSaveTransformDefault_clicked();
    void on_pushButtonLoadTransformDefault_clicked();
    void on_pushButtonMakeProfileByImage_clicked();
    void on_pushButtonLoadColorProfile_clicked();

private:
    Ui::PropertyRasterForm *ui;

	void	RepaintImage(void);
	void	GetCenterRaster(double &MinX ,double &MinY ,double &MaxX ,double &MaxY);
	void	MakeImageToMaster(void);
	void	MakeBitImage(void);

	void	ShowMaskIDList(void);
	
	RasterOperationMode	GetCurrentOperationMode(void);
	DisplayImageWithAlgorithm	*GetImagePanel(void);
	void	GetOperationalButton(BoolList &ButtonsToOperateLayer);

	void	UpdateAlignment(void);
	void	GoNextStepAlignment(void);
	void	GoNextStepForAddAlignment(void);
	int		GetInputTypeAlignment(void);
	int		GetInputNumberAlignment(void);

	void	ShowAllocationGrid(void);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

	int		GetLineCount(void);
	int		GetMaxFileLayerID(void);
	void	ReflectChildToWindow(void);
	int		GetCurrentFileLayerID(void);

	void	LoadRaster(int FileNo,QByteArray &Data ,const QString &FileName);

	bool	SaveTransform(const QString &FileName);
	bool	LoadTransform(const QString &FileName);

	void	TransferRasterToImage(void);
};

#endif // PROPERTYRASTERFORM_H
