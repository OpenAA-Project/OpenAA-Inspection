#ifndef PROPERTYTHINMETALFORM_H
#define PROPERTYTHINMETALFORM_H

#include <QWidget>
#include "XThinMetal.h"
#include "XThinMetalLibrary.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"
#include "ShowSampleForm.h"

namespace Ui {
class PropertyThinMetalForm;
}
class	AlgorithmLibraryLevelContainer;

class PropertyThinMetalForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyThinMetalForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyThinMetalForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	StartPage	(void)	override;

	void	ClearLibList(void);
	void	SetLib(int LibID);
	//void	GenerateThinMetals(void);

	enum	KindOfSort
	{
		KOS_ID_Up
		,KOS_ID_Dn
		,KOS_Name_Up
		,KOS_Name_Dn
	}LibSortType;

private slots:
    void on_toolButtonLibrary_clicked();
    void on_toolButtonCreateArea_clicked();
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
    void on_ButtonLibSave_clicked();
	void	MListSectionClicked ( int logicalIndex );

    void on_tableWidgetItems_clicked(const QModelIndex &index);
    void on_tableWidgetItems_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyThinMetalForm *ui;

	AlgorithmLibraryLevelContainer	*LLib;
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
	ThinMetalBase	*GetThinMetalBase(void);
	QTabBar	TabBarThinMetalOnMouse;

	struct	ThinMetalItemWithPageLayer{
		ThinMetalItem	*ThinMetalInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	ThinMetalItemWithPageLayer	BInfo[100];
	void		ShowThinMetalInfoList(void);

	ThinMetalInfoContainer	ThinMetalInfos;
	FlexArea	GlobalPickupArea;
	ShowSampleForm	*ShowSampleFormInst;
	
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
};

#endif // PROPERTYTHINMETALFORM_H
