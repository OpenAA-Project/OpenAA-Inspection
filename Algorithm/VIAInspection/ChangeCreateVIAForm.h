#ifndef CHANGECREATEVIAFORM_H
#define CHANGECREATEVIAFORM_H

#include <QDialog>
#include "XViaInspection.h"
#include "XViaInspectionLibrary.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;
namespace Ui {
class ChangeCreateVIAForm;
}

class ChangeCreateVIAForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit ChangeCreateVIAForm(VIABase *base ,QWidget *parent = 0);
    ~ChangeCreateVIAForm();
    
	VIABase					*Base;
	AlgorithmLibraryLevelContainer	*TempLib;
	VIAItem					ResultVIA;
	GeneralLibFolderForm	*pLibFolderForm;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetItemFromWindow(VIAItem &data);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::ChangeCreateVIAForm *ui;
};

#endif // CHANGECREATEVIAFORM_H
