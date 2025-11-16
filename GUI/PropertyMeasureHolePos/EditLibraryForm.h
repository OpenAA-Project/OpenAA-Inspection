#ifndef EDITLIBRARYFORM_H
#define EDITLIBRARYFORM_H

#include <QDialog>
#include "ui_EditLibraryForm.h"
#include "XMeasureHolePos.h"
#include "XServiceForLayers.h"
#include "ShowRGBCube.h"
#include "XColorSpace.h"
#include "XDLLOnly.h"
#include "SelectColorSample.h"
#include "XDataAlgorithm.h"

class	GeneralLibFolderForm;

class EditLibraryForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditLibraryForm(LayersBase *Base ,QWidget *parent = 0);
	~EditLibraryForm();

	void	Initial(AlgorithmBase *InstBase);
private:
	Ui::EditLibraryFormClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//MeasureHolePosLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	AlgorithmLibraryListContainer	LibIDList;

	MeasureHolePosBase	*GetMeasureHolePosBase(void);
	void		ShowSubtractList(MeasureHolePosLibrary &data);
	AlgorithmLibraryListContainer	LibList;

	ShowRGBSpace	HoleColor;


private slots:
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButtonNColor_clicked();
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // EDITLIBRARYFORM_H
