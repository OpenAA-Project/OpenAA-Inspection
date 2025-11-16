#ifndef EDITDYNAMICCLASSIFYLIBRARY_H
#define EDITDYNAMICCLASSIFYLIBRARY_H

#include <QDialog>
#include "ui_EditDynamicClassifyLibrary.h"
#include "XDynamicClassify.h"
#include "XServiceForLayers.h"
#include "ShowRGBCube.h"

class	GeneralLibFolderForm;

class EditDynamicClassifyLibrary : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EditDynamicClassifyLibrary(LayersBase *base ,QWidget *parent = 0);
	~EditDynamicClassifyLibrary();

private:
	Ui::EditDynamicClassifyLibraryClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//DynamicClassifyLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	DynamicClassifyBase	*GetDynamicClassifyBase(void);
	void		ShowSubtractList(DynamicClassifyLibrary &data);
	AlgorithmLibraryListContainer	LibList;

	ShowRGBSpace	PickupColor;

private slots:
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void on_pushButtonClose_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
};

#endif // EDITDYNAMICCLASSIFYLIBRARY_H
