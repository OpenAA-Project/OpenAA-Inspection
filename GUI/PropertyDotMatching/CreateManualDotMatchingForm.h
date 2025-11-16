#ifndef CREATEMANUALDOTMATCHINGFORM_H
#define CREATEMANUALDOTMATCHINGFORM_H

#include <QDialog>
#include "XDotMatching.h"
#include "XServiceForLayers.h"

namespace Ui {
class CreateManualDotMatchingForm;
}

class	GeneralLibFolderForm;

class CreateManualDotMatchingForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    int	SelectedLibID;

public:
    explicit CreateManualDotMatchingForm(LayersBase *Base,QWidget *parent = 0);
    ~CreateManualDotMatchingForm();
	
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	DotMatchingItem			*BItem;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::CreateManualDotMatchingForm *ui;

	void	GetDataFromWindow(DotMatchingItem &data);
	//DotMatchingLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int				DotMatchingLibID;
};

#endif // CREATEMANUALDOTMATCHINGFORM_H
