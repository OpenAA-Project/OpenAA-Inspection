#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XNickInspection.h"
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

	//NickInspectionLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	AlgorithmLibraryListContainer	LibIDList;

	NickInspectionBase	*GetNickInspectionBase(void);
	AlgorithmLibraryListContainer	LibList;

	void ShowLibraries(AlgorithmLibraryListContainer &Libraries);
};

#endif // SELECTLIBRARYDIALOG_H
