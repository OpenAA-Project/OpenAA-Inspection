#ifndef CHANGESERVERFORMASTERDIALOG_H
#define CHANGESERVERFORMASTERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XChangeServerInfo.h"

namespace Ui {
class ChangeServerForMasterDialog;
}

class ChangeServerForMasterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    ChangeServerContainer	ServerList;
public:
    explicit ChangeServerForMasterDialog(LayersBase *base,QWidget *parent = 0);
    ~ChangeServerForMasterDialog();
    
	ChangeServerInfo		*Selected;
private slots:
    void on_listWidgetServer_doubleClicked(const QModelIndex &index);
    void on_pushButtonChange_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonEdit_clicked();

private:
    Ui::ChangeServerForMasterDialog *ui;

	void	DrawList(void);
};

#endif // CHANGESERVERFORMASTERDIALOG_H
