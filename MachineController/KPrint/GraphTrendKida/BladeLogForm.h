#ifndef BLADELOGFORM_H
#define BLADELOGFORM_H

#include <QWidget>
#include <QResizeEvent>
#include "XServiceForLayers.h"
#include "XDateTime.h"
#include "libxl.h"
using namespace libxl;

namespace Ui {
class BladeLogForm;
}
class GraphTrendKidaForm;

const	int	MaxNGCount=1000;

class BladeLogForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    GraphTrendKidaForm	*Parent;
	int		CountGraphLine;
	int		BladeItemID[100];
	int		*InspectionID;
	double	*NGList[100];
	int		RowCount;
	XDateTime			*InspectionTime;
	QStringList	Headers;

public:
    explicit BladeLogForm(GraphTrendKidaForm *p ,LayersBase *Base ,QWidget *parent = 0);
    ~BladeLogForm();
    
private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonExcel_clicked();

private:
    Ui::BladeLogForm *ui;

	Book	*XLSXBook;
	Sheet	*XLSXSheet;
	Format	*Lang;
	Font	*Fnt;

	virtual	void resizeEvent ( QResizeEvent * event ) override;
	void	WriteCell (int Row, int Col ,const QString &Str);
	void	WriteCellV(int Row, int Col ,const QVariant &Data);
};

#endif // BLADELOGFORM_H
