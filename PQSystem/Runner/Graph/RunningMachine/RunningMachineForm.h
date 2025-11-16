#ifndef RUNNINGMACHINEFORM_H
#define RUNNINGMACHINEFORM_H

#include <QWidget>
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"

namespace Ui {
class RunningMachineForm;
}

class RunningMachineForm : public PQSystemRunner
{
    Q_OBJECT
    
public:
    explicit RunningMachineForm(LayersBase *base ,const QString &root ,const QString &name
							,QWidget *parent = 0);
    ~RunningMachineForm();
    
    virtual	bool	Initial(void)   override;
	virtual	const QString	GetPath(void)			override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemRunningMachine";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemRunningMachine.dat";  }
protected:
	virtual	void showEvent(QShowEvent *event)	override;

private slots:
    void on_pushButtonStartSearch_clicked();
    void on_pushButtonView_clicked();
    void on_pushButtonExcel_clicked();

private:
    Ui::RunningMachineForm *ui;
};

#endif // RUNNINGMACHINEFORM_H
