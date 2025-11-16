#ifndef ADDEDITITEMDIALOG_H
#define ADDEDITITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"
namespace Ui {
class AddEditItemDialog;
}

class AddEditItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit AddEditItemDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~AddEditItemDialog();

	int		SearchDot	;
	double	MaxDegree	;
	int		LineLength	;
	double	MinVar		;

    void    Initial(AlgorithmLibrary *Lib);

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::AddEditItemDialog *ui;
};

#endif // ADDEDITITEMDIALOG_H
