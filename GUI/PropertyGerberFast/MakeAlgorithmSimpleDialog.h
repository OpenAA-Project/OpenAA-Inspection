#ifndef MAKEALGORITHMSIMPLEDIALOG_H
#define MAKEALGORITHMSIMPLEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"

namespace Ui {
class MakeAlgorithmSimpleDialog;
}
class	GeneralLibFolderForm;
class	PropertyGerberFastForm;

class MakeAlgorithmSimpleDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	friend	class	PropertyGerberFastForm;

	int						BaseRow;
	PropertyGerberFastForm	*Parent;
	AlgoGenerationalContainer	MakeAlgoAllList;

public:
    explicit MakeAlgorithmSimpleDialog(AlgoGenerationalContainer &MakeAlgoAllList
									,int _BaseRow
									,PropertyGerberFastForm *hparent
									,LayersBase *base ,QWidget *parent = 0);
    ~MakeAlgorithmSimpleDialog();

private slots:
    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelectButton_clicked();
    void on_tableWidgetSelected_doubleClicked(const QModelIndex &index);
    void on_pushButtonUpdate_clicked();
    void on_pushButtonCancel_clicked();

	void	SlotSelectLibFolderSelect(int LibFolderID ,QString FolderName);
private:
    Ui::MakeAlgorithmSimpleDialog *ui;

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

#endif // MAKEALGORITHMSIMPLEDIALOG_H
