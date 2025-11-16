#ifndef MANUALINPUTPROJECTEDINSPECTIONDIALOG_H
#define MANUALINPUTPROJECTEDINSPECTIONDIALOG_H

#include <QDialog>
#include "XProjectedInspection.h"
#include "XServiceForLayers.h"

namespace Ui {
class ManualInputProjectedInspectionDialog;
}
class	GeneralLibFolderForm;

class ManualInputProjectedInspectionDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int	SelectedLibID;
public:
    explicit ManualInputProjectedInspectionDialog(LayersBase *Base,QWidget *parent = 0);
    ~ManualInputProjectedInspectionDialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	ProjectedInspectionItem			*BItem;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::ManualInputProjectedInspectionDialog *ui;

	//ProjectedInspectionLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		ProjectedInspectionLibID;
};

#endif // MANUALINPUTPROJECTEDINSPECTIONDIALOG_H
