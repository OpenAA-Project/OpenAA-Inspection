#ifndef EDITIMPORTANCEFORM_H
#define EDITIMPORTANCEFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class EditImportanceForm;
}

class EditImportanceForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditImportanceForm(LayersBase *base, QWidget *parent = 0);
    ~EditImportanceForm();

	int		ImportanceLevel;
	void	SetImportanceLevel(int L);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonOKLevel_clicked();
    void on_pushButtonCancel_clicked();
    void on_radioButtonVeryHigh_clicked(bool checked);
    void on_radioButtonHigh_clicked(bool checked);
    void on_radioButtonNormal_clicked(bool checked);
    void on_radioButtonNotSoHigh_clicked(bool checked);
    void on_spinBoxLevel_valueChanged(int arg1);

private:
    Ui::EditImportanceForm *ui;
};

#endif // EDITIMPORTANCEFORM_H
