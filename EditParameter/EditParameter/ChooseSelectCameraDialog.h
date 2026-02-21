#ifndef CHOOSESELECTCAMERADIALOG_H
#define CHOOSESELECTCAMERADIALOG_H

#include <QDialog>

namespace Ui {
class ChooseSelectCameraDialog;
}

class ChooseSelectCameraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseSelectCameraDialog(QWidget *parent = nullptr);
    ~ChooseSelectCameraDialog();

private:
    Ui::ChooseSelectCameraDialog *ui;
};

#endif // CHOOSESELECTCAMERADIALOG_H
