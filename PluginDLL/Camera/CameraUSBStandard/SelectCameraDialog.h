#ifndef SELECTCAMERADIALOG_H
#define SELECTCAMERADIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
namespace Ui {
class SelectCameraDialog;
}

class SelectCameraDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	int VendoredProductIDList[100];
	int CountOfCam;
public:
    explicit SelectCameraDialog(int VendoredProductIDList[] ,int CountOfCam ,LayersBase *base,QWidget *parent = 0);
    ~SelectCameraDialog();
    
	int	SelectedNo;

private slots:
    void on_listWidgetCameraList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();

private:
    Ui::SelectCameraDialog *ui;
};

#endif // SELECTCAMERADIALOG_H
