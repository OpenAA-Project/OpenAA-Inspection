#ifndef PROPERTYALIGNMENTPROJECTIONFORM_H
#define PROPERTYALIGNMENTPROJECTIONFORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"
#include "ui_PropertyAlignmentProjectionForm.h"
#include "WMultiGrid.h"
#include "PropertyAlignmentProjectionPacket.h"
#include "XAlignmentProjection.h"

namespace Ui {
class PropertyAlignmentProjectionForm;
}

class PropertyAlignmentProjectionForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit PropertyAlignmentProjectionForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyAlignmentProjectionForm();

	AlignmentProjectionPointListPack		PointList;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
	virtual void	ShowInEdit	(void)	override;

	void	CreateAlignmentPoint(FlexArea &area ,int globalPage ,int PeakCount ,double Angle, int UsageLayer);
    
private slots:
    void on_tableWidgetPoint_doubleClicked(const QModelIndex &index);
	void on_tableWidgetPoint_clicked(const QModelIndex &MIndex);

private:
    Ui::PropertyAlignmentProjectionForm *ui;

	void	ShowPointList(void);

	AlignmentProjectionBase	*GetAlignmentProjectionBase(void);
};

#endif // PROPERTYALIGNMENTPROJECTIONFORM_H
