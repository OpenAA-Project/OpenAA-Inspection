#ifndef INTEGRATIONNGCATEGORIZEDLISTFORM_H
#define INTEGRATIONNGCATEGORIZEDLISTFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "libxl.h"
using namespace libxl;

namespace Ui {
class IntegrationNGCategorizedListForm;
}
class NGTypeList;

class IntegrationNGCategorizedListForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit IntegrationNGCategorizedListForm(LayersBase *Base,QWidget *parent = 0);
    ~IntegrationNGCategorizedListForm();
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonEXCEL_clicked();

private:
    Ui::IntegrationNGCategorizedListForm *ui;

	virtual	void resizeEvent(QResizeEvent *event)	override;
    void    MakeList(void);
    QString	GetNGName(NGTypeList *p);

	Book	*XLSXBook;
	Sheet	*XLSXSheet;
	Format	*Lang;
	Font	*Fnt;

    void	WriteCell (int Row, int Col ,const QString &Str);
    void	WriteCellV(int Row, int Col ,const QVariant &Data);

};

#endif // INTEGRATIONNGCATEGORIZEDLISTFORM_H
