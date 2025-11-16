#ifndef EDITLIBRARYDIALOG_H
#define EDITLIBRARYDIALOG_H

#include <QDialog>

namespace Ui {
class EditLibraryDialog;
}

class EditLibraryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditLibraryDialog(QWidget *parent = 0);
    ~EditLibraryDialog();

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);

    void on_ButtonLibNew_clicked();

    void on_ButtonLibDelete_clicked();

    void on_ButtonLibSaveNew_clicked();

    void on_ButtonLibSave_clicked();

    void on_pushButton_clicked();

private:
    Ui::EditLibraryDialog *ui;
};

#endif // EDITLIBRARYDIALOG_H
