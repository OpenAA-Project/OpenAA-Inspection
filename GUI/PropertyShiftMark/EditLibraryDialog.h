#ifndef EditLibraryDIALOG_H
#define EditLibraryDIALOG_H

#include <QDialog>
#include <QString>
#include <QModelIndex>
#include <QToolButton>
#include "XShiftMark.h"
#include "XShiftMarkLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditLibraryDialog;
}
class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class EditLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditLibraryDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~EditLibraryDialog();

    void	Initial(AlgorithmBase *InstBase);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibUpdate_clicked();
    void on_pushButtonClose_clicked();
    void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

private:
    Ui::EditLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	ShiftMarkBase	*GetShiftMarkBase(void);
	AlgorithmLibraryListContainer	LibList;
};

#endif // EditLibraryDIALOG_H
