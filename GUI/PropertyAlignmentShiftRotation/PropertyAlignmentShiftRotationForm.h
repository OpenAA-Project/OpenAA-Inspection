#ifndef PROPERTYALIGNMENTSHIFTROTATIONFORM_H
#define PROPERTYALIGNMENTSHIFTROTATIONFORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"
#include "ui_PropertyAlignmentShiftRotationForm.h"
#include "WMultiGrid.h"
#include "XPropertyAlignmentShiftRotationPacket.h"
#include "XAlignmentShiftRotation.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyAlignmentShiftRotationForm;
}


class PropertyAlignmentShiftRotationForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyAlignmentShiftRotationForm(LayersBase *Base,QWidget *parent = nullptr);
    ~PropertyAlignmentShiftRotationForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
	virtual void	ShowInEdit	(void)	override;

private slots:
    void on_toolButtonAlignmentShiftRotationItem_clicked();
    void on_toolButtonVHLineGroup_clicked();
    void on_comboBoxAngle_currentIndexChanged(int index);
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_cellDoubleClicked(int row, int column);
    void on_tableWidgetGeneratedLibList_cellDoubleClicked(int row, int column);
    void on_pushButtonEditLibrary_clicked();
    void on_tableWidgetItemList_itemSelectionChanged();
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();

private:
    Ui::PropertyAlignmentShiftRotationForm *ui;

    AlignmentShiftRotationBase	*GetAlignmentShiftRotationBase(void);

    virtual void	SetLibFolder(int _LibFolderID ,const QString &LinFolderName)    override;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);

	AlignmentShiftRotationItemListPack	ItemList;
	void	ShowItemList(void);

};

#endif // PROPERTYALIGNMENTSHIFTROTATIONFORM_H
