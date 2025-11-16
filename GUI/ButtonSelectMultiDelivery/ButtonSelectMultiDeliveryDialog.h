#ifndef BUTTONSELECTMULTIDELIVERYDIALOG_H
#define BUTTONSELECTMULTIDELIVERYDIALOG_H

#include <QDialog>
#include <QBuffer>
#include <QByteArray>
#include <QIODevice>
#include "XServiceForLayers.h"
#include "XDateTime.h"
#include "XIntClass.h"


namespace Ui {
class ButtonSelectMultiDeliveryDialog;
}

class	GUIFormBase;

class ButtonSelectMultiDeliveryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	GUIFormBase	*ParentGUI;
public:
    explicit ButtonSelectMultiDeliveryDialog(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonSelectMultiDeliveryDialog();

	bool	RetMode;

	IntList 	SelectedLotAutoCount;
	QString		SelectedLotID;
	QString		SelectedLotName;
	XDateTime	SelectedLastUpdated;
	QString		SelectedRemark;
	IntList		SubLotNumber;

	bool	RxSync(QByteArray &f);
	bool	RxSync(QIODevice &Buff);

	virtual	void	TxSync(QBuffer &f);

	void	CreateNewLot(const QString &LotID ,const QString &LotName ,bool Synchronized=true);
private slots:
    void on_ButtonCreate_clicked();
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::ButtonSelectMultiDeliveryDialog *ui;

	IntList	LotAutoCounts;

	bool SelectLotAction(void);
	bool ExecuteCreateNew(void);
};

#endif // BUTTONSELECTMULTIDELIVERYDIALOG_H
