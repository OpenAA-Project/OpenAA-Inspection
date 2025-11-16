#ifndef RESULTVALUEFORM_H
#define RESULTVALUEFORM_H

#include <QWidget>
#include <QModelIndex>
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"
#include "SelectLotForm.h"

namespace Ui {
class ResultValueForm;
}

class ResultValueForm : public PQSystemRunner
{
    Q_OBJECT
     
	AlgorithmBasePointerContainer 	AlgorithmContainer;
	AlgorithmBase					*CurrentAlgorithm;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmLibraryList			*CurrentLibrary;
	SelectLotForm					LotForm;
public:
	int	ResultRelationCode;
	FlexArea					SelectArea;

    explicit ResultValueForm(LayersBase *base ,const QString &root ,const QString &name
							,QWidget *parent = 0);
    ~ResultValueForm();
    
    virtual	bool	Initial(void)   override;
	virtual	const QString	GetPath(void)			override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemResultValue";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemResultValue.dat";  }
protected:
	virtual	void showEvent(QShowEvent *event)	override;

private slots:
    void on_pushButtonSelectMaster_clicked();
    void on_pushButtonSelectArea_clicked();
    void on_listWidgetAlgorithm_clicked(const QModelIndex &index);
    void on_tableWidgetLibrary_clicked(const QModelIndex &index);
    void on_pushButtonStartSearch_clicked();
    void on_pushButtonView_clicked();
    void on_pushButtonExcel_clicked();

private:
    Ui::ResultValueForm *ui;
};

#endif // RESULTVALUEFORM_H
