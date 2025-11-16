#ifndef OPERATEVRSFORM_H
#define OPERATEVRSFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class OperateVRSForm;
}
class	ShowVRSOperation;

class OperateVRSForm : public GUIFormBase
{
    Q_OBJECT

	GUIFormBase	*VRSOpe;
    
public:
    explicit OperateVRSForm(LayersBase *base ,QWidget *parent = 0);
    ~OperateVRSForm();

    virtual void	Prepare(void)	override;

private slots:
    void on_pushButtonOrigin_clicked();
    void on_pushButtonEscape_clicked();
    void on_pushButtonXP1_clicked();
    void on_pushButtonXP10_clicked();
    void on_pushButtonXP100_clicked();
    void on_pushButtonXM1_clicked();
    void on_pushButtonXM10_clicked();
    void on_pushButtonXM100_clicked();
    void on_pushButtonYP1_clicked();
    void on_pushButtonYP10_clicked();
    void on_pushButtonYP100_clicked();
    void on_pushButtonYM10_clicked();
    void on_pushButtonYM100_clicked();
    void on_pushButtonYM1_clicked();

private:
    Ui::OperateVRSForm *ui;
};

#endif // OPERATEVRSFORM_H
