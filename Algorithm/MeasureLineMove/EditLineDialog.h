#ifndef EDITLINEDIALOG_H
#define EDITLINEDIALOG_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"

namespace Ui {
    class EditLineDialog;
}

class EditLineDialog : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    int HistgramPage;
public:
    explicit EditLineDialog(LayersBase *Base,QWidget *parent = 0);
    ~EditLineDialog();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_pushButtonChangeLib_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_pushButtonTest_clicked();
    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);
    void on_ButtonClose_clicked();
    void on_EditSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDot_valueChanged(double arg1);
    void on_doubleSpinBoxThresholdM_valueChanged(double arg1);
    void on_doubleSpinBoxThresholdM_2_valueChanged(double arg1);
    void on_doubleSpinBoxThresholdP_valueChanged(double arg1);
    void on_doubleSpinBoxThresholdP_2_valueChanged(double arg1);

    void on_pushButtonChangeItemID_clicked();

private:
    Ui::EditLineDialog *ui;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;
	bool	OnChanging;

	HistgramTypeListInAlgoContainer	HContainer;
	void	ShowHistgramList(void);
	void	GetDataFromWindow(void);
	void	ShowLibrary(void);
	void	ShowThreshold(void);
};

#endif // EDITLINEDIALOG_H
