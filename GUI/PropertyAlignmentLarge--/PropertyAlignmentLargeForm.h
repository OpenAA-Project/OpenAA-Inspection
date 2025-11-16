#ifndef PROPERTYALIGNMENTLARGEFORM_H
#define PROPERTYALIGNMENTLARGEFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAlignmentLargeForm.h"
#include "WMultiGrid.h"
#include "PropertyAlignmentLargePacket.h"
#include "XAlignmentLarge.h"

namespace Ui {
class PropertyAlignmentLargeForm;
}

class	ImageControlTools;

class PropertyAlignmentLargeForm : public GUIFormBase
{
    Q_OBJECT
    
	ImageControlTools	*ImageControlToolsPointer;
public:
	ReqAlignmentLargeAreaListPack	AreaListFromMaster;
	AlignmentLargeAreaListPack		AreaList;
	AlignmentLargePointListPack		PointList;
	DoubleList		AngleList;

	explicit PropertyAlignmentLargeForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyAlignmentLargeForm();

	virtual void	ReadyParam(void)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	BuildForShow(void)	override;
	void	CreateAndShowPointGrid(void);
	virtual void	StartPage	(void)	override;
	virtual void	ShowInEdit	(void)	override;

	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)	override;

	void	CreateAlignmentArea(FlexArea &area);
	void	CreateAlignmentPoint(FlexArea &area ,int MoveDotX ,int MoveDotY
												,int MoveDotX2,int MoveDotY2);

	void	ClearAllAreas(void);
	void	ClearAllPoints(void);
	void	CreateAreaInMask(int Priority,int Erosion);
	void	AutoCreatePoint(int PointSize ,int SearchAreaDot,int SearchAreaDot2);
	void	SetAreaMode(void);
	void	SetPointMode(void);
	void	SelectAreaByPriority(int AreaPriority);
    
private slots:
    void on_toolButtonArea_clicked();
    void on_toolButtonPoint_clicked();
    void on_tableWidgetPoint_doubleClicked(const QModelIndex &index);
    void on_tableWidgetArea_doubleClicked(const QModelIndex &index);
    void on_tableWidgetArea_clicked(const QModelIndex &index);

    void on_pushButtonGrouping_clicked();
    void on_pushButtonUngrouping_clicked();
    void on_pushButtonCombination_clicked();

    void on_tableWidgetPoint_clicked(const QModelIndex &index);
    void on_pushButtonEditLibrary_clicked();
    void on_pushButtonSelectAll_clicked();
	void	SlotLayerButtonClicked(int newLayer);


    void on_comboBoxAngle_currentIndexChanged(int index);

private:
    Ui::PropertyAlignmentLargeForm *ui;

	void	ShowAreaGrid(void);
	void	ShowPointList(void);

	void	ShowPointGrid(AlignmentLargeAreaList *A);
	void	ShowPointGridRaw(void);
	void	CreatePointList(AlignmentLargeAreaList *A);
	GUIFormBase	*GetImageControlToolsPointer(void);

	AlignmentLargeBase	*GetAlignmentLargeBase(void);
	bool	GetUseBitBuffMode(void);
};

#endif // PROPERTYALIGNMENTLARGEFORM_H
