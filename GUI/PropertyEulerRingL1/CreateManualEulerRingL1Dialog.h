#ifndef CREATEMANUALEULERRINGL1DIALOG_H
#define CREATEMANUALEULERRINGL1DIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XEulerRingL1.h"
#include "XServiceForLayers.h"
#include "XEulerRingL1Library.h"

namespace Ui {
class CreateManualEulerRingL1Dialog;
}
class	GeneralLibFolderForm;

class CreateManualEulerRingL1Dialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	int	SelectedLibID;

public:
    explicit CreateManualEulerRingL1Dialog(LayersBase *Base,QWidget *parent = 0);
    ~CreateManualEulerRingL1Dialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	EulerRingL1Item			*BItem;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

private:
    Ui::CreateManualEulerRingL1Dialog *ui;

	//EulerRingL1Library	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		EulerRingL1LibID;
};

#endif // CREATEMANUALEULERRINGL1DIALOG_H
