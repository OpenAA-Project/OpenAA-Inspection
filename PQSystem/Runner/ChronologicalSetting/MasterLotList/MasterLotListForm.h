#ifndef MASTERLOTLISTFORM_H
#define MASTERLOTLISTFORM_H

#include <QWidget>
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"

namespace Ui {
class MasterLotListForm;
}

class MasterLotListForm : public PQSystemRunner
{
    Q_OBJECT
    
public:
    explicit MasterLotListForm(LayersBase *base ,const QString &root ,const QString &name
							,QWidget *parent = 0);
    ~MasterLotListForm();
    
    virtual	bool	Initial(void)   override;
	virtual	const QString	GetPath(void)			override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemMasterLotList";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemMasterLotList.dat";  }
protected:
	virtual	void showEvent(QShowEvent *event)	override;

private slots:
    void on_pushButtonStartSearch_clicked();
    void on_pushButtonView_clicked();
    void on_pushButtonExcel_clicked();

private:
    Ui::MasterLotListForm *ui;
};

#endif // MASTERLOTLISTFORM_H
