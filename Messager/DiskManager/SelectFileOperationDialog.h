#ifndef SELECTFILEOPERATIONDIALOG_H
#define SELECTFILEOPERATIONDIALOG_H

#include <QDialog>
#include "XDiskInfoCommon.h"

namespace Ui {
class SelectFileOperationDialog;
}

class SelectFileOperationDialog : public QDialog
{
    Q_OBJECT

	DiskFileInfo	Data;
public:
	QString	DestPath;

    explicit SelectFileOperationDialog(DiskFileInfo *data ,QWidget *parent = 0);
    ~SelectFileOperationDialog();

private slots:
    void on_pushButtonDelete_clicked();
    void on_pushButtonSelectDestination_clicked();
    void on_pushButtonMoveStart_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SelectFileOperationDialog *ui;
};

#endif // SELECTFILEOPERATIONDIALOG_H
