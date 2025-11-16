#ifndef PROPERTYNICKINSPECTIONFORM_H
#define PROPERTYNICKINSPECTIONFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XNickInspection.h"

namespace Ui {
class PropertyNickInspectionForm;
}

class	NickInspectionBase;
class	NickInspectionLibrary;

class PropertyNickInspectionForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyNickInspectionForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyNickInspectionForm();
    
	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	
private slots:
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_pushButtonEditLibrary_clicked();
    void on_ButtonGenerateLibs_clicked();
    void on_tableWidgetItemList_clicked(const QModelIndex &index);

private:
    Ui::PropertyNickInspectionForm *ui;
    
	//NickInspectionLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;

	void	ShowSelectedLibList(void);
	void	ShowLibList(void);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	AlgorithmLibraryListContainer	SelectedLibList;

	NickInspectionBase	*GetNickInspectionBase(void);
	void	ShowListGrid(void);

	NickInspectionListForPacketPack	NickInspectionItemList;
	void	ShowItemList(void);
};

#endif // PROPERTYNICKINSPECTIONFORM_H
