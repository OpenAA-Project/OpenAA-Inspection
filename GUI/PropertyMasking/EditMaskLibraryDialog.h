#ifndef EDITMASKLIBRARYDIALOG_H
#define EDITMASKLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditMaskLibraryDialog;
}

class	GeneralLibFolderForm;
class	MaskingLibrary;
class	MaskingBase;
class	AlgorithmLibraryLevelContainer;

class EditMaskLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditMaskLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditMaskLibraryDialog();

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelectButton_clicked();
    void on_tableWidgetSelected_doubleClicked(const QModelIndex &index);
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonColor_clicked();

	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
	void	SlotSelectLibFolderSelect(int LibFolderID ,QString FolderName);



    void on_radioButtonEffective_clicked();

    void on_radioButtonIneffective_clicked();

    void on_radioButtonLimitedEffective_clicked();

    void on_radioButtonLimitedIneffective_clicked();

private:
    Ui::EditMaskLibraryDialog *ui;

	GeneralLibFolderForm			*pLibFolder;
	int								LibFolderID;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmLibraryLevelContainer	*LLib;

	GeneralLibFolderForm			*pLibFolderSelect;
	int								CurrentLibType;
	int								CurrentLibFolderID;
	AlgorithmLibraryListContainer	LibIDListSelect;
	AlgorithmLibraryListContainer	LimitedLibraries;

	MaskingBase	*GetMaskingBase(void);
	void	SetLibTypeInComboBox(void);
	void	ShowFolder(int LibType);
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	LibNewFunc(void);
	void	ShowTableSelect(void);
};

#endif // EDITMASKLIBRARYDIALOG_H
