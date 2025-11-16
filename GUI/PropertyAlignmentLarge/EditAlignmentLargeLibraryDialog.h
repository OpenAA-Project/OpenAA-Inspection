#ifndef EDITALIGNMENTLARGELIBRARYDIALOG_H
#define EDITALIGNMENTLARGELIBRARYDIALOG_H

#include <QDialog>
#include <QDialog>
#include <QModelIndex>
#include <QToolButton>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XAlignmentLarge.h"

namespace Ui {
class EditAlignmentLargeLibraryDialog;
}

class GeneralLibFolderForm;

class EditAlignmentLargeLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditAlignmentLargeLibraryDialog(LayersBase *Base ,QWidget *parent = 0);
    ~EditAlignmentLargeLibraryDialog();
    
	void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonClose_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void	SlotDrop(int FolderParentID ,int LibFolderID , QWidget *w);

private:
    Ui::EditAlignmentLargeLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	AlignmentLargeBase	*GetAlignmentLargeBase(void);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITALIGNMENTLARGELIBRARYDIALOG_H
