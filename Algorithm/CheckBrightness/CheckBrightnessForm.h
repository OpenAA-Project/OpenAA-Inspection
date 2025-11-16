#ifndef CHECKBRIGHTNESSFORM_H
#define CHECKBRIGHTNESSFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class CheckBrightnessForm;
}

class CheckBrightnessForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit CheckBrightnessForm(LayersBase *Base,QWidget *parent = 0);
    ~CheckBrightnessForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_pushButtonSetThresholdOne_clicked();
    void on_pushButtonSetThresholdAll_clicked();
    void on_ButtonClose_clicked();

private:
    Ui::CheckBrightnessForm *ui;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmLibraryListContainer	LibIDList;
	DisplaySimPanel		SimPanel;

	void	ShowThreshold(void);
	void	GetDataFromWindow(void);
	void	CreateThreshld(void);
};

#endif // CHECKBRIGHTNESSFORM_H
