#ifndef SELECTIMAGEPATHDIALOG_H
#define SELECTIMAGEPATHDIALOG_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
    class SelectImagePathDialog;
}

class SelectImagePathDialog : public QDialog
{
    Q_OBJECT

	QStringList	PathList;
public:
    explicit SelectImagePathDialog(const QStringList &_PathList,QWidget *parent = 0);
    ~SelectImagePathDialog();

	QString	SelectedPath;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_listWidgetPath_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectImagePathDialog *ui;
};

#endif // SELECTIMAGEPATHDIALOG_H
