#ifndef SELECTALIGNMENTLARGEDIALOG_H
#define SELECTALIGNMENTLARGEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QToolButton>
#include "XAlignmentLarge.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectAlignmentLargeDialog;
}

class	GeneralLibFolderForm;

class SelectAlignmentLargeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    int	SelectedLibID;
public:
    explicit SelectAlignmentLargeDialog(LayersBase *Base,QWidget *parent = 0);
    ~SelectAlignmentLargeDialog();

 	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

	int				AlignmentLargeLibID;   
private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::SelectAlignmentLargeDialog *ui;

	void	GetDataFromWindow(XAlignmentLarge &data);
	AlgorithmLibraryLevelContainer	*TempLib;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // SELECTALIGNMENTLARGEDIALOG_H
