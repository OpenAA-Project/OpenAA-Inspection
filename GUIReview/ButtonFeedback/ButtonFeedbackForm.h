#ifndef BUTTONFEEDBACKFORM_H
#define BUTTONFEEDBACKFORM_H

#include <QDialog>

namespace Ui {
class ButtonFeedbackForm;
}

class ButtonFeedbackForm : public QDialog
{
    Q_OBJECT

public:
    explicit ButtonFeedbackForm(QWidget *parent = 0);
    ~ButtonFeedbackForm();

private:
    Ui::ButtonFeedbackForm *ui;
};

#endif // BUTTONFEEDBACKFORM_H
