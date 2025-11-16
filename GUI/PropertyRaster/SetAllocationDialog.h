#ifndef SETALLOCATIONDIALOG_H
#define SETALLOCATIONDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SetAllocationDialog;
}
class	GeneralLibFolderForm;
class	RasterBase;
class	AlgorithmLibraryLevelContainer;

class SetAllocationDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SetAllocationDialog(bool NewMode,LayersBase *base ,QWidget *parent = 0);
    ~SetAllocationDialog();

	void	Set(int ShrinkDot
				,int InsideEdgeWidth
				,int OutsideEdgeWidth
				,AlgorithmLibraryListContainer &AllocatedStaticLib
				,AlgorithmLibraryListContainer &AllocatedInsideEdgeLib
				,AlgorithmLibraryListContainer &AllocatedOutsideEdgeLib);
    
	//AlgorithmLibraryListContainer	LimitedLibraries;
	int			LibID;
	int			ShrinkDot;
	int			InsideEdgeWidth;
	int			OutsideEdgeWidth;
	AlgorithmLibraryListContainer	LimitedLibrariesStatic		;
	AlgorithmLibraryListContainer	LimitedLibrariesInsideEdge	;
	AlgorithmLibraryListContainer	LimitedLibrariesOutsideEdge	;

private slots:
    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelectButton_clicked();
    void on_tableWidgetSelected_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void	SlotSelectLibFolderSelect(int LibFolderID ,QString FolderName);

    void on_toolButtonStatic_clicked();
    void on_toolButtonEdgeIn_clicked();
    void on_toolButtonEdgeOut_clicked();
    void on_tableWidgetLibList_itemSelectionChanged();

private:
    Ui::SetAllocationDialog *ui;

	GeneralLibFolderForm			*pLibFolderForm;
	int								LibFolderID;
	AlgorithmLibraryLevelContainer	*LLib;
	int								LibType;
	AlgorithmLibraryListContainer	LibList;

	GeneralLibFolderForm			*pLibFolderSelect;
	int								CurrentLibType;
	int								CurrentLibFolderID;
	AlgorithmLibraryListContainer	LibIDListSelect;

	void	ShowFolder(int LibType);
	void	SetLibTypeInComboBox(void);
	void	ShowTableSelect(void);

	RasterBase	*GetRasterBase(void);
};

#endif // SETALLOCATIONDIALOG_H
