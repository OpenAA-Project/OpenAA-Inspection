#ifndef SELECTHOLEWALLLIBRARYFORM_H
#define SELECTHOLEWALLLIBRARYFORM_H

#include <QDialog>
#include "XHoleWallInspection.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectHoleWallLibraryForm;
}
class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class SelectHoleWallLibraryForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectHoleWallLibraryForm(LayersBase *,QWidget *parent = 0);
    ~SelectHoleWallLibraryForm();

	int	SelectedLibID;

private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::SelectHoleWallLibraryForm *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
};

#endif // SELECTHOLEWALLLIBRARYFORM_H
