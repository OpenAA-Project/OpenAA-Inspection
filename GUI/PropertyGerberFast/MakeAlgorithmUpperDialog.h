#ifndef MAKEALGORITHMUPPERDIALOG_H
#define MAKEALGORITHMUPPERDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"

namespace Ui {
class MakeAlgorithmUpperDialog;
}
class	GeneralLibFolderForm;
class	PropertyGerberFastForm;

class MakeAlgorithmUpperDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	friend	class	PropertyGerberFastForm;

	PropertyGerberFastForm	*Parent;
	AlgoGenerationalContainer	MakeAlgoAllList;
public:
    explicit MakeAlgorithmUpperDialog(AlgoGenerationalContainer &MakeAlgoAllList
									,PropertyGerberFastForm *hparent
									,LayersBase *base ,QWidget *parent = 0);
    ~MakeAlgorithmUpperDialog();

private slots:
    void on_tableWidgetCrossedLayer_clicked(const QModelIndex &index);
    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelectButton_clicked();
    void on_tableWidgetSelected_doubleClicked(const QModelIndex &index);
    void on_pushButtonUpdate_clicked();
    void on_pushButtonClose_clicked();
	void	SlotSelectLibFolderSelect(int LibFolderID ,QString FolderName);
private:
    Ui::MakeAlgorithmUpperDialog *ui;

	GeneralLibFolderForm			*pLibFolderSelect;
	int								CurrentLibType;
	int								CurrentLibFolderID;
	AlgorithmLibraryListContainer	LibIDListSelect;
	AlgorithmLibraryListContainer	Libraries;

	void	SetLibTypeInComboBox(void);
	void	ShowFolder(int LibType);
	void	ShowSelectedList(void);
	void	ShowLibraries(void);
	void	ShowLibrariesCount(void);
};

#endif // MAKEALGORITHMUPPERDIALOG_H
