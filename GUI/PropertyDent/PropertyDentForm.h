#ifndef PROPERTYDENTFORM_H
#define PROPERTYDENTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XDentInspection.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyDentForm;
}

class	DentItem;
class	DentBase;
class	AlgorithmLibraryLevelContainer;

class PropertyDentForm : public GUIFormBase ,public StandardPropertyForm
{
    Q_OBJECT
    
public:
    explicit PropertyDentForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyDentForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override; 

	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

	void	ClearLibList(void);
	void	SetLib(int LibID);
	void	GenerateDents(void);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private slots:
    void on_pushButtonEditLibrary_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonEditLibFolder_clicked();
    void on_ButtonPickupTest_clicked();
    void on_ButtonPickupClearTest_clicked();
    void on_ButtonGenerateLibs_clicked();
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyDentForm *ui;

	DentBase	*GetDentBase(void);
	AlgorithmLibraryLevelContainer		*LLib;
	int				LibType;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	bool	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	NPListPack<DentInfoList>	DentInfos;

	void	ShowList(void);
};

#endif // PROPERTYDENTFORM_H
