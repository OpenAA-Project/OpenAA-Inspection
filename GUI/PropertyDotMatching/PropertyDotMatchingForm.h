#ifndef PROPERTYDOTMATCHINGFORM_H
#define PROPERTYDOTMATCHINGFORM_H

#include "XGUIFormBase.h"
#include "XDotMatching.h"
#include "XDotMatchingLibrary.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyDotMatchingForm;
}

class	DotMatchingItem;
class	DotMatchingBase;


class PropertyDotMatchingForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT
    
public:
    explicit PropertyDotMatchingForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyDotMatchingForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

	void	ClearLibList(void);
	void	SetLib(int LibID);
	void	GenerateDotMatchings(void);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
private slots:
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonEditLibrary_clicked();
    void on_ButtonPickupTest_clicked();
    void on_ButtonPickupClearTest_clicked();
    void on_ButtonGenerateLibs_clicked();
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);

private:
    Ui::PropertyDotMatchingForm *ui;

	//DotMatchingLibrary	*TempLib;
	AlgorithmLibraryLevelContainer *TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	bool	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	DotMatchingBase	*GetDotMatchingBase(void);

	struct	DotMatchingItemWithPageLayer{
		DotMatchingItem	*DotMatchingInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	DotMatchingItemWithPageLayer	BInfo[100];
	void		ShowDotMatchingInfoList(void);
	void		ShowTab(void);

	FlexArea	GlobalPickupArea;
};

#endif // PROPERTYDOTMATCHINGFORM_H
