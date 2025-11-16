#ifndef EDITLIBRARYDIALOG_H
#define EDITLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XMatchShiftRotation.h"
#include "XMatchShiftRotationLibrary.h"
#include "XServiceForLayers.h"
#include <QToolButton>

namespace Ui {
class EditLibraryDialog;
}
class	GeneralLibFolderForm;

class EditLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditLibraryDialog();

	void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonClose_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

private:
    Ui::EditLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	//MatchShiftRotationLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	MatchShiftRotationBase	*GetMatchShiftRotationBase(void);
	AlgorithmLibraryListContainer	LibList;

	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITLIBRARYDIALOG_H
