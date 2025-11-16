#ifndef SHOWNGMAPDIALOG_H
#define SHOWNGMAPDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

namespace Ui {
class ShowNGMapDialog;
}
class IntegrationShowNGMapButtonForm;
class ShowNGMapDialog;


class	NGMapWidget : public QWidget , public ServiceForLayers
{
	friend	class ShowNGMapDialog;

	ShowNGMapDialog	*Parent;
	QImage	MasterImage;
	QImage	NGMapImage;
public:
	NGMapWidget(LayersBase *base ,ShowNGMapDialog *p);

private slots:

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};


class ShowNGMapDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
	friend	class	NGMapWidget;

    IntegrationShowNGMapButtonForm	*Parent;
	NGMapWidget		Window;
public:
	int	**NGCountMap;
	int	XLen;
	int	YLen;
	double	XRes,YRes;
	int	NGCount;


    explicit ShowNGMapDialog(LayersBase *base ,IntegrationShowNGMapButtonForm *p,QWidget *parent = 0);
    ~ShowNGMapDialog();
    
private slots:
    void on_pushButtonReview_clicked();
    void on_pushButtonClose_clicked();
    void on_doubleSpinBoxMatrixSizeMM_valueChanged(double arg1);

private:
    Ui::ShowNGMapDialog *ui;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;

	void	AllocateMap(void);
	void	ReleaseMap(void);
};

#endif // SHOWNGMAPDIALOG_H
