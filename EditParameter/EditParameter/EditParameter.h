#ifndef EDITPARAMETER_H
#define EDITPARAMETER_H

#include <QMainWindow>
#include "XParamGlobal.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTranslator>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "WEditParameterTab.h"
#include "FormCommSetting.h"
#include "XOutlineOffset.h"
#include "EditScanPhaseNumber.h"
#include "WMultiGrid.h"

namespace Ui {
class EditParameter;
}

class	OutlineOffsetGrid;
class	FormScanStrategy;
class	EditSyncGUIForm;
class	EditPhaseForm;
class	FormDirectionOnEachPage;
class	EditParameter;
class	EditScanPhaseNumber;
class	ShareMasterDataForm;
class	AlgorithmDLLList;
class	LogicDLL;

class	OutlineOffsetGrid : public WMultiGrid
{
friend	class EditParameter;

    EditParameter	*EParent;

public:
    OutlineOffsetGrid(EditParameter *eParent ,QWidget * parent=0):WMultiGrid(parent),EParent(eParent){}

protected:
    virtual	void	ChangeValue(int row ,int col,const QVariant &value);
    virtual	void	GetValue(int row ,int col,QVariant &value);

};

class EditParameter : public QMainWindow,public ServiceForLayers
{
    Q_OBJECT
    friend	class	OutlineOffsetGrid;
public:
    explicit EditParameter(LayersBase *base
                           ,ParamComm	*ParamCommData
                           ,QWidget *parent = 0);
    ~EditParameter();

    WEditParameterTab	*WTab;
    FormScanStrategy	*WStrategy;
    FormCommSetting		*WCommSetting;
    ShareMasterDataForm	*WShareMasterDataForm;

    int RedFirstPoint;
    int RedSecondPoint;
    int RedFirstX;
    int RedFirstY;
    int RedSecondX;
    int RedSecondY;
    BYTE	ImageTable[256];

private slots:
    void on_SaveButton_clicked();
    void on_UpdateDefaultButton_clicked();
    void on_LoadButton_clicked();
    void on_CancelButton_clicked();
    void on_pushButtonLoadFileStrategy_clicked();
    void on_pushButtonOverWriteFileStrategy_clicked();
    void on_pushButtonSaveFileStrategy_clicked();
    void on_pushButtonLoadFileComm_clicked();
    void on_pushButtonOverWriteFileComm_clicked();
    void on_pushButtonSaveFileComm_clicked();
    void on_pushButtonOutlineOffsetParam_clicked();
    void on_pushButtonConnectOutlineOffset_clicked();
    void on_comboBoxOutlineOffsetPhase_currentIndexChanged(int index);
    void on_pushButtonUpdateOutlineOffset_clicked();
    void on_pushButtonOutlineOffsetUseCurrent_clicked();
    void on_pushButtonOutlineOffsetTileX_clicked();
    void on_pushButtonTileY_clicked();
    void on_tableWidgetMachine_clicked(const QModelIndex &index);
    void on_pushButtonLoadFilesFilter_clicked();
    void on_pushButtonOverWriteFileFilter_clicked();
    void on_pushButtonSaveFileFilter_clicked();
    void on_pushButtonFilterUp_clicked();
    void on_pushButtonFilterDown_clicked();
    void on_pushButtonFilterDelete_clicked();
    void on_pushButtonLoadFileImageDir_clicked();
    void on_pushButtonOverWriteFileImageDir_clicked();
    void on_pushButtonSaveFileImageDir_clicked();
    void on_pushButtonOverWriteScanPhase_clicked();
    void on_pushButtonSaveFileScanPhase_clicked();
    void on_comboBoxPhase_currentIndexChanged(int index);
    void on_comboBoxPage_currentIndexChanged(int index);
    void on_comboBoxLayer_currentIndexChanged(int index);
    void on_cbRedGraphType_currentIndexChanged(int index);
    void on_pbRedUpdate_clicked();
    void on_pushButtonLoadAgainImageTable_clicked();
    void on_pushButtonOverWriteImageTable_clicked();
    void on_pushButtonCopy_clicked();
    void on_pushButtonPaste_clicked();
    void on_pushButtonOverWriteFileTransfer_clicked();
    void on_pushButtonTransferPlus_clicked();
    void on_pushButtonTransferMinus_clicked();
    void on_pushButtonAddShadow_clicked();
    void on_pushButtonRemoveShadow_clicked();
    void on_pushButtonShadowControlDLLFileName_clicked();
    void on_pushButtonShadowGlobalFileName_clicked();
    void on_pushButtonShadowGUIFileName_clicked();
    void on_pushButtonShadowParamFileName_clicked();
    void on_pushButtonShadowSetting_clicked();
    void on_pushButtonUpdateShadow_clicked();
	void on_tableWidgetShadow_itemSelectionChanged();
    void on_tableWidgetShadow_doubleClicked(const QModelIndex &index);
    void	SlotChanged(void);
    void on_listWidgetAlgorithmList_itemSelectionChanged();
    void on_pushButtonShowAlgorithmParam_clicked();

    void on_pushButtonEachPage_clicked();

private:
    Ui::EditParameter *ui;

    QString		GlobalParamLoadedFileName;
    QString		CommParamLoadedFileName;

    void	ExecuteAfterGlobalParam(void);

    class	MachineList : public NPList<MachineList>
    {
    public:
        int		MachineID;
        QString	MachineName;

        MachineList(void){}
    };
    OutlineOffsetGrid		WOutlineOffsetGrid;
    NPListPack<MachineList>	MachineContainer;
    OutlineOffsetInBlob		*OutlineOffset;
    int	LastPhase;
    void OutlineOffsetLoadFromWindow(void);
    void	SetOutlineOffsetGrid(void);
    int		GetCurrentPhaseInOutlineOffset(void);
	void	ShowTransfer(void);
	void	GetTransferFromWindow(void);

    enum GraphType{
            Default		=0,
            StraightLine=1,
            HightPass	=2,
            LowPass		=3,
            UpDownPass	=4,
            DownUpPass	=5,
            ShigmoidCurve=6,
            Logarithm	=7
    };
    void	ShowImageTable(int Phase ,int Page ,int Layer);
    void	InitialImageTable(void);

    QStringList	FilterFileNames;
    void LoadAndShowFilter(void);

	void	LoadShowShadow(void);
	void	ShowShadow(void);

    EditSyncGUIForm	*WEditSyncGUIForm;
    EditPhaseForm	*WEditPhaseForm;

    FormDirectionOnEachPage	*WFormDirectionOnEachPage;
    EditScanPhaseNumber		*WEditScanPhaseNumber;

    QStringList AlgorithmFileNames;
    QStringList GUIFileNames;

    AlgorithmDLLList    *DLL;
    LogicDLL	        *DLLInst;

    virtual	void resizeEvent(QResizeEvent *e)	override;
};

#endif // EDITPARAMETER_H
