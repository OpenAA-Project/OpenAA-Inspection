#ifndef EDITRASTERLIBRARYDIALOG_H
#define EDITRASTERLIBRARYDIALOG_H

#include <QDialog>
#include <QString>
#include <QModelIndex>
#include <QToolButton>
#include "XRaster.h"
#include "XRasterLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditRasterLibraryDialog;
}
class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class EditRasterLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditRasterLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditRasterLibraryDialog();
    
	void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibUpdate_clicked();
    void on_tableWidgetLibList_itemSelectionChanged();
    void on_pushButtonClose_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void	SlotSelectLibFolderSelect(int LibFolderID ,QString FolderName);

    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelectButton_clicked();
    void on_tableWidgetSelected_doubleClicked(const QModelIndex &index);
    void on_toolButtonStatic_clicked();
    void on_toolButtonEdgeIn_clicked();
    void on_toolButtonEdgeOut_clicked();

private:
    Ui::EditRasterLibraryDialog *ui;

	GeneralLibFolderForm			*pLibFolderForm;
	int								LibFolderID;
	AlgorithmLibraryLevelContainer	*LLib;
	//AlgorithmLibraryListContainer	LibIDList;
	int								LibType;
	AlgorithmLibraryListContainer	LibList;

	GeneralLibFolderForm			*pLibFolderSelect;
	int								CurrentLibType;
	int								CurrentLibFolderID;
	AlgorithmLibraryListContainer	LibIDListSelect;
	AlgorithmLibraryListContainer	LimitedLibrariesStatic;
	AlgorithmLibraryListContainer	LimitedLibrariesInsideEdge;
	AlgorithmLibraryListContainer	LimitedLibrariesOutsideEdge;


	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	SetLibTypeInComboBox(void);
	void	ShowFolder(int LibType);
	void	ShowTableSelect(void);

	void ShowThresholdList(void);
	RasterBase	*GetRasterBase(void);
};

#endif // EDITRASTERLIBRARYDIALOG_H
