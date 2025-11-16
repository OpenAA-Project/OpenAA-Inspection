#ifndef PROPERTYDXFOPERATIONFORM_H
#define PROPERTYDXFOPERATIONFORM_H

#include "XGUIFormBase.h"
#include <QModelIndex>
#include "XDXFOperation.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class PropertyDXFOperationForm;
}

class	DXFOperationBase;

class PropertyDXFOperationForm : public GUIFormBase
{
    Q_OBJECT
    
	DXFLayerContainer	DXFLayerList;
	AlgorithmLibraryListContainer	MaskLib;
	AlgorithmLibraryListContainer	InspLib;
public:
    explicit PropertyDXFOperationForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyDXFOperationForm();

    virtual void	ReadyParam(void)    override;
	virtual void	ShowInEdit(void)    override;
	virtual void	BuildForShow(void)  override;
    virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
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

	DXFOperationBase	*GetDXFOperationBase(void);

private slots:
    void on_listWidgetDXFFileName_clicked(const QModelIndex &index);
    void on_pushButtonRegisterFileName_clicked();
    void on_pushButtonRemoveFileName_clicked();
    void on_pushButtonLoadDXF_clicked();
    void on_toolButtonMoveDialog_clicked();
    void on_toolButtonExpandDialog_clicked();
    void on_toolButtonRotationDialog_clicked();
    void on_toolButtonShearDialog_clicked();

    void on_toolButtonMove_clicked();
    void on_toolButtonExpand_clicked();
	void on_toolButtonRotate_clicked();
    void on_toolButtonXShear_clicked();
    void on_toolButtonYShear_clicked();
    void on_toolButtonDrawInside_clicked();
    void on_toolButtonAutoMatching_clicked();
    void on_toolButtonFatLine_clicked();
    void on_toolButtonGenerateMask_clicked();
    void on_toolButtonLibraryMask_clicked();
    void on_toolButtonGenerateInspection_clicked();
    void on_toolButtonLibraryInspection_clicked();
    void on_toolButtonMirrorX_clicked();
    void on_toolButtonMirrorY_clicked();
    void on_tableWidgetLayerInfo_clicked(const QModelIndex &index);
    void on_toolButtonCenterize_clicked();

    void on_pushButtonAllocateColor_clicked();
    void on_toolButtonShowFilledArea_clicked();
    void on_toolButtonGenerateMaskFillArea_clicked();
    void on_toolButtonMakeEffectiveMask_clicked();
    void on_toolButtonSendEffectiveMask_clicked();

    void on_pushButtonSaveTransform_clicked();
    void on_pushButtonLoadTransform_clicked();

private:
    Ui::PropertyDXFOperationForm *ui;

	GUIFormBase	*GetImagePanel(void);
	void	RepaintImage(void);
	void	GetCenterDXF(double &MinX ,double &MinY ,double &MaxX ,double &MaxY);
	void	ShowLayerList(void);
	DXFOperationMode	GetCurrentOperationMode(void);
	void	LoadDXF(int FileNo,QByteArray &Data ,QString &FileName);
    void    PostLoadingDXF(void);
};

#endif // PROPERTYDXFOPERATIONFORM_H
