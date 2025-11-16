#ifndef EDITDCODEDIALOG_H
#define EDITDCODEDIALOG_H

#include <QDialog>
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGerberFastPacket.h"
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditDCodeDialog;
}

class EditDCodeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	GerberApertureInfoContainer *ApertureList;
public:
    explicit EditDCodeDialog(int FileLayerNo ,LayersBase *base, GerberApertureInfoContainer *ApertureList ,QWidget *parent = 0);
    ~EditDCodeDialog();
    
	BoolList	SelectedList;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonCreateDCode_clicked();
    void on_tableWidgetDCode_doubleClicked(const QModelIndex &index);

private:
    Ui::EditDCodeDialog *ui;
};

#endif // EDITDCODEDIALOG_H
