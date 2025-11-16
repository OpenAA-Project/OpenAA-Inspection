#ifndef CREATEMANUALITEMFORM_H
#define CREATEMANUALITEMFORM_H

#include <QDialog>
#include "ui_CreateManualItemForm.h"
#include "XServiceForLayers.h"
#include "XMeasureHolePos.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "XDLLOnly.h"
#include "SelectColorSample.h"

class	GeneralLibFolderForm;

class CreateManualItemForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	int	SelectedLibID;

public:
	CreateManualItemForm(LayersBase *Base ,QWidget *parent = 0);
	~CreateManualItemForm();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	MeasureHolePosItem			*BItem;

	void	Reflect(void);

private:
	Ui::CreateManualItemFormClass ui;

	//MeasureHolePosLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int					LibID;

	ShowRGBSpace		ColorGenerator;
	SelectColorSample	ColorSamples;
	void	GetDataFromWindow(MeasureHolePosItem &data);

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void on_pushButtonNColor_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // CREATEMANUALITEMFORM_H
