#ifndef PROPERTYCOLORDIFFERENCEFORM_H
#define PROPERTYCOLORDIFFERENCEFORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XColorDifference.h"
#include "XStandardPropertyForm.h"
#include "OnFlowForm.h"

namespace Ui {
class PropertyColorDifferenceForm;
}
class	ColorDifferenceItem;
class	ColorDifferenceBase;
class	ItemListForPageContainer;
class	ColorDifferenceLibrary;
class	AlgorithmLibraryLevelContainer;

class PropertyColorDifferenceForm : public GUIFormBase ,public StandardPropertyForm
{
    Q_OBJECT
    
	ItemListForPageContainer	*ItemListForPageData;
	OnFlowForm					*OnFlowFormWindow;
public:
    explicit PropertyColorDifferenceForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyColorDifferenceForm();

 	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

	void	ClearLibList(void);
	void	SetLib(int LibID);
	void	GenerateColorDifferences(void);
	void	AddColor(bool OKMode);
	void	SetRegistInFlow(bool ONMode);
	void	SetStatisticThreshold(double SigmaH,double SigmaS,double SigmaV);
	void	ClearFlowStack(void);
	void	AutoGenerate(int LibID);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

	bool	SaveFlow(QIODevice *f);
	bool	LoadFlow(QIODevice *f);
private slots:
    void on_toolButtonShowItem_clicked();
    void on_toolButtonShowRegulation_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_pushButtonEditLibrary_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonRegisterOK_clicked();
    void on_pushButtonRegisterNG_clicked();
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_toolButtonRegistInFlow_clicked();
    void on_toolButtonSetThresholdHSV_clicked();
    void on_toolButtonClearFlow_clicked();
    void on_pushButtonSaveFlow_clicked();
    void on_pushButtonLoadFlow_clicked();

    void on_pushButtonAutoGenerate_clicked();

private:
    Ui::PropertyColorDifferenceForm *ui;

	AlgorithmLibraryLevelContainer	*LLib;
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
	ColorDifferenceBase	*GetColorDifferenceBase(void);

	struct	ColorDifferenceItemWithPageLayer{
		ColorDifferenceItem	*ColorDifferenceInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	ColorDifferenceItemWithPageLayer	BInfo[100];
	void		ShowColorDifferenceInfoList(void);
	void		ShowTab(void);
	void		ShowItemList(void);
	FlexArea	GlobalPickupArea;
};

#endif // PROPERTYCOLORDIFFERENCEFORM_H
