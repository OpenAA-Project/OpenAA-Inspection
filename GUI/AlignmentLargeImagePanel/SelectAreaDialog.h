#ifndef SELECTAREADIALOG_H
#define SELECTAREADIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XPacketAlignmentLarge.h"
#include "XAlignmentLarge.h"

namespace Ui {
class SelectAreaDialog;
}

class SelectAreaDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	ListAreaIDInfoContainer Areas;
public:
    explicit SelectAreaDialog(ListAreaIDInfoContainer &PickedAreasWithPage
							  ,LayersBase *Base
							  ,QWidget *parent = 0);
    ~SelectAreaDialog();

	ListAreaIDInfoContainer SelectedAreas;
    
private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectAreaDialog *ui;
};

#endif // SELECTAREADIALOG_H
