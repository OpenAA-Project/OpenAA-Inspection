#ifndef PROPERTYDYNAMICCLASSIFYFORM_H
#define PROPERTYDYNAMICCLASSIFYFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyDynamicClassifyForm.h"
#include "XDynamicClassify.h"
#include "ShowRGBCube.h"
#include "XStandardPropertyForm.h"

class PropertyDynamicClassifyForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

public:
	PropertyDynamicClassifyForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyDynamicClassifyForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::PropertyDynamicClassifyFormClass ui;

	DynamicClassifyBase	*GetDynamicClassifyBase(void);

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	void	ShowAreaList(void);
	virtual void	BuildForShow(void)	override;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	//DynamicClassifyLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int						LibType;
	DClassifyInfos			DCInfos;

	ShowRGBSpace	ColorGenerator;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

private slots:
	void on_toolButtonInsideArea_clicked();
	void on_toolButtonBareArea_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonGenerateLibs_clicked();
	void on_ButtonPickupClearTest_clicked();
	void on_ButtonPickupTest_clicked();
	void on_pushButtonEditLibrary_clicked();
	void on_pushButtonGetBackAll_clicked();
	void on_pushButtonSetFromAll_clicked();
	void on_pushButtonGetBack_clicked();
	void on_pushButtonSetFrom_clicked();
	void on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex);
	void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &);
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButtonEditLibFolder_clicked();
	void on_toolButtonOutlineOArea_clicked();
	void on_toolButtonOutlineTArea_clicked();
	void on_toolButtonOutlineIArea_clicked();
	void on_toolButtonMinZone_clicked();
	void on_toolButtonMaxZone_clicked();
	void on_toolButtonCoreArea_clicked();
};

#endif // PROPERTYDYNAMICCLASSIFYFORM_H
