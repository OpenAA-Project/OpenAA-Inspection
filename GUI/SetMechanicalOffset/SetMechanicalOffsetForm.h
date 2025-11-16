#ifndef SETMechanicalOFFSETFORM_H
#define SETMechanicalOFFSETFORM_H

#include "XGUIFormBase.h"

namespace Ui {
    class SetMechanicalOffsetForm;
}

class	SignalOperandInt;

class SetMechanicalOffsetForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit SetMechanicalOffsetForm(LayersBase *Base,QWidget *parent = 0);
    ~SetMechanicalOffsetForm();

	int		MechanicalOffset;
	SignalOperandInt	*ioMechanicalOffset;

	virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;

private slots:
    void on_pushButtonSet_clicked();
	void	OperandChanged();

private:
    Ui::SetMechanicalOffsetForm *ui;
};

#endif // SETMechanicalOFFSETFORM_H
