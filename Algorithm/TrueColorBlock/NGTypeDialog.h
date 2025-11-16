#ifndef NGTYPEDIALOG_H
#define NGTYPEDIALOG_H

#include <QDialog>
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "mtColorFrame.h"
#include "XServiceForLayers.h"

namespace Ui {
    class NGTypeDialog;
}

class	TrueColorBlockLibNGTypeItem;

class NGTypeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	TrueColorBlockLibNGTypeItem	*Item;
	ShowRGBSpace		ColorZoneRGB;
	SelectColorSample	ColorSamples;
	ColorLogic			ColorZone;
public:
    explicit NGTypeDialog(LayersBase *base ,TrueColorBlockLibNGTypeItem *Item ,QWidget *parent = 0);
    ~NGTypeDialog();

private slots:
    void on_pushButtonAddColor_clicked();

    void on_pushButtonEliminateColor_clicked();

    void on_pushButtonOK_clicked();

    void on_pushButtonClear_clicked();

	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
	void	SlotAddEliminated(void);
	void	SlotDelEliminated(void);

private:
    Ui::NGTypeDialog *ui;
};

#endif // NGTYPEDIALOG_H
