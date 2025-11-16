#ifndef SELECTPRINTERDIALOG_H
#define SELECTPRINTERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QModelIndex>
#include "XDateTime.h"
#include <QByteArray>
#include <QBuffer>
#include "XIntClass.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectPrinterDialog;
}
class	ButtonOutputToPrinter;

class	PrinterButton : public QPushButton
{
	Q_OBJECT
public:
	int	ID;

	PrinterButton(int id, QWidget *parent);

signals:
	void	SignalClicked(int id);
protected:
	void	SlotClicked();
};


class SelectPrinterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ButtonOutputToPrinter	*Parent;

	int		CountOfButton;
	PrinterButton	**Button;

public:
	int	SelectedPrinterNo;

    explicit SelectPrinterDialog(ButtonOutputToPrinter *p ,LayersBase *pbase ,QWidget *parent = 0);
    ~SelectPrinterDialog();

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonPrinter1_clicked();
	void	SlotClicked(int id);
private:
    Ui::SelectPrinterDialog *ui;
};

#endif // SELECTPRINTERDIALOG_H
