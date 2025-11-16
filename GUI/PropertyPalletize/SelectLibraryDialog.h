#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include "XPalletize.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLibraryDialog;
}
class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class SelectLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectLibraryDialog(LayersBase *,QWidget *parent = nullptr);
    ~SelectLibraryDialog();

    int	SelectedLibID;

private slots:
    void on_tableWidgetLibList_itemDoubleClicked(QTableWidgetItem *item);
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();
    void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::SelectLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
};

#endif // SELECTLIBRARYDIALOG_H
