#ifndef EDITHOLEWALLINSPECTIONDIALOG_H
#define EDITHOLEWALLINSPECTIONDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QToolButton>
#include "XHoleWallInspection.h"
#include "XHoleWallLibrary.h"
#include "XServiceForLayers.h"


namespace Ui {
class EditHoleWallInspectionDialog;
}
class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class EditHoleWallInspectionDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditHoleWallInspectionDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditHoleWallInspectionDialog();

	void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_toolButtonPickup_clicked();
    void on_toolButtonInspect_clicked();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonClose_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::EditHoleWallInspectionDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	HoleWallBase	*GetHoleWallBase(void);
	AlgorithmLibraryListContainer	LibList;

	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITHOLEWALLINSPECTIONDIALOG_H
