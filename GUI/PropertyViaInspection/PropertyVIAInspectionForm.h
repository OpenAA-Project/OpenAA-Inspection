#ifndef PROPERTYVIAINSPECTIONFORM_H
#define PROPERTYVIAINSPECTIONFORM_H

#include <QWidget>
#include <QTabBar>
#include "ui_PropertyVIAInspectionForm.h"
#include "XViaInspection.h"
#include "XViaInspectionLibrary.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"

namespace Ui {
class PropertyVIAInspectionForm;
}

class PropertyVIAInspectionForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT
    
public:
    explicit PropertyVIAInspectionForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyVIAInspectionForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

	void	ClearLibList(void);
	void	SetLib(int LibID);
	void	GenerateVIAs(void);

	enum	KindOfSort
	{
		KOS_ID_Up
		,KOS_ID_Dn
		,KOS_Name_Up
		,KOS_Name_Dn
	}LibSortType;

private slots:
    void on_toolButtonLibrary_clicked();
    void on_toolButtonCreateVIA_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
	void on_pushButtonEditLibrary_clicked();
    void on_ButtonPickupTest_clicked();
    void on_ButtonPickupClearTest_clicked();
    void on_ButtonGenerateLibs_clicked();
    void on_ButtonLibSave_clicked();
	void	MListSectionClicked ( int logicalIndex );
private:
    Ui::PropertyVIAInspectionForm *ui;


	//VIALibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	VIABase	*GetVIABase(void);
	QTabBar	TabBarVIAOnMouse;

	struct	VIAItemWithPageLayer{
		VIAItem	*VIAInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	VIAItemWithPageLayer	BInfo[100];
	void		ShowVIAInfoList(void);

	NPListPack<VIAInfoList>	VIAInfos;
	FlexArea	GlobalPickupArea;
	
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
};

#endif // PROPERTYVIAINSPECTIONFORM_H
