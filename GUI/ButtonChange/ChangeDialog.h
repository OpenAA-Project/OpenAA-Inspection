#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H

#include <QDialog>
#include <QTableView>
#include "XServiceForLayers.h"

namespace Ui {
class ChangeDialog;
}

class ChangeDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
public:
	int		NewPhaseCount	;
	int		NewPageCount	;
	int		NewLayerCount	;
	int		NewLineCount	;
	
	explicit ChangeDialog(LayersBase *Base ,QWidget *parent = 0);
    ~ChangeDialog();
    
private slots:
    void on_pushButtonExecute_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ChangeDialog *ui;
};

#endif // CHANGEDIALOG_H
