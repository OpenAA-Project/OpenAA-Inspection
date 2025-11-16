#ifndef SELECTALIGNMENTFLEXAREADIALOG_H
#define SELECTALIGNMENTFLEXAREADIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XAlignmentFlexArea.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectAlignmentFlexAreaDialog;
}
class	AlgorithmLibraryLevelContainer;
class	GeneralLibFolderForm;

class SelectAlignmentFlexAreaDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	int	SelectedLibID;

public:
    explicit SelectAlignmentFlexAreaDialog(LayersBase *Base,QWidget *parent = 0);
    ~SelectAlignmentFlexAreaDialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

	int				AlignmentFlexAreaLibID;

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectAlignmentFlexAreaDialog *ui;

	void	GetDataFromWindow(AlignmentFlexAreaItem &data);
	AlgorithmLibraryLevelContainer	*TempLib;

};

#endif // SELECTALIGNMENTFLEXAREADIALOG_H
