#ifndef PROPERTYPROJECTEDINSPECTIONFORM_H
#define PROPERTYPROJECTEDINSPECTIONFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XIntClass.h"
#include "XProjectedInspection.h"
#include "XProjectedInspectionLibrary.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyProjectedInspectionForm;
}

class PropertyProjectedInspectionForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyProjectedInspectionForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyProjectedInspectionForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_tableWidgetAllItems_clicked(const QModelIndex &index);
    void on_tableWidgetAllItems_doubleClicked(const QModelIndex &index);
    void on_pushButtonEditLibrary_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonPickupTest_clicked();
    void on_ButtonGenerateLibs_clicked();
    void on_ButtonPickupClearTest_clicked();

private:
    Ui::PropertyProjectedInspectionForm *ui;

	ProjectedInspectionBase	*GetProjectedInspectionBase(void);

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual void	BuildForShow(void)	override;

	//ProjectedInspectionLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int						LibType;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);
};

#endif // PROPERTYPROJECTEDINSPECTIONFORM_H
