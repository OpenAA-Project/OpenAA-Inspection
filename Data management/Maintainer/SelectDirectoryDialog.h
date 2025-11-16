#ifndef SELECTDIRECTORYDIALOG_H
#define SELECTDIRECTORYDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QTreeView>

namespace Ui {
class SelectDirectoryDialog;
}

class SelectDirectoryDialog : public QDialog
{
    Q_OBJECT
    QFileSystemModel	Model;
public:
    explicit SelectDirectoryDialog(const QString &Path ,QWidget *parent = 0);
    ~SelectDirectoryDialog();
    
	QString	Directory;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::SelectDirectoryDialog *ui;
};

#endif // SELECTDIRECTORYDIALOG_H
