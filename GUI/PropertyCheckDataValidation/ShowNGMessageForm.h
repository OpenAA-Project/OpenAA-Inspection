#ifndef SHOWNGMESSAGEFORM_H
#define SHOWNGMESSAGEFORM_H

#include <QWidget>

namespace Ui {
class ShowNGMessageForm;
}

class ShowNGMessageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShowNGMessageForm(QWidget *parent = nullptr);
    ~ShowNGMessageForm();

    void    SetMessage(const QString &msg);
private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::ShowNGMessageForm *ui;
};

#endif // SHOWNGMESSAGEFORM_H
