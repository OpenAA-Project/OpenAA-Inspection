#ifndef EDITTEMPLATERULEITEMDIALOG_H
#define EDITTEMPLATERULEITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class EditTemplateRuleItemDialog;
}

class EditTemplateRuleItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTemplateRuleItemDialog(QWidget *parent = nullptr);
    ~EditTemplateRuleItemDialog();

private slots:
    void on_pushButtonCreate_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();
    void on_tableWidgetMemberList_doubleClicked(const QModelIndex &index);

private:
    Ui::EditTemplateRuleItemDialog *ui;
};

#endif // EDITTEMPLATERULEITEMDIALOG_H
