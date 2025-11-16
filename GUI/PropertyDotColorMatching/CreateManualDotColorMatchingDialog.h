#ifndef CREATEMANUALDOTCOLORMATCHINGDIALOG_H
#define CREATEMANUALDOTCOLORMATCHINGDIALOG_H

#include <QDialog>
#include "XDotColorMatching.h"
#include "XServiceForLayers.h"

namespace Ui {
class CreateManualDotColorMatchingDialog;
}
class	GeneralLibFolderForm;
class AlgorithmLibraryLevelContainer;

class CreateManualDotColorMatchingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	int	SelectedLibID;

public:
    explicit CreateManualDotColorMatchingDialog(LayersBase *Base,QWidget *parent = 0);
    ~CreateManualDotColorMatchingDialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	DotColorMatchingItem			*BItem;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_toolButtonBroad_clicked();

    void on_toolButtonNarrow_clicked();

private:
    Ui::CreateManualDotColorMatchingDialog *ui;

	void	GetDataFromWindow(DotColorMatchingItem &data);
	AlgorithmLibraryLevelContainer	*LLib;
	int				DotColorMatchingLibID;
};

#endif // CREATEMANUALDOTCOLORMATCHINGDIALOG_H
