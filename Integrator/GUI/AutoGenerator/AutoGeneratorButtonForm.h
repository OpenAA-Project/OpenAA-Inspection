#ifndef AUTOGENERATORBUTTONFORM_H
#define AUTOGENERATORBUTTONFORM_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XAutoGenerator.h"


namespace Ui {
class AutoGeneratorButtonForm;
}

class AutoGeneratorForm;
class	SignalOperandInt;
class	SignalOperandBit;

class AutoGeneratorButtonForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

    AutoGeneratorForm   *Window;
    SignalOperandBit	*iEnableRunning;
    SignalOperandBit	*iAlarm;
    GUIFormBase	        *FormRun;
public:
    ListAutoGeneratorContainer  ListContainer;
    QString                     DefaultListFileName;
    int32                       RegNumberEnableRunning;
    int32                       RegNumberAlarm;
    ListAutoGenerator           CurrentList;    //Don't set pointer fot editting list

    explicit AutoGeneratorButtonForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~AutoGeneratorButtonForm();

    virtual void	Prepare(void)		override;
    virtual void	AfterStartSequence(void)    override;

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)  override;
    virtual	void	BuildForShow(void)  override;

    void    SaveListContainer(void);
    void	SetRun(bool StateRun);
    void	SetInspectionRunOnly(bool StateRun);

private slots:
    void on_PushButtonRun_clicked();
    void on_PushButtonSetting_clicked();
    void on_PushButtonSelect_clicked();

private:
    Ui::AutoGeneratorButtonForm *ui;
};

#endif // AUTOGENERATORBUTTONFORM_H
