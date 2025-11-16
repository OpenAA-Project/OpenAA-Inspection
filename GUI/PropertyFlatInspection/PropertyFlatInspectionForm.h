#ifndef PROPERTYFLATINSPECTIONFORM_H
#define PROPERTYFLATINSPECTIONFORM_H

#include "XGUIFormBase.h"
#include "XFlatInspection.h"
#include "XFlatInspectionLibrary.h"
#include "XStandardPropertyForm.h"
#include <QModelIndex>

namespace Ui {
class PropertyFlatInspectionForm;
}
class	FlatInspectionItem;
class	FlatInspectionBase;
class	ItemListForPageContainer;
class	ItemListForm;

class PropertyFlatInspectionForm : public GUIFormBase ,public StandardPropertyForm
{
    Q_OBJECT
	ItemListForPageContainer	*ItemListForPageData;
	ItemListForm				*ItemListWindow;
public:
    explicit PropertyFlatInspectionForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyFlatInspectionForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)		override;
	virtual void	BuildForShow(void)		override;
	virtual void	StartPage	(void)		override;

	void	ClearLibList(void);
	void	SetLib(int LibID);
	void	ShowEditLibrary(void);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
private slots:
    void on_toolButtonInsoectionArea_clicked();
    void on_toolButtonWindowArea_clicked();
    void on_toolButtonMasterShapeArea_clicked();
    void on_toolButtonAdaptiveArea_clicked();
    void on_toolButtonAdaptiveShape_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_pushButtonEditLibrary_clicked();

private:
    Ui::PropertyFlatInspectionForm *ui;

	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	bool	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	int		GetCurrentLibID(void);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	FlatInspectionBase	*GetFlatInspectionBase(void);

	struct	FlatInspectionItemWithPageLayer{
		FlatInspectionItem	*FlatInspectionInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	FlatInspectionItemWithPageLayer	BInfo[100];
	void		ShowFlatInspectionInfoList(void);
	void		ShowItemList(void);
};

#endif // PROPERTYFLATINSPECTIONFORM_H
