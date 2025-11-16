#ifndef LOGLISTDIALOG_H
#define LOGLISTDIALOG_H

#include <QDialog>
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
class LogListDialog;
}

class GraphTrendColorDifferenceForm;
struct	RunningColorHSVE;

struct	LogList
{
	struct	RunningColorHSVE	*Point[100];
};

class LogListDialog : public QDialog
{
    Q_OBJECT
    
	GraphTrendColorDifferenceForm	*Parent;
	struct	LogList	*LogListDim;
	int		LogListCount;
public:
    explicit LogListDialog(GraphTrendColorDifferenceForm *p ,QWidget *parent = 0);
    ~LogListDialog();
    
	void	MakeLogList(void);
	void	ShowList(void);
private slots:
    void on_pushButtonExcel_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::LogListDialog *ui;

	virtual	void	resizeEvent ( QResizeEvent * event )	override;

	Book	*XLSXBook;
	Sheet	*XLSXSheet;
	Format	*Lang;
	Font	*Fnt;

	void	WriteCell (int Row, int Col ,const QString &Str);
	void	WriteCellV(int Row, int Col ,const QVariant &Data);
};

#endif // LOGLISTDIALOG_H
