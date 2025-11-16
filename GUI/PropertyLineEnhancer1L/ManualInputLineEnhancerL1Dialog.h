#ifndef MANUALINPUTLINEENHANCERL1DIALOG_H
#define MANUALINPUTLINEENHANCERL1DIALOG_H

#include <QDialog>
#include "XLineEnhancer1L.h"
#include "XServiceForLayers.h"

namespace Ui {
class ManualInputLineEnhancerL1Dialog;
}
class	GeneralLibFolderForm;

class ManualInputLineEnhancerL1Dialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	int	SelectedLibID;

public:
    explicit ManualInputLineEnhancerL1Dialog(LayersBase *Base,QWidget *parent = 0);
    ~ManualInputLineEnhancerL1Dialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	LineEnhancer1LItem			*BItem;

	void	Reflect(void);

private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::ManualInputLineEnhancerL1Dialog *ui;

	//LineEnhancer1LLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int		LineEnhancer1LLibID;
};

#endif // MANUALINPUTLINEENHANCERL1DIALOG_H
