#ifndef PANELMAXSTOCKFORM_H
#define PANELMAXSTOCKFORM_H

#include "XGUIFormBase.h"
#include <QStringList>
#include <QLabel>
#include <QSpinBox>

namespace Ui {
class PanelMaxStockForm;
}

class	SignalOperandInt;

class PanelMaxStockForm : public GUIFormBase
{
    Q_OBJECT

	SignalOperandInt	**iRegMaxStock;
public:
	int		*CurrentMaxStock;
	int		TopRegNumber;
	QStringList	StockStringList;
	int			StockStringListCount;

	class	StockLine : public QFrame
	{
	public:
		int			Row;
		QLabel		StockName;
		QSpinBox	StockValue;

		StockLine(PanelMaxStockForm *parent,int row);
	};
	StockLine	**StockLineData;

    explicit PanelMaxStockForm(LayersBase *Base ,QWidget *parent = 0);
    ~PanelMaxStockForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private slots:
    void on_pushButtonSet_clicked();
	void	OperandChanged();
private:
    Ui::PanelMaxStockForm *ui;
};

#endif // PANELMAXSTOCKFORM_H
