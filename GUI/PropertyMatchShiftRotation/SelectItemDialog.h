#ifndef SELECTITEMDIALOG_H
#define SELECTITEMDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XMatchShiftRotation.h"
#include "XServiceForLayers.h"
#include "XMatchShiftRotationLibrary.h"

namespace Ui {
class SelectItemDialog;
}
class	GeneralLibFolderForm;

class SelectItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int	SelectedLibID;
public:
    explicit SelectItemDialog(LayersBase *Base,QWidget *parent = 0);
    ~SelectItemDialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	QString			ItemName;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

    void on_ButtonDelete_clicked();

private:
    Ui::SelectItemDialog *ui;

	//MatchShiftRotationLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
public:
	int		MatchShiftRotationLibID;
};

#endif // SELECTITEMDIALOG_H
