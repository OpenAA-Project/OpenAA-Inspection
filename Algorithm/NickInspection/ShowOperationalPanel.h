#ifndef SHOWOPERATIONALPANEL_H
#define SHOWOPERATIONALPANEL_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"
#include "XNickInspection.h"

namespace Ui {
class ShowOperationalPanel;
}

class ShowOperationalPanel : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    
public:
    explicit ShowOperationalPanel(LayersBase *Base,QWidget *parent = 0);
    ~ShowOperationalPanel();
    
	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonClose_clicked();

private:
    Ui::ShowOperationalPanel *ui;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmLibraryListContainer	LibIDList;

	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	CreateThreshld(void);

	int			NGPercentage;	
	int			RefBrightness;
	bool		EnableWhite;
	AlgorithmLibraryListWithResultContainer	Result;
};

#endif // SHOWOPERATIONALPANEL_H
