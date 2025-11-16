#ifndef EDITLIBRARYAUTOALIGNMENT_H
#define EDITLIBRARYAUTOALIGNMENT_H

#include <QDialog>
#include "ui_EditLibraryAutoAlignment.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "mtColorFrame.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XDataAlgorithm.h"
#include "XAutoAlignment.h"
#include "ShowRGBSamples.h"

class	GeneralLibFolderForm;

class EditLibraryAutoAlignment : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditLibraryAutoAlignment(LayersBase *Base,QWidget *parent = 0);
	~EditLibraryAutoAlignment();

	void	Initial(AlgorithmBase *InstBase);

private:
	Ui::EditLibraryAutoAlignmentClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	//AutoAlignmentLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibIDList;

	ShowRGBSpace		ColorThre;
	SelectColorSample	ColorSamples;
	ShowRGBSamples		RGBPanel;
	QColor PickupColor;
	mtColorFrame	PickupColorFrame;

	void ShowThresholdList(void);
	AutoAlignmentBase	*GetAutoAlignmentBase(void);
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_listWidgetEliminatedColor_doubleClicked(QModelIndex);
	void on_listWidgetBaseColor_doubleClicked(QModelIndex);
	void on_pushButtonEliminateColorArea_clicked();
	void on_pushButtonAddColorArea_clicked();
	void on_pushButtonAddAllColor_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButtonSubPickupColor_clicked();
	void on_pushButtonAddPickupColor_clicked();
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
	void	SlotAddEliminated(void);
	void	SlotDelEliminated(void);
};

#endif // EDITLIBRARYAUTOALIGNMENT_H
