#ifndef VCUTIMAGEPROPERTYFORM_H
#define VCUTIMAGEPROPERTYFORM_H


#include "ui_VCutImagePropertyForm.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XVCutInspection.h"
#include "VCutImagePacket.h"
#include "XStandardPropertyForm.h"

class	GeneralLibFolderForm;

class VCutImagePropertyForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT
	VCutInspectionListForPacketPack	VCutInfo;
public:
	VCutImagePropertyForm(LayersBase *Base ,QWidget *parent = 0);
	~VCutImagePropertyForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
private:
	Ui::VCutImagePropertyFormClass ui;

	void	ShowAreaGrid(void);

	VCutInspectionBase	*GetVCutInspectionBase(void);

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//VCutInspectionLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_tableWidgetVCutList_clicked(const QModelIndex &);
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

};



#endif // VCUTIMAGEPROPERTYFORM_H
