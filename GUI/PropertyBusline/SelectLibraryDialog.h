#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include "XBuslineInspection.h"
#include "XServiceForLayers.h"
#include "XDLLOnly.h"
#include "XDataAlgorithm.h"

namespace Ui {
class SelectLibraryDialog;
}

class	GeneralLibFolderForm;

class SelectLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectLibraryDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SelectLibraryDialog();
    
	void	Initial(AlgorithmBase *InstBase);
	int		SelectedID;

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

private:
    Ui::SelectLibraryDialog *ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//BuslineLibrary	*TempLib;
	AlgorithmLibraryLevelContainer *TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	AlgorithmLibraryListContainer	LibIDList;

	BuslineBase	*GetBuslineBase(void);
	AlgorithmLibraryListContainer	LibList;
};

#endif // SELECTLIBRARYDIALOG_H
