#ifndef SHOWMARKFORM_H
#define SHOWMARKFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include <QModelIndex>
#include "XAlgorithmLibrary.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XSwitchPhase.h"

namespace Ui {
class ShowMarkForm;
}

class ShowMarkForm : public QWidget,public ServiceForLayers,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit ShowMarkForm(LayersBase *Base,QWidget *parent = 0);
    ~ShowMarkForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;

private slots:
    void on_tableWidgetPhaseList_clicked(const QModelIndex &index);
    void on_ButtonReflectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonClose_clicked();

private:
    Ui::ShowMarkForm *ui;

	bool	OnChanging;
};

#endif // SHOWMARKFORM_H
