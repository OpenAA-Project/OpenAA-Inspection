#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XGerberAperture.h"
#include "XGerberFastLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLibraryDialog;
}
class	GeneralLibFolderForm;
class	GerberFastBase;

class SelectLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectLibraryDialog();

	void	SetLibID(int LibID);
	int	SelectedLibID;
private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
    void on_ButtonClear_clicked();
    void on_pushButtonEditLibrary_clicked();

private:
    Ui::SelectLibraryDialog *ui;
	GerberFastBase	*GetGerberFastBase(void);
	GeneralLibFolderForm		*pLibFolderForm;
	//GerberFastLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int					LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	void	ShowDataToWindow(AlgorithmLibraryLevelContainer *Attr);
};

#endif // SELECTLIBRARYDIALOG_H
