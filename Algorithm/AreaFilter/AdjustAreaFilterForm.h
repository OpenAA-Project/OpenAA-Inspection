#ifndef ADJUSTAREAFILTERFORM_H
#define ADJUSTAREAFILTERFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XPasswordQWidget.h"

namespace Ui {
class AdjustAreaFilterForm;
}

class AdjustAreaFilterForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    
public:
    explicit AdjustAreaFilterForm(LayersBase *Base,QWidget *parent = 0);
    ~AdjustAreaFilterForm();

    void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
private slots:
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_pushButtonTransmitItemNameAll_clicked();
    void on_pushButtonChangeLib_clicked();

private:
    Ui::AdjustAreaFilterForm *ui;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmLibraryListContainer	LibIDList;

	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
};

#endif // ADJUSTAREAFILTERFORM_H
