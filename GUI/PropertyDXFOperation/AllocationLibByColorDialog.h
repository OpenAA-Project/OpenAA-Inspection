#ifndef ALLOCATIONLIBBYCOLORDIALOG_H
#define ALLOCATIONLIBBYCOLORDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"
#include "XDXFOperation.h"
#include "mtPushButtonColored.h"

namespace Ui {
class AllocationLibByColorDialog;
}
class	GeneralLibFolderForm;
class	DXFOperationBase;
class	PropertyDXFOperationForm;

class AllocationLibByColorDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	PropertyDXFOperationForm	*Parent;
public:
	AllocationLibByColorContainer	AllocationLibByColorContainerInst;

	explicit AllocationLibByColorDialog(LayersBase *base, PropertyDXFOperationForm *p,QWidget *parent = 0);
    ~AllocationLibByColorDialog();
    
private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButtonAddColor_clicked();
    void on_pushButtonSubColor_clicked();
    void on_comboBoxLibTypeSelect_currentIndexChanged(const QString &arg1);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelectButton_clicked();
    void on_tableWidgetSelected_doubleClicked(const QModelIndex &index);
    void on_pushButtonUpdate_clicked();
    void on_pushButtonCancel_clicked();

	void	SignalClickedColorList(int row);
	void	SlotSelectLibFolderSelect(int libFolderID ,QString FolderName);
    void on_pushButtonOK_clicked();
    void on_pushButtonFromDXFData_clicked();

private:
    Ui::AllocationLibByColorDialog *ui;

	GeneralLibFolderForm			*pLibFolderSelect;
	int								CurrentLibType;
	int								CurrentLibFolderID;
	AlgorithmLibraryListContainer	LibIDListSelect;
	AlgorithmLibraryListContainer	Libraries;

	DXFOperationBase	*GetDXFOperationBase(void);
	void	SetLibTypeInComboBox(void);
	void	ShowFolder(int LibType);	
	void	ShowAllocationLibByColorContainerList(void);
	void	ShowLibraries(void);
	void	ReqAllocationLibByColorContainer(int LevelID);
};

class	ColotButtonInList : public mtPushButtonColored
{
    Q_OBJECT

 public:
	int	Row;
	ColotButtonInList(int row ,QWidget *parent = 0);

signals:
	void	SignalClicked(int row);
private slots:
	void	SlotClicked();
};


#endif // ALLOCATIONLIBBYCOLORDIALOG_H
