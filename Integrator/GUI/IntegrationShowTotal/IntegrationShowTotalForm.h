#ifndef INTEGRATIONSHOWTOTALFORM_H
#define INTEGRATIONSHOWTOTALFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "libxl.h"
using namespace libxl;


namespace Ui {
class IntegrationShowTotalForm;
}

struct	InfoOkNg
{
	int	OKCount;
	int	NGCount;
};


class IntegrationShowTotalForm : public GUIFormBase
{
    Q_OBJECT
    
	struct	InfoOkNg	*InfoOkNgDim;
	int					InfoOkNgDimCount;

public:
	bool	ModeShowTotal;
	bool	ModeShowAllResult;
	bool	ModeShowEachResult;


    explicit IntegrationShowTotalForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationShowTotalForm();
    
	virtual void	ReadyParam(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;

private slots:
    void on_PushButtonReset_clicked();
    void on_pushButtonExcelSave_clicked();
	void	SlotDoneLoadResult(InspectionList *n);
	void	ResizeAction();
private:
    Ui::IntegrationShowTotalForm *ui;
	void	ShowData(void);

	Book	*XLSXBook;
	Sheet	*XLSXSheet;
	Format	*Lang;
	Font	*Fnt;

	void	WriteCell(int Row, int Col ,const QString &Str);
	void	WriteCellV(int Row, int Col ,const QVariant &Data);
	QImage	LoadDataFromMaster(int masterCode);
	int			SetNGImageToExcel(InspectionList *L, int Printout_MaxCountfNGImage,int N,int &Row);
	QStringList	GetInformation(InspectionList *L,NGPoint *Rp);

signals:
	void	SignalUpdated();
};

#endif // INTEGRATIONSHOWTOTALFORM_H
