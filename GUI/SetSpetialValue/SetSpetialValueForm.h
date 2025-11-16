#ifndef SETMechanicalOFFSETFORM_H
#define SETMechanicalOFFSETFORM_H

#include "XGUIFormBase.h"

namespace Ui {
    class SetSpetialValueForm;
}

class	SignalOperandInt;

class SetSpetialValueForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit SetSpetialValueForm(LayersBase *Base,QWidget *parent = 0);
    ~SetSpetialValueForm();

	int		SpetialValue;
	SignalOperandInt	*ioSpetialValue;

	virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;

private slots:
    void on_pushButtonSet_clicked();
	void	OperandChanged();

private:
    Ui::SetSpetialValueForm *ui;
};

#endif // SETMechanicalOFFSETFORM_H
