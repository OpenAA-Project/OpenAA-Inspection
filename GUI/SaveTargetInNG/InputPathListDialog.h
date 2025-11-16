#ifndef INPUTPATHLISTDIALOG_H
#define INPUTPATHLISTDIALOG_H

#include <QDialog>

namespace Ui {
class InputPathListDialog;
}

class InputPathListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputPathListDialog(QWidget *parent = 0);
    ~InputPathListDialog();

private:
    Ui::InputPathListDialog *ui;
};

#endif // INPUTPATHLISTDIALOG_H
