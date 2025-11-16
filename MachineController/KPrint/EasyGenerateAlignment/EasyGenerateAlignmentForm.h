#ifndef EASYGENERATEALIGNMENTFORM_H
#define EASYGENERATEALIGNMENTFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include <QPushButton>
#include <QModelIndex>


namespace Ui {
class EasyGenerateAlignmentForm;
}

class EasyGenerateAlignmentForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit EasyGenerateAlignmentForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyGenerateAlignmentForm();
	virtual void	Prepare(void)		override;
signals:
	void	SignalBusy();
	void	SignalIdle();    
private slots:
    void on_toolButtonAutoGenerate_clicked();
	void	ResizeAction();
private:
    Ui::EasyGenerateAlignmentForm *ui;
};

#endif // EASYGENERATEALIGNMENTFORM_H
