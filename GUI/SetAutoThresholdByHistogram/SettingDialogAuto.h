#ifndef SETTINGDIALOGAUTO_H
#define SETTINGDIALOGAUTO_H

#include <QDialog>
#include "XTypeDef.h"
#include "XIntClass.h"
#include <QString>
#include <QModelIndex>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialogAuto;
}

class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class SetAutoThresholdByHistogramForm;

class SettingDialogAuto : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    SetAutoThresholdByHistogramForm *Parent;
public:
    int32   LibType;
    int32   LibID;
    IntList HistID;
    int32   Strength;
	QString	ButtonName;

    explicit SettingDialogAuto(SetAutoThresholdByHistogramForm *p,QWidget *parent = nullptr);
    ~SettingDialogAuto();

private slots:
    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_itemSelectionChanged();
    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);
    void on_listWidgetCurrentUse_doubleClicked(const QModelIndex &index);
    void on_pushButtonUseCurrent_clicked();
    void on_pushButtonReturnCurrent_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void	SlotSelectLibFolderSelect(int libFolderID ,QString FolderName);

private:
    Ui::SettingDialogAuto *ui;

	int								LibFolderID;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmLibraryLevelContainer	*LLib;

	GeneralLibFolderForm			*pLibFolderSelect;
	int								CurrentLibType;
	int								CurrentLibFolderID;
	AlgorithmLibraryListContainer	LibIDListSelect;

    void ShowHistList(void);
    void ShowUsageHistList(void);
};

#endif // SETTINGDIALOGAUTO_H
