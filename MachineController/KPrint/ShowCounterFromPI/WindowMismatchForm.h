#ifndef WINDOWMISMATCHFORM_H
#define WINDOWMISMATCHFORM_H

#include <QWidget>

namespace Ui {
class WindowMismatchForm;
}

class WindowMismatchForm : public QWidget
{
    Q_OBJECT

public:
    explicit WindowMismatchForm(QWidget *parent = nullptr);
    ~WindowMismatchForm();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::WindowMismatchForm *ui;
};

#endif // WINDOWMISMATCHFORM_H
