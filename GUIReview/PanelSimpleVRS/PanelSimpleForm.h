#ifndef PANELSIMPLEFORM_H
#define PANELSIMPLEFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class PanelSimpleForm;
}

class PanelSimpleForm : public GUIFormBase
{
    Q_OBJECT
    
	GUIFormBase	*VRSOpe;
public:
	int32		StepPulse;

    explicit PanelSimpleForm(LayersBase *base ,QWidget *parent = 0);
    ~PanelSimpleForm();
    
	virtual	void	Prepare(void)	override;
private slots:
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonLeft_clicked();
    void on_pushButtonRight_clicked();
    void on_pushButtonOrg_clicked();
    void on_pushButtonHome_clicked();

private:
    Ui::PanelSimpleForm *ui;
};

#endif // PANELSIMPLEFORM_H
