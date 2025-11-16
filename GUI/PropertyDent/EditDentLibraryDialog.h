#ifndef EDITDENTLIBRARYDIALOG_H
#define EDITDENTLIBRARYDIALOG_H

#include <QDialog>
#include <QString>
#include <QModelIndex>
#include <QToolButton>
#include "XDentInspection.h"
#include "XDentLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditDentLibraryDialog;
}
class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class EditDentLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	QList<QToolButton *>	LayerGenButtons;
public:
    explicit EditDentLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditDentLibraryDialog();
    
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
    Ui::EditDentLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	DentBase	*GetDentBase(void);
	AlgorithmLibraryListContainer	LibList;
};

#endif // EDITDENTLIBRARYDIALOG_H
