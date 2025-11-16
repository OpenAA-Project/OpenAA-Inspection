#ifndef EDITLIBRARYDIALOG_H
#define EDITLIBRARYDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include "XRasterInspection.h"
#include "XRasterInspectionLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditLibraryDialog;
}
class	GeneralLibFolderForm;
class	RasterInspectionBase;
class	AlgorithmLibraryLevelContainer;


class EditLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	bool	OnChanging;

	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;

public:
    explicit EditLibraryDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~EditLibraryDialog();

private slots:
    void on_tableWidgetLibList_itemSelectionChanged();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::EditLibraryDialog *ui;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	RasterInspectionBase	*GetRasterInspectionBase(void);
	AlgorithmLibraryListContainer	LibList;
};

#endif // EDITLIBRARYDIALOG_H
