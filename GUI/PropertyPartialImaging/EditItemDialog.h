#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QDialog>
#include "XTypeDef.h"
#include <QString>
#include "XServiceForLayers.h"

namespace Ui {
class EditItemDialog;
}

class EditItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditItemDialog(LayersBase *base ,bool Editable ,QWidget *parent = 0);
    ~EditItemDialog();

	int32			Priority;
	bool			SaveTargetImage;
	bool			SaveOnlyInNG;
	int32			BufferType;
	QString			ItemName;

	void	Initial(void);

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::EditItemDialog *ui;
};

#endif // EDITITEMDIALOG_H
