#ifndef WIZARDMENUFORM_H
#define WIZARDMENUFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationPacketComm.h"

namespace Ui {
class WizardMenuForm;
}
class WizardMasterMenuForm;

#define WM_DWMCOMPOSITIONCHANGED        0x031E

class WizardMenuForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
	WizardMasterMenuForm	*Parent;

	bool	UpperMode;
public:
    explicit WizardMenuForm(WizardMasterMenuForm *p,LayersBase *Base ,QWidget *parent = 0);
    ~WizardMenuForm();

private slots:
    void on_PushButtonCreateNew_clicked();
    void on_PushButtonEdit_clicked();
    void on_PushButtonLoadMaster_clicked();
    void on_PushButtonClose_clicked();
    void on_PushButtonCreateNewNext1_clicked();
    void on_PushButtonCreateNewNext2_clicked();
    void on_PushButtonCreateNewSave_clicked();
    void on_PushButtonCreateNewAgain_clicked();
    void on_PushButtonCreateNewNext4_clicked();
    void on_PushButtonAutoGenerate_clicked();
    void on_PushButtonSwitchPhase_clicked();
    void on_PushButtonCopyImage_clicked();
    void on_PushButtonEditDetail_clicked();
    void on_PushButtonSwitchPhaseNext_clicked();
    void on_PushButtonSwitchPhaseNext2_clicked();
    void on_PushButtonReadDXFUpper_clicked();
    void on_PushButtonReadDXFLower_clicked();
    void on_PushButtonDXFReturn_clicked();
    void on_DXFNext1_clicked();
    void on_PushButtonDXFNext2_clicked();
    void on_PushButtonDXFNext3_clicked();
    void on_PushButtonMaskNext1_clicked();
    void on_PushButtonAlignmentNext_clicked();
    void on_PushButtonInspectionNext1_clicked();
    void on_PushButtonBladeNext1_clicked();
    void on_PushButtonCreateNewPrev4_clicked();
    void on_PushButtonCreateNewPrev1_clicked();
    void on_PushButtonCreateNewPrev2_clicked();
    void on_PushButtonSwitchPhasePrev_clicked();
    void on_PushButtonSwitchPhasePrev2_clicked();
    void on_PushButtonDXFPrev_clicked();
    void on_DXFPrev1_clicked();
    void on_PushButtonDXFPrev3_clicked();
    void on_PushButtonMaskPrev1_clicked();
    void on_PushButtonAlignmentPrev_clicked();
    void on_PushButtonInspectionPrev1_clicked();
    void on_PushButtonBladePrev1_clicked();
    void on_stackedWidgetSenario_currentChanged(int arg1);
    void on_stackedWidget_currentChanged(int arg1);

    void on_PushButtonSetExposure_clicked();

    void on_pushButtonSetTriggerPosition_clicked();

private:
    Ui::WizardMenuForm *ui;

	virtual	void showEvent ( QShowEvent * event )	override;
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

class	GUICmdIntegrationCopyImageToTarget: public IntegrationCmdPacketBase
{
public:

	GUICmdIntegrationCopyImageToTarget(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // WIZARDMENUFORM_H
