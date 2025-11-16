#ifndef SELECTSTARTDIALOG_H
#define SELECTSTARTDIALOG_H

#include <QDialog>
#include"XServiceForLayers.h"
#include <QModelIndex>

namespace Ui {
class SelectStartDialog;
}

class AutoGeneratorButtonForm;
class ListAutoGenerator;

class SelectStartDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    AutoGeneratorButtonForm *Parent;
public:
    ListAutoGenerator   *Selected;

    explicit SelectStartDialog(LayersBase *base,AutoGeneratorButtonForm *p ,QWidget *parent = nullptr);
    ~SelectStartDialog();

private slots:
    void on_tableWidgetStoredList_itemSelectionChanged();
    void on_tableWidgetStoredList_clicked(const QModelIndex &index);
    void on_lineEditCode_textChanged(const QString &arg1);
    void on_pushButtonGenerate_clicked();

    void on_tableWidgetStoredList_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectStartDialog *ui;

    void    ShowStoredGrid(void);
};

#endif // SELECTSTARTDIALOG_H
