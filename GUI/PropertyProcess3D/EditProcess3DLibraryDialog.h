#ifndef EDITPROCESS3DLIBRARYDIALOG_H
#define EDITPROCESS3DLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QToolButton>
#include <QWidget>
#include "XProcess3D.h"
#include "XProcess3DLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditProcess3DLibraryDialog;
}
class	GeneralLibFolderForm;

class EditProcess3DLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditProcess3DLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditProcess3DLibraryDialog();

	void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibUpdate_clicked();
    void on_pushButtonClose_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::EditProcess3DLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	//Process3DLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	Process3DBase	*GetProcess3DBase(void);
	AlgorithmLibraryListContainer	LibList;

	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITPROCESS3DLIBRARYDIALOG_H
