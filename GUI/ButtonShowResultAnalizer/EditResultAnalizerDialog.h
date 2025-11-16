#ifndef EDITRESULTANALIZERDIALOG_H
#define EDITRESULTANALIZERDIALOG_H

#include <QDialog>
#include <QTableView>
#include "XServiceForLayers.h"

namespace Ui {
class EditResultAnalizerDialog;
}

class EditResultAnalizerDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditResultAnalizerDialog(LayersBase *Base ,QWidget *parent = 0);
    ~EditResultAnalizerDialog();
    
private slots:
    void on_listWidgetResultAnalizerDLL_doubleClicked(const QModelIndex &index);
    void on_pushButtonFromDLL_clicked();
    void on_pushButtonToDLL_clicked();
    void on_tableWidgetResultAnalizerItemBase_doubleClicked(const QModelIndex &index);
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonUpdateDefault_clicked();

private:
    Ui::EditResultAnalizerDialog *ui;

	void	ShowList(void);
};

#endif // EDITRESULTANALIZERDIALOG_H
