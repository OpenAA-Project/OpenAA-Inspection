#ifndef SELECTLOTDIALOG_H
#define SELECTLOTDIALOG_H

#include <QDialog>
#include "SelectLotForm.h"
#include "XServiceForLayers.h"
#include "XLotInformation.h"

namespace Ui {
    class SelectLotDialog;
}
class	SelectLotDialog;

class	SelectLotFormForDialog : public SelectLotForm
{
	SelectLotDialog	*ParentDialog;
public:
	SelectLotFormForDialog(LayersBase *pbase ,SelectLotDialog *_ParentDialog,QWidget *parent,QWidget *rootParent)
		:SelectLotForm(pbase ,parent,rootParent,1000){	ParentDialog=_ParentDialog;	}

	virtual	void	TxSync(QBuffer &Buff);
};

class	LotInformationWithCounted : public LotInformation
{
	int	Counter;
public:
	LotInformationWithCounted(LayersBase *base):LotInformation(base){	Counter=0;	}

	virtual	void	ExecuteEveryInspectInMaster(int InspectionID);
	virtual	void	ExecuteEveryInspectInSlave(int InspectionID,int Phase ,int Page);
};

//---------------------------------------------------------------------------

class SelectLotDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	SelectLotFormForDialog	*SelectLot;
public:
    explicit SelectLotDialog(LayersBase *Base,QWidget *parent = 0);
    ~SelectLotDialog();

	int		LotCountNumber;

	bool	RetMode;
	int			SelectedLotAutoCount;
	QString		SelectedLotID;
	QString		SelectedLotName;
	XDateTime	SelectedLastUpdated;
	QString		SelectedRemark;

	bool	RxSync(QByteArray &f);
	void	LoadFromWindow(void);

private slots:
	void	SlotClose();
private:
    Ui::SelectLotDialog *ui;
};

#endif // SELECTLOTDIALOG_H
