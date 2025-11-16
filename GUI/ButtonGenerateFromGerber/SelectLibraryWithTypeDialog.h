#ifndef SELECTLIBRARYWITHTYPEDIALOG_H
#define SELECTLIBRARYWITHTYPEDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLibraryWithTypeDialog;
}

class	GerberFastBase;
class	GeneralLibFolderForm;

class SelectLibraryWithTypeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectLibraryWithTypeDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectLibraryWithTypeDialog();

	int								CurrentLibType;
	int								SelectedLibID;

	void	Initial(void);

private slots:
    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
	void	SlotSelectLibFolderSelect(int LibFolderID ,QString FolderName);
private:
    Ui::SelectLibraryWithTypeDialog *ui;

	GeneralLibFolderForm			*pLibFolderSelect;
	AlgorithmLibraryListContainer	LibIDListSelect;
	int								CurrentLibFolderID;

	void	SetLibTypeInComboBox(void);
	void	ShowFolder(int LibType);
	void	ShowSelectedList(void);

	GerberFastBase	*GetGerberFastBase(void);

};

#endif // SELECTLIBRARYWITHTYPEDIALOG_H
