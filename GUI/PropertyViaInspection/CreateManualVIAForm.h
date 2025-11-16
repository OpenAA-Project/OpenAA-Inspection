#ifndef CREATEMANUALVIAFORM_H
#define CREATEMANUALVIAFORM_H

#include <QDialog>
#include "XViaInspection.h"
#include "XServiceForLayers.h"

namespace Ui {
class CreateManualVIAForm;
}
class	GeneralLibFolderForm;
class	VIALibrary;

class CreateManualVIAForm : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
 	int	SelectedLibID;   
public:
    explicit CreateManualVIAForm(LayersBase *Base,QWidget *parent = 0);
    ~CreateManualVIAForm();
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	VIAItem			*BItem;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::CreateManualVIAForm *ui;

	void	GetDataFromWindow(VIAItem &data);
	//VIALibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int				VIALibID;
};

#endif // CREATEMANUALVIAFORM_H
