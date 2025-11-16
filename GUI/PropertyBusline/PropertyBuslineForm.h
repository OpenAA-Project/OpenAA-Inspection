#ifndef PROPERTYBUSLINEFORM_H
#define PROPERTYBUSLINEFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XBuslineInspection.h"

namespace Ui {
class PropertyBuslineForm;
}

class	BuslineLibrary;
class	BuslineBase;

class PropertyBuslineForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT
    
public:
    explicit PropertyBuslineForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyBuslineForm();
    
	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	void	CommandGenerateBlocks(int LibID,int X1,int Y1,int X2,int Y2);
	void	CommandGenerateBlocksByLib(int LibID);

private slots:
    void on_toolButtonGenerate_clicked();
    void on_toolButtonTest_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_pushButtonEditLibrary_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonGenerateFotTest_clicked();
    void on_tableWidgetItemList_clicked(const QModelIndex &index);
    void on_tableWidgetItemList_doubleClicked(const QModelIndex &index);

    void on_pushButtonTest_clicked();

    void on_pushButtonClear_clicked();

private:
    Ui::PropertyBuslineForm *ui;

	//BuslineLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	ShowSelectedLibList(void);

	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	AlgorithmLibraryListContainer	SelectedLibList;

	BuslineBase	*GetBuslineBase(void);
	void	ShowListGrid(void);

	BuslineListForPacketPack	BuslineItemList;
	void	ShowItemList(void);
};

#endif // PROPERTYBUSLINEFORM_H
