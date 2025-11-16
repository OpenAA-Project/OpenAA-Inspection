#ifndef EDITLIBRARYMONO_H
#define EDITLIBRARYMONO_H

#include <QDialog>
#include "ui_EditLibraryMono.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XAutoAlignment.h"

class	GeneralLibFolderForm;

class EditLibraryMono : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditLibraryMono(LayersBase *Base,QWidget *parent = 0);
	~EditLibraryMono();

	void	Initial(AlgorithmBase *InstBase);

private:
	Ui::EditLibraryMonoClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	//AutoAlignmentLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	void ShowThresholdList(void);
	AutoAlignmentBase	*GetAutoAlignmentBase(void);
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITLIBRARYMONO_H
