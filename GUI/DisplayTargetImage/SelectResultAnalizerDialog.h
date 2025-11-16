#ifndef SELECTRESULTANALIZERDIALOG_H
#define SELECTRESULTANALIZERDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class SelectResultAnalizerDialog;
}

class	ResultAnalizerItemBase;

class SelectResultAnalizerDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectResultAnalizerDialog(LayersBase *Base,QWidget *parent = 0);
    ~SelectResultAnalizerDialog();
    
	ResultAnalizerItemBase *Selected;

private slots:
    void on_tableWidgetResultAnalizerItemBase_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectResultAnalizerDialog *ui;

	void	ShowList(void);
};

#endif // SELECTRESULTANALIZERDIALOG_H
