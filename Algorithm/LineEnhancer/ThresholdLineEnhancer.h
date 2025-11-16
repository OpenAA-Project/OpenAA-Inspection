#ifndef THRESHOLDLINEENHANCER_H
#define THRESHOLDLINEENHANCER_H

#include <QWidget>
#include "ui_ThresholdLineEnhancer.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

class ThresholdLineEnhancer : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	ThresholdLineEnhancer(LayersBase *Base,QWidget *parent = 0);
	~ThresholdLineEnhancer();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::ThresholdLineEnhancerClass ui;
	AlgorithmItemIndependentPack	*IData;
	AlgorithmLibraryListContainer	LibIDList;

	double	EmphasizeRate;
	int32	MaxLineWidth;
	int		StepDot;
	int32	SelfSearch;

	void	CreateThreshld(void);
	void	GetDataFromWindow(void);
	void	ShowLibrary(void);

private slots:
	void on_pushButtonChangeLib_clicked();
	void on_ButtonClose_clicked();
	void on_ButtonLoadFromLibrary_clicked();
	void on_ButtonSaveToLibrary_clicked();
	void on_ButtonReflectAllBlocks_clicked();
	void on_ButtonReflectOnlyBlock_clicked();
	void on_ButtonReflectSaveParts_clicked();
};

#endif // THRESHOLDLINEENHANCER_H
