#ifndef SELECTDELETIONDIALOG_H
#define SELECTDELETIONDIALOG_H

#include <QDialog>

namespace Ui {
class SelectDeletionDialog;
}

class SelectDeletionDialog : public QDialog
{
    Q_OBJECT
    
public:
	bool	DeleteManualItems	;
	bool	DeleteCADItems		;
	
	explicit SelectDeletionDialog(QWidget *parent = 0);
    ~SelectDeletionDialog();
    
private slots:
    void on_toolButtonOK_clicked();
    void on_toolButtonCancel_clicked();

private:
    Ui::SelectDeletionDialog *ui;
};

#endif // SELECTDELETIONDIALOG_H
