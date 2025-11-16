#ifndef VARIETYLISTFORM_H
#define VARIETYLISTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"
#include "SelectLotForm.h"

namespace Ui {
class VarietyListForm;
}

class VarietyListForm : public PQSystemRunner
{
    Q_OBJECT
    AlgorithmBasePointerContainer 	AlgorithmContainer;
	AlgorithmBase					*CurrentAlgorithm;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmLibraryList			*CurrentLibrary;
	SelectLotForm					LotForm;
public:
	int							ResultRelationCode;
	FlexArea					SelectArea;

    explicit VarietyListForm(LayersBase *base ,const QString &root ,const QString &name
							,QWidget *parent = 0);
    ~VarietyListForm();
    
    virtual	bool	Initial(void)   override;
	virtual	const QString	GetPath(void)			override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemVarietyList";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemVarietyList.dat";  }
protected:
	virtual	void showEvent(QShowEvent *event)	override;

private slots:
    void on_pushButtonSelectArea_clicked();
    void on_pushButtonSelectMaster_clicked();
    void on_listWidgetAlgorithm_clicked(const QModelIndex &index);
    void on_tableWidgetLibrary_clicked(const QModelIndex &index);
    void on_pushButtonStartSearch_clicked();
    void on_pushButtonView_clicked();
    void on_pushButtonExcel_clicked();

private:
    Ui::VarietyListForm *ui;
};

#endif // VARIETYLISTFORM_H
