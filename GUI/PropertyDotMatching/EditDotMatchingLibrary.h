#ifndef EDITDOTMATCHINGLIBRARY_H
#define EDITDOTMATCHINGLIBRARY_H

#include <QDialog>
#include <QModelIndex>
#include <QString>
#include "XDotMatching.h"
#include "XDotMatchingLibrary.h"
#include "XServiceForLayers.h"
#include <QToolButton>

namespace Ui {
class EditDotMatchingLibrary;
}
class	GeneralLibFolderForm;

class EditDotMatchingLibrary : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditDotMatchingLibrary(LayersBase *base ,QWidget *parent = 0);
    ~EditDotMatchingLibrary();

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//DotMatchingLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	DotMatchingBase	*GetDotMatchingBase(void);
	void		ShowSubtractList(DotMatchingLibrary &data);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_toolButtonPickup_clicked();
    void on_toolButtonInspect_clicked();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);

private:
    Ui::EditDotMatchingLibrary *ui;
};

#endif // EDITDOTMATCHINGLIBRARY_H
