#ifndef SHOWOLDDATADIALOG_H
#define SHOWOLDDATADIALOG_H

#include <QDialog>

namespace Ui {
class ShowOldDataDialog;
}

class ShowOldDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowOldDataDialog(QWidget *parent = 0);
    ~ShowOldDataDialog();

private:
    Ui::ShowOldDataDialog *ui;
};

#endif // SHOWOLDDATADIALOG_H
