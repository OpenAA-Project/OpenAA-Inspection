#ifndef TUNABLELISTDIALOG_H
#define TUNABLELISTDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class TunableListDialog;
}

class TunableListDialog : public QDialog
{
    Q_OBJECT
    
public:
    QStringList &MList;

    explicit TunableListDialog(QStringList &mList,QWidget *parent = 0);
    ~TunableListDialog();
    
private slots:
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::TunableListDialog *ui;

    void ShowList(void);
};

#endif // TUNABLELISTDIALOG_H
