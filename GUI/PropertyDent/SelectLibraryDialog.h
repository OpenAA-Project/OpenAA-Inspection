#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include "XDentInspection.h"
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
    explicit SelectLibraryDialog(LayersBase *,QWidget *parent = 0);
    ~SelectLibraryDialog();

	int			SelectedLibID;
	QString		ItemName;
    
private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);

private:
    Ui::SelectLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
};

#endif // SELECTLIBRARYDIALOG_H
