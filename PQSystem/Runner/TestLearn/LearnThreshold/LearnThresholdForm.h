#ifndef LEARNTHRESHOLDFORM_H
#define LEARNTHRESHOLDFORM_H

#include <QWidget>
#include <QModelIndex>
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"

namespace Ui {
class LearnThresholdForm;
}

class LearnThresholdForm : public PQSystemRunner
{
    Q_OBJECT
    AlgorithmBasePointerContainer 	AlgorithmContainer;
	AlgorithmBase					*CurrentAlgorithm;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmLibraryList			*CurrentLibrary;    
public:
	int	ResultRelationCode;

    explicit LearnThresholdForm(LayersBase *base ,const QString &root ,const QString &name
							,QWidget *parent = 0);
    ~LearnThresholdForm();
    
    virtual	bool	Initial(void)   override;
	virtual	const QString	GetPath(void)			override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemLearnThreshold";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemLearnThreshold.dat";  }
protected:
	virtual	void showEvent(QShowEvent *event)	override;

private slots:
    void on_pushButtonSelectMaster_clicked();
    void on_listWidgetAlgorithm_clicked(const QModelIndex &index);
    void on_tableWidgetLibrary_clicked(const QModelIndex &index);
    void on_pushButtonStartSearch_clicked();
    void on_pushButtonSimulateView_clicked();
    void on_pushButtonTestByImage_clicked();
    void on_pushButtonUpdate_clicked();

private:
    Ui::LearnThresholdForm *ui;
};

#endif // LEARNTHRESHOLDFORM_H
