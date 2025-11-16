#ifndef SELECTLOTFORM_H
#define SELECTLOTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XServiceForLayers.h"
#include "XIntegrationBase.h"
#include "PQSystemService.h"

namespace Ui {
class SelectLotForm;
}
class LotList;


class SelectLotForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
public:
    NPListPack<LotListWithResult>	LotContainer;
	LotListWithResult	*CurrentLot;

    explicit SelectLotForm(LayersBase *Base ,QWidget *parent = 0);
    ~SelectLotForm();
    
	void	Clear(void);
	void	Update();

signals:
	void	SignalSelectLine();
private slots:
    void on_tableWidget_itemSelectionChanged();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonSearch_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectLotForm *ui;

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // SELECTLOTFORM_H
