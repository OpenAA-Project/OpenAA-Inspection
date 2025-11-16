#ifndef EDITLIBRARYDIALOG_H
#define EDITLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QToolButton>
#include <QString>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XLinePatternInspection.h"

namespace Ui {
class EditLibraryDialog;
}
class	GeneralLibFolderForm;

class EditLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditLibraryDialog(LayersBase *Base ,QWidget *parent = 0);
    ~EditLibraryDialog();

	void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonAddSubtractLib_clicked();
    void on_ButtonDelSubtractLib_clicked();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_toolButtonPickup_clicked();

    void on_toolButtonInspect_clicked();

private:
    Ui::EditLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	//LinePatternLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowSubtractList(LinePatternLibrary &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	LinePatternBase	*GetLinePatternBase(void);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITLIBRARYDIALOG_H
