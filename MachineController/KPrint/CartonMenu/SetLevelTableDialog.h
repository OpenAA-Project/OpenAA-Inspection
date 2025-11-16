#ifndef SETLEVELTABLEDIALOG_H
#define SETLEVELTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class SetLevelTableDialog;
}

class SetLevelTableDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetLevelTableDialog(QWidget *parent = 0);
    ~SetLevelTableDialog();
    
private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonSaveClose_clicked();

private:
    Ui::SetLevelTableDialog *ui;
};

#endif // SETLEVELTABLEDIALOG_H
