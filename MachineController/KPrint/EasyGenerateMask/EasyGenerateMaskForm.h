#ifndef EASYGENERATEMASKFORM_H
#define EASYGENERATEMASKFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include <QPushButton>
#include <QModelIndex>


namespace Ui {
class EasyGenerateMaskForm;
}

class EasyGenerateMaskForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit EasyGenerateMaskForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyGenerateMaskForm();
	virtual void	Prepare(void)		override;
signals:
	void	SignalBusy();
	void	SignalIdle();    
private slots:
    void on_toolButtonAutoGenerate_clicked();
	void	ResizeAction();
private:
    Ui::EasyGenerateMaskForm *ui;
};

#endif // EASYGENERATEMASKFORM_H
