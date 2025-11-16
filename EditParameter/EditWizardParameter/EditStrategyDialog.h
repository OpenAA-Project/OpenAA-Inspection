#ifndef EDITSTRATEGYDIALOG_H
#define EDITSTRATEGYDIALOG_H

#include <QDialog>

namespace Ui {
class EditStrategyDialog;
}

class EditStrategyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditStrategyDialog(QWidget *parent = 0);
    ~EditStrategyDialog();

private:
    Ui::EditStrategyDialog *ui;
};

#endif // EDITSTRATEGYDIALOG_H
