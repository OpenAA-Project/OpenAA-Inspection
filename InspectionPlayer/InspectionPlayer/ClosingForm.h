#ifndef CLOSINGFORM_H
#define CLOSINGFORM_H

#include <QWidget>

namespace Ui {
class ClosingForm;
}

class ClosingForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit ClosingForm(QWidget *parent = 0);
    ~ClosingForm();
    
private:
    Ui::ClosingForm *ui;
};

#endif // CLOSINGFORM_H
