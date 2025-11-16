#ifndef ONFLOWFORM_H
#define ONFLOWFORM_H

#include <QWidget>

namespace Ui {
class OnFlowForm;
}

class OnFlowForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit OnFlowForm(QWidget *parent = 0);
    ~OnFlowForm();
    
private:
    Ui::OnFlowForm *ui;
};

#endif // ONFLOWFORM_H
