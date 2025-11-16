#ifndef LOADAUTOSAVEIMAGEDIALOG_H
#define LOADAUTOSAVEIMAGEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XAutoSaveImage.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class LoadAutoSaveImageDialog;
}

class LoadAutoSaveImageDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit LoadAutoSaveImageDialog(LayersBase *base ,QWidget *parent = 0);
    ~LoadAutoSaveImageDialog();

	BandImageFileContainer	FoundFile;
	BandImageFileList		*Selected;

private slots:
    void on_checkBoxAllDrives_clicked();
    void on_pushButtonStartSearch_clicked();
    void on_tableWidgetFound_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::LoadAutoSaveImageDialog *ui;
};


#endif // LOADAUTOSAVEIMAGEDIALOG_H
