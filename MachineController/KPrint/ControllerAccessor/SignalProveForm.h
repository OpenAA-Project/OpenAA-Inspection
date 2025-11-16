#ifndef SIGNALPROVEFORM_H
#define SIGNALPROVEFORM_H

#include <QWidget>

namespace Ui {
class SignalProveForm;
}

class ControllerAccessor;

class SignalProveForm : public QWidget
{
    Q_OBJECT
    
	ControllerAccessor	*Parent;

public:
    explicit SignalProveForm(ControllerAccessor *p ,QWidget *parent = 0);
    ~SignalProveForm();
    
private:
    Ui::SignalProveForm *ui;
};

#endif // SIGNALPROVEFORM_H
