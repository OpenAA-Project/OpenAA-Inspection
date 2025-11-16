#ifndef PROPERTYHOUGHINSPECTIONFORM_H
#define PROPERTYHOUGHINSPECTIONFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XHoughInspection.h"

namespace Ui {
class PropertyHoughInspectionForm;
}

class PropertyHoughInspectionForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyHoughInspectionForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyHoughInspectionForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	void	CommandGenerateBlocks(int LibID,int X1,int Y1,int X2,int Y2);

private slots:
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonEditLibrary_clicked();
    void on_toolButtonGenerate_clicked();
    void on_toolButtonTest_clicked();
    void on_ButtonLibSave_clicked();
    void on_tableWidgetItemList_clicked(const QModelIndex &index);
    void on_tableWidgetItemList_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyHoughInspectionForm *ui;

	//HoughLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	ShowSelectedLibList(void);

	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	AlgorithmLibraryListContainer	SelectedLibList;

	HoughBase	*GetHoughBase(void);
	void	ShowListGrid(void);

	HoughListForPacketPack	HoughItemList;
	void	ShowItemList(void);
};

#endif // PROPERTYHOUGHINSPECTIONFORM_H
