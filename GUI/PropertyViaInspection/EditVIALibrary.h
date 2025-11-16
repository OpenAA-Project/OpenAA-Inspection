#ifndef EDITVIALIBRARY_H
#define EDITVIALIBRARY_H

#include <QDialog>
#include <QModelIndex>
#include <QToolButton>
#include <QString>
#include "XViaInspection.h"
#include "XViaInspectionLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditVIALibrary;
}
class	GeneralLibFolderForm;
class	VIALibrary;

class EditVIALibrary : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditVIALibrary(LayersBase *base ,QWidget *parent = 0);
    ~EditVIALibrary();

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
    Ui::EditVIALibrary *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//VIALibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);

	VIABase		*GetVIABase(void);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // EDITVIALIBRARY_H
