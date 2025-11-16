#ifndef EDITHOLEPOSDIALOG_H
#define EDITHOLEPOSDIALOG_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"

namespace Ui {
    class EditHolePosDialog;
}

class EditHolePosDialog : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditHolePosDialog(LayersBase *Base,QWidget *parent = 0);
    ~EditHolePosDialog();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_pushButtonChangeLib_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);
    void on_pushButtonTest_clicked();

private:
    Ui::EditHolePosDialog *ui;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;

	HistgramTypeListInAlgoContainer	HContainer;
	void	ShowHistgramList(void);
	void	GetDataFromWindow(void);
	void	ShowLibrary(void);
	void	ShowThreshold(void);
};

#endif // EDITHOLEPOSDIALOG_H
