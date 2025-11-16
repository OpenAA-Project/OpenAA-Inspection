#ifndef BLADENGLISTFORM_H
#define BLADENGLISTFORM_H

#include "XGUIFormBase.h"
#include "mtGraph.h"
#include "mtLineGraph.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XServiceForLayers.h"
#include "XDateTime.h"
#include "libxl.h"
using namespace libxl;

namespace Ui {
class BladeNGListForm;
}

class	ShowPrintTotalBladeForm;
class	EasyPropertyDentMeasureForm;
class	BladeNGListForm;

#define	MaxCountGraphLine	10
const	int	MaxNGCount=1000;

class	BladeList
{
	friend class BladeNGListForm;

	BladeNGListForm	*Parent;
public:
	EachMaster	*Machine;
	int			LibID;
	int			UniqueID;
	int			IndexInMachine;
	int			Index;
	int			StartIndex;

	BladeList(int index,BladeNGListForm *p);
	
};
class BladeNGListForm : public GUIFormBase
{
    Q_OBJECT

 	ShowPrintTotalBladeForm		*ShowPrintTotalBladePointer;
	EasyPropertyDentMeasureForm	*EasyPropertyDentMeasurePointer[10];   

	BladeList	*BladeListDim[MaxCountGraphLine];
	int			CountGraphLine;
	int			LastInspectionID;
public:
    explicit BladeNGListForm(LayersBase *Base ,QWidget *parent = 0);
    ~BladeNGListForm();
    
	virtual	void	Prepare(void) override;
	virtual void	ReadyParam(void) override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	virtual void	StartLot(void)override;
	void	Clear(void);
private slots:
    void on_pushButtonExcelOut_clicked();
	void	ResizeAction();
	void	SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK);
    void on_pushButtonReDraw_clicked();
    	
private:
    Ui::BladeNGListForm *ui;

	Book	*XLSXBook;
	Sheet	*XLSXSheet;
	Format	*Lang;
	Font	*Fnt;
	void	SetBladeList(EachMaster *M);
	void	SetLabels(void);
	void	ShowData(void);

	void	WriteCell (int Row, int Col ,const QString &Str);
	void	WriteCellV(int Row, int Col ,const QVariant &Data);
};

#endif // BLADENGLISTFORM_H
