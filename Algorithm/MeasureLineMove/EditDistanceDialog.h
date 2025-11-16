#ifndef EDITDISTANCEDIALOG_H
#define EDITDISTANCEDIALOG_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"

namespace Ui {
    class EditDistanceDialog;
}

class MeasureLineMoveDistanceItem;

class EditDistanceDialog : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    int HistgramPage;
public:
    explicit EditDistanceDialog(LayersBase *Base,QWidget *parent = 0);
    ~EditDistanceDialog();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_pushButtonChangeLib_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_pushButtonTest_clicked();
    void on_ButtonClose_clicked();
    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);
    void on_doubleSpinBoxThresholdM_valueChanged(double arg1);
    void on_doubleSpinBoxThresholdM_2_valueChanged(double arg1);
    void on_doubleSpinBoxThresholdP_valueChanged(double arg1);
    void on_doubleSpinBoxThresholdP_2_valueChanged(double arg1);
    void on_groupBoxTransfer_clicked();
    void on_spinBoxTransferInfo_valueChanged(int arg1);

    void on_pushButtonChangeItemID_clicked();

private:
    Ui::EditDistanceDialog *ui;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;
	bool	OnChanging;

	HistgramTypeListInAlgoContainer	HContainer;
	void	ShowHistgramList(void);
	void	GetDataFromWindow(void);
	void	ShowLibrary(void);
	void	ShowThreshold(void);
    MeasureLineMoveDistanceItem *GetItem(void);

	double	XTrasnformUnitFromPixel(double Pixel);
	double	XTransformPixelFromUnit(double Unit);
};

#endif // EDITDISTANCEDIALOG_H
