#ifndef EDITLIBRARYCOLOR_H
#define EDITLIBRARYCOLOR_H

#include <QDialog>
#include "ui_EditLibraryColor.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "mtColorFrame.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XDataAlgorithm.h"
#include "XLineEnhancer.h"
#include "ShowRGBSamples.h"

class	GeneralLibFolderForm;

class EditLibraryColor : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditLibraryColor(LayersBase *Base,QWidget *parent = 0);
	~EditLibraryColor();

	void	Initial(AlgorithmBase *InstBase);

private:
	Ui::EditLibraryColorClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	//LineEnhancerLibrary	*TempLib;
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
	LineEnhancerBase	*GetLineEnhancerBase(void);

	AlgorithmLibraryListContainer	LibList;

private slots:
	void	SlotAddEliminated(void);
	void	SlotDelEliminated(void);
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButtonAddAllColor_clicked();
	void on_listWidgetEliminatedColor_doubleClicked(QModelIndex);
	void on_listWidgetBaseColor_doubleClicked(QModelIndex);
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void on_pushButtonSubPickupColor_clicked();
	void on_pushButtonAddPickupColor_clicked();
	void on_pushButtonEliminateColorArea_clicked();
	void on_pushButtonAddColorArea_clicked();
};

#endif // EDITLIBRARYCOLOR_H
