#ifndef EDITMULTISPECTRALLIBRARYDIALOG_H
#define EDITMULTISPECTRALLIBRARYDIALOG_H

#include <QDialog>
#include <QString>
#include <QModelIndex>
#include <QToolButton>
#include "XMultiSpectral.h"
#include "XMultiSpectralLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditMultiSpectralLibraryDialog;
}
class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class EditMultiSpectralLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditMultiSpectralLibraryDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~EditMultiSpectralLibraryDialog();

    void	Initial(AlgorithmBase *InstBase);
private slots:
    void on_tableWidgetLibList_itemSelectionChanged();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
    void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

private:
    Ui::EditMultiSpectralLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	MultiSpectralBase	*GetMultiSpectralBase(void);
	AlgorithmLibraryListContainer	LibList;
};

#endif // EDITMULTISPECTRALLIBRARYDIALOG_H
