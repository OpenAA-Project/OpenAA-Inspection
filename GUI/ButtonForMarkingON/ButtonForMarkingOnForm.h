#ifndef BUTTONFORMARKINGONFORM_H
#define BUTTONFORMARKINGONFORM_H

#include <QDialog>
#include "XGUIFormBase.h"

namespace Ui {
    class ButtonForMarkingOnForm;
}
class	SignalOperandInt;

class ButtonForMarkingOnForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit ButtonForMarkingOnForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonForMarkingOnForm();

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	virtual void	Prepare(void)	override;

	SignalOperandInt	*ioMarkingON;

private slots:
        void on_toolButton_clicked();
		void	ResizeAction();
		void	OperandChanged();
private:
    Ui::ButtonForMarkingOnForm *ui;
};

#endif // BUTTONFORMARKINGONFORM_H
