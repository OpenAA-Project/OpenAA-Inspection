#ifndef EDITEULERRINGL1LIBRARYDIALOG_H
#define EDITEULERRINGL1LIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QToolButton>
#include "XEulerRingL1.h"
#include "XEulerRingL1Library.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditEulerRingL1LibraryDialog;
}
class	GeneralLibFolderForm;

class EditEulerRingL1LibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditEulerRingL1LibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditEulerRingL1LibraryDialog();

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
    Ui::EditEulerRingL1LibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	//EulerRingL1Library	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	EulerRingL1Base	*GetEulerRingL1Base(void);
	AlgorithmLibraryListContainer	LibList;

	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITEULERRINGL1LIBRARYDIALOG_H
