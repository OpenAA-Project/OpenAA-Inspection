#ifndef EDITLIBRARYDIALOG_H
#define EDITLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QToolButton>
#include <QString>
#include "XThinMetal.h"
#include "XThinMetalLibrary.h"
#include "XServiceForLayers.h"
#include <QModelIndex>
#include <QToolButton>

namespace Ui {
class EditLibraryDialog;
}

class	ThinMetalLibrary;
class	AlgorithmLibraryLevelContainer;
class	GeneralLibFolderForm;

class EditLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditLibraryDialog();

	enum	KindOfSort
	{
		KOS_ID_Up
		,KOS_ID_Dn
		,KOS_Name_Up
		,KOS_Name_Dn
	}LibSortType;

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
	void	MListSectionClicked ( int logicalIndex );

private:
    Ui::EditLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);

	ThinMetalBase		*GetThinMetalBase(void);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITLIBRARYDIALOG_H
