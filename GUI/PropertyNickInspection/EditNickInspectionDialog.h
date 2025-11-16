#ifndef EDITNICKINSPECTIONDIALOG_H
#define EDITNICKINSPECTIONDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XNickInspection.h"
#include <QToolButton>

namespace Ui {
class EditNickInspectionDialog;
}
class	GeneralLibFolderForm;

class EditNickInspectionDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditNickInspectionDialog(LayersBase *Base ,QWidget *parent = 0);
    ~EditNickInspectionDialog();

	void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelectButton_clicked();
    void on_tableWidgetSelected_doubleClicked(const QModelIndex &index);
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonClose_clicked();

	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void	SlotSelectLibFolderSelect(int libFolderID ,QString FolderName);
private:
    Ui::EditNickInspectionDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	//NickInspectionLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	NickInspectionBase	*GetNickInspectionBase(void);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;

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

#endif // EDITNICKINSPECTIONDIALOG_H
