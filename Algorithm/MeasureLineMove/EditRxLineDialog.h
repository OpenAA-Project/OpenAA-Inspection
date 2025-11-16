#ifndef EDITRXLINEDIALOG_H
#define EDITRXLINEDIALOG_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"

namespace Ui {
class EditRxLineDialog;
}

class EditRxLineDialog : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    int HistgramPage;
public:
    explicit EditRxLineDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~EditRxLineDialog();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_pushButtonChangeLib_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_pushButtonTest_clicked();
    void on_ButtonClose_clicked();

    void on_pushButtonUpdateRxValue_clicked();

    void on_pushButtonChangeItemID_clicked();

private:
    Ui::EditRxLineDialog *ui;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;
	bool	OnChanging;

	HistgramTypeListInAlgoContainer	HContainer;

	void	GetDataFromWindow(void);
};

#endif // EDITRXLINEDIALOG_H
