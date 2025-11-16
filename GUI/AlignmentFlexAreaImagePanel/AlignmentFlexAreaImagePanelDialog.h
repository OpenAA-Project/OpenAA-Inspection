#ifndef ALIGNMENTFLEXAREAIMAGEPANELDIALOG_H
#define ALIGNMENTFLEXAREAIMAGEPANELDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class AlignmentFlexAreaImagePanelDialog;
}

class AlignmentFlexAreaImagePanelDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	bool	OnChanging;
public:
    explicit AlignmentFlexAreaImagePanelDialog(int ItemID ,int GlobalSearchDot ,int SearchDot ,bool KeepBW ,LayersBase *base ,QWidget *parent = 0);
    ~AlignmentFlexAreaImagePanelDialog();

	int		GlobalSearchDot;
	int		SearchDot;
	bool	KeepBW;

    int     Page;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();

    void on_spinBoxGlobalSearchDot_valueChanged(int arg1);

    void on_spinBoxSearchDot_valueChanged(int arg1);

private:
    Ui::AlignmentFlexAreaImagePanelDialog *ui;
};

#endif // ALIGNMENTFLEXAREAIMAGEPANELDIALOG_H
