#ifndef CREATEMANUALThinMetalFORM_H
#define CREATEMANUALThinMetalFORM_H

#include <QDialog>
#include "XThinMetal.h"
#include "XServiceForLayers.h"

namespace Ui {
class CreateManualThinMetalForm;
}
class	GeneralLibFolderForm;
class	ThinMetalLibrary;
class	AlgorithmLibraryLevelContainer;

class CreateManualThinMetalForm : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
 	int	SelectedLibID;   
public:
    explicit CreateManualThinMetalForm(LayersBase *Base,QWidget *parent = 0);
    ~CreateManualThinMetalForm();
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	ThinMetalItem			*BItem;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::CreateManualThinMetalForm *ui;

	void	GetDataFromWindow(ThinMetalItem &data);
	AlgorithmLibraryLevelContainer	*LLib;
	int				ThinMetalLibID;
};

#endif // CREATEMANUALThinMetalFORM_H
