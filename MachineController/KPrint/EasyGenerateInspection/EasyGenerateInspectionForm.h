#ifndef EASYGENERATEINSPECTIONFORM_H
#define EASYGENERATEINSPECTIONFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include <QPushButton>
#include <QModelIndex>

namespace Ui {
class EasyGenerateInspectionForm;
}

class EasyGenerateInspectionForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit EasyGenerateInspectionForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyGenerateInspectionForm();
	virtual void	Prepare(void)		override;
	void	GenerateStart(void);
    void	GenerateStart(int SlaveNo);
signals:
	void	SignalBusy();
	void	SignalIdle();   
private slots:
    void on_toolButtonAutoGenerate_clicked();
	void	ResizeAction();
private:
    Ui::EasyGenerateInspectionForm *ui;
};

#endif // EASYGENERATEINSPECTIONFORM_H
