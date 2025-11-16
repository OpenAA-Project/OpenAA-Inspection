#ifndef MONOOUTLINEFORM_H
#define MONOOUTLINEFORM_H

#include <QDialog>
#include "ui_MonoOutlineForm.h"
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithm.h"
#include "XOutlineInspect.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

class	OutlineBase;
class	mtColorFrame;

class MonoOutlineForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

	int		YMax;
	bool	EditReEntrant;
public:
	MonoOutlineForm(LayersBase *Base,QWidget *parent = 0);
	~MonoOutlineForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
private:
	Ui::MonoOutlineFormClass ui;

	mtLineGraph						LGraphInside;
	mtGStick						GraphMasterInside;
	mtGStick						GraphTargetInside;
	mtGStick						GraphThreshNInside;
	mtGStick						GraphThreshBInside;
	mtGStick						GraphInside;

	mtLineGraph						LGraphTrInside;
	mtGStick						GraphMasterTrInside;
	mtGStick						GraphTargetTrInside;
	mtGStick						GraphThreshNTrInside;
	mtGStick						GraphThreshBTrInside;
	mtGStick						GraphTrInside;

	mtLineGraph						LGraphTrOutside;
	mtGStick						GraphMasterTrOutside;
	mtGStick						GraphTargetTrOutside;
	mtGStick						GraphThreshNTrOutside;
	mtGStick						GraphThreshBTrOutside;
	mtGStick						GraphTrOutside;

	mtLineGraph						LGraphOutside;
	mtGStick						GraphMasterOutside;
	mtGStick						GraphTargetOutside;
	mtGStick						GraphThreshNOutside;
	mtGStick						GraphThreshBOutside;
	mtGStick						GraphOutside;

	AlgorithmItemIndependentPack	*IData;

	OutlineBase	*GetOutlineBase(void);
	AlgorithmLibraryListContainer	LibIDList;
	OutlineThreshold	TmpThreshold;

	mtColorFrame	*MasterPanel;
	mtColorFrame	*TargetPanel;
	mtColorFrame	*ThresholdNPanel;
	mtColorFrame	*ThresholdBPanel;

	void	GetHistogramData(void);
	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	ShowThreshold(void);
	void	LoadThresholdDataFromWindow(OutlineThreshold *W);

private slots:
	void on_ButtonOptimizeAll_clicked();
	void on_ButtonOptimizeOnly_clicked();
	void on_EditNInsideColorH_valueChanged(int);
	void on_EditNInsideColorL_valueChanged(int);
	void on_EditBInsideColorH_valueChanged(int);
	void on_EditBInsideColorL_valueChanged(int);
	void on_EditNTrInsideColorH_valueChanged(int);
	void on_EditNTrInsideColorL_valueChanged(int);
	void on_EditBTrInsideColorH_valueChanged(int);
	void on_EditBTrInsideColorL_valueChanged(int);
	void on_EditNTrOutsideColorH_valueChanged(int);
	void on_EditNTrOutsideColorL_valueChanged(int);
	void on_EditBTrOutsideColorH_valueChanged(int);
	void on_EditBTrOutsideColorL_valueChanged(int);
	void on_EditNOutsideColorH_valueChanged(int);
	void on_EditNOutsideColorL_valueChanged(int);
	void on_EditBOutsideColorH_valueChanged(int);
	void on_EditBOutsideColorL_valueChanged(int);
	void on_pushButtonClose_clicked();
	void on_ButtonLoadFromLibrary_clicked();
	void on_ButtonReflectAllBlocks_clicked();
	void on_ButtonSaveToLibrary_clicked();
	void on_ButtonRefrectOnlyBlock_clicked();
	void on_ButtonCalc_clicked();
	void	SlotLineGraphDClickInside(int X,int Y);
	void	SlotLineGraphDClickTrInside(int X,int Y);
	void	SlotLineGraphDClickTrOutside(int X,int Y);
	void	SlotLineGraphDClickOutside(int X,int Y);
};

#endif // MONOOUTLINEFORM_H
