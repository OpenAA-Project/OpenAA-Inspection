#ifndef EDITCOLORDIFFERENCELIBRARYDIALOG_H
#define EDITCOLORDIFFERENCELIBRARYDIALOG_H

#include <QDialog>
#include "XColorDifference.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditColorDifferenceLibraryDialog;
}

class	GeneralLibFolderForm;

class	ColorDifferenceLibrary;
class	AlgorithmLibraryLevelContainer;

class EditColorDifferenceLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditColorDifferenceLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditColorDifferenceLibraryDialog();
 
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	bool	OnChanging;

	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	ColorDifferenceBase	*GetColorDifferenceBase(void);
	AlgorithmLibraryListContainer	LibList;

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);

private:
    Ui::EditColorDifferenceLibraryDialog *ui;
};

#endif // EDITCOLORDIFFERENCELIBRARYDIALOG_H
