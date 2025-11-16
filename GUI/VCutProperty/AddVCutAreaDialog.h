#ifndef ADDVCUTAREADIALOG_H
#define ADDVCUTAREADIALOG_H

#include <QDialog>
#include "ui_AddVCutAreaDialog.h"
#include "XServiceForLayers.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XVCutInspection.h"
#include "VCutImagePacket.h"

class	VCutInspectionBase;
class	VCutInspectionLibrary;
class	GeneralLibFolderForm;

class AddVCutAreaDialog : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	AddVCutAreaDialog(LayersBase *Base ,QWidget *parent = 0);
	~AddVCutAreaDialog();

	int		ThresholdShift;
	double	ThresholdLevel;
	int		ThresholdLength;
	int		SelectedLibID;
private:
	Ui::AddVCutAreaDialogClass ui;

	VCutInspectionBase	*GetVCutInspectionBase(void);

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//VCutInspectionLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;

	AlgorithmLibraryListContainer	LibList;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(void);

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonGenerateLib_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
};

#endif // ADDVCUTAREADIALOG_H
