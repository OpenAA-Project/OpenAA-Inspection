#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XAlgorithmBase.h"
#include "NList.h"
#include "XAlgorithmLibrary.h"
#include "XDXFOperation.h"

namespace Ui {
class SelectLibraryDialog;
}
class	GeneralLibFolderForm;
class	PropertyDXFOperationForm;

class	LogicDLLPointer : public NPList<LogicDLLPointer>
{
public:
	LogicDLL *Pointer;

	LogicDLLPointer(LogicDLL *p):Pointer(p){}
};

class SelectLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
  
	PropertyDXFOperationForm	*Parent;
	NPListPack<LogicDLLPointer>		LogicDLLPointerContainer;
public:
    explicit SelectLibraryDialog(DWORD AlgorithmType ,PropertyDXFOperationForm *p,LayersBase *base, QWidget *parent = 0);
    ~SelectLibraryDialog();
    
	AlgorithmLibraryListContainer	Selected;

private slots:
    void on_tableWidgetAlgorithm_clicked(const QModelIndex &index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonClose_clicked();
	void	SlotSelectLibFolderSelect(int LibFolderID ,QString FolderName);
private:
    Ui::SelectLibraryDialog *ui;

	GeneralLibFolderForm			*pLibFolderSelect;
	int								CurrentLibType;
	int								CurrentLibFolderID;
	AlgorithmLibraryListContainer	LibIDListSelect;

	void	ShowFolder(int LibType);

};

#endif // SELECTLIBRARYDIALOG_H
