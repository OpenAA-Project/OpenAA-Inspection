#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditItemDialog;
}

class RepeatControlBase;

class EditItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditItemDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~EditItemDialog();

	int		RepeatCount	    ;
	int		MeshSize	    ;
	int		SequenceOffset	;
	bool	GatherAllPhase  ;

	void	Initial(void);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditItemDialog *ui;
    RepeatControlBase	*GetRepeatControlBase(void);
};

#endif // EDITITEMDIALOG_H
