#ifndef SETALIGNMENTLARGEHEADLINEDIALOG_H
#define SETALIGNMENTLARGEHEADLINEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SetAlignmentLargeHeadLineDialog;
}

class SetAlignmentLargeHeadLineDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SetAlignmentLargeHeadLineDialog(LayersBase *base,QWidget *parent = nullptr);
    ~SetAlignmentLargeHeadLineDialog();

	bool		UseHeadAlignment		;
	int			MaxHeadAlignmentX		;
	int			MaxHeadAlignmentY		;
	int			SkipHeadAlignmentX		;
	int			SkipHeadAlignmentY		;
	int			HeadAlignmentDifColor	;
	int			HeadAlignmentMinSize	;
	int			HeadAlignmentStep		;

	void		SetInitial(void);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SetAlignmentLargeHeadLineDialog *ui;
};

#endif // SETALIGNMENTLARGEHEADLINEDIALOG_H
