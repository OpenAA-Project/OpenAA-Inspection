#ifndef SELECTSMALLLOTFORM_H
#define SELECTSMALLLOTFORM_H

#include <QDialog>
#include <QModelIndex>
#include "XDateTime.h"
#include <QByteArray>
#include <QBuffer>
#include "XIntClass.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectSmallLotForm;
}

class	GUIFormBase;

class SelectSmallLotForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	GUIFormBase	*ParentGUI;
    
public:
    explicit SelectSmallLotForm(bool ShowMode ,LayersBase *pbase ,QWidget *parent=0, QWidget *parentGUI=0);
    ~SelectSmallLotForm();
    
	bool	RetMode;
	int			SelectedLotAutoCount;
	QString		SelectedLotID;
	int			SelectedIDNumber;
	QString		SelectedLotName;
	XDateTime	SelectedLastUpdated;
	QString		SelectedRemark;
	int			RetCmd;

	virtual	void	closeEvent ( QCloseEvent * event )	override;
	bool	RxSync(QByteArray &f);
	bool	RxSync(QIODevice &Buff);

	virtual	void	TxSync(QBuffer &f);

private:
	IntList	LotAutoCounts;

	bool SelectLotAction(void);
	bool ExecuteCreateNew(void);

private slots:
    void on_ButtonCreate_clicked();
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();
    void on_tableWidgetLot_clicked(const QModelIndex &index);
    void on_pushButtonIncrement_clicked();

private:
    Ui::SelectSmallLotForm *ui;
};

#endif // SELECTSMALLLOTFORM_H
