#ifndef OPERATINGFORM_H
#define OPERATINGFORM_H

#include <QMainWindow>

namespace Ui {
class OperatingForm;
}

class OperatingForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit OperatingForm(QWidget *parent = 0);
    ~OperatingForm();

private:
    Ui::OperatingForm *ui;
};

#endif // OPERATINGFORM_H
