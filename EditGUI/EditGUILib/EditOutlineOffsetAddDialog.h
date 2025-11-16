#ifndef EDITOUTLINEOFFSETADDDIALOG_H
#define EDITOUTLINEOFFSETADDDIALOG_H

#include <QDialog>

namespace Ui {
class EditOutlineOffsetAddDialog;
}

class EditOutlineOffsetAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditOutlineOffsetAddDialog(QWidget *parent = 0);
    ~EditOutlineOffsetAddDialog();

	int	AddedOffset;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditOutlineOffsetAddDialog *ui;
};

#endif // EDITOUTLINEOFFSETADDDIALOG_H
