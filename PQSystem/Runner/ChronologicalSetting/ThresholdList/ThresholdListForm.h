#ifndef THRESHOLDLISTFORM_H
#define THRESHOLDLISTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"

namespace Ui {
class ThresholdListForm;
}

class ThresholdListForm : public PQSystemRunner
{
    Q_OBJECT
    AlgorithmBasePointerContainer 	AlgorithmContainer;
	AlgorithmBase					*CurrentAlgorithm;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmLibraryList			*CurrentLibrary;    
public:
	int	ResultRelationCode;

    explicit ThresholdListForm(LayersBase *base ,const QString &root ,const QString &name
							,QWidget *parent = 0);
    ~ThresholdListForm();
    
    virtual	bool	Initial(void)   override;
	virtual	const QString	GetPath(void)			override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemThresholdList";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemThresholdList.dat";  }
protected:
	virtual	void showEvent(QShowEvent *event)	override;

private slots:
    void on_pushButtonSelectMaster_clicked();
    void on_listWidgetAlgorithm_clicked(const QModelIndex &index);
    void on_tableWidgetLibrary_clicked(const QModelIndex &index);
    void on_pushButtonStartSearch_clicked();
    void on_pushButtonView_clicked();
    void on_pushButtonExcel_clicked();

private:
    Ui::ThresholdListForm *ui;
};

#endif // THRESHOLDLISTFORM_H
