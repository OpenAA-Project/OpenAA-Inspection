#ifndef THRESHOLDAREASHADER_H
#define THRESHOLDAREASHADER_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
    class ThresholdAreaShader;
}

class ThresholdAreaShader : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ThresholdAreaShader(LayersBase *Base,QWidget *parent = 0);
    ~ThresholdAreaShader();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_pushButtonChangeLib_clicked();
    void on_ButtonReflectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonReflectSaveParts_clicked();
    void on_ButtonClose_clicked();

private:
    Ui::ThresholdAreaShader *ui;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmLibraryListContainer	LibIDList;

	int		CellSize;
	double	AdoptRate;	//çÃópó¶
	bool	Fixed;
	double	Average;
	double	Sigma;		//ïWèÄïŒç∑

	void	CreateThreshld(void);
	void	GetDataFromWindow(void);
	void	ShowLibrary(void);
};

#endif // THRESHOLDAREASHADER_H
