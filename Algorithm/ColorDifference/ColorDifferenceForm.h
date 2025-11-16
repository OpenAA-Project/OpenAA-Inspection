#ifndef COLORDIFFERENCEFORM_H
#define COLORDIFFERENCEFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XPasswordQWidget.h"

namespace Ui {
class ColorDifferenceForm;
}
class ColorDifferenceForm;

class	HSVMap : public QWidget
{
    Q_OBJECT
		
	ColorDifferenceForm	*Parent;
	double	ZoomRate;
	QImage	HSVImageMap;
	QTimer	TM;
	bool	FlapToShowThreshold;
public:
	int	V;

	HSVMap(ColorDifferenceForm *p);

	void	SetV(int v);
private:
	virtual	void paintEvent ( QPaintEvent * event ) 		override;
	virtual	void mouseReleaseEvent ( QMouseEvent * event )	override;
	virtual	void resizeEvent ( QResizeEvent * event )		override;

signals:
	void	SignalClickRGB(int R ,int G ,int B);

private slots:
	void	SlotTimeOut();
};

class ColorDifferenceForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    
	HSVMap					PanelHSVMap;
public:
    explicit ColorDifferenceForm(LayersBase *Base,QWidget *parent = 0);
    ~ColorDifferenceForm();
    
	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	bool	IsInsideInThresholdOK(int R,int G,int B);
	bool	IsInsideInThresholdNG(int R,int G,int B);
	bool	IsInsideInCurrentColor(int R,int G,int B);
private slots:
    void on_verticalSliderY_valueChanged(int value);
    void on_spinBoxK_valueChanged(int arg1);
    void on_listWidgetOKBrightness_currentRowChanged(int currentRow);
    void on_listWidgetNGBrightness_currentRowChanged(int currentRow);
    void on_toolButtonDelOKColor_clicked();
    void on_toolButtonDelNGColor_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
	void	SlotClickRGB(int R ,int G ,int B);
    void on_toolButtonCurrentColor_clicked();
    void on_listWidgetOKBrightness_pressed(const QModelIndex &index);
    void on_listWidgetNGBrightness_pressed(const QModelIndex &index);
    void on_pushButtonSetItemName_clicked();
    void on_pushButtonOutputFlowList_clicked();
private:
    Ui::ColorDifferenceForm *ui;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmLibraryListContainer	LibIDList;

	void	GetDataFromWindow(void);
	void	ShowOKColorList(void);
	void	ShowNGColorList(void);
	void	ShowRGB(int R, int G ,int B);
	void	ShowThreshold(void);
	void	Calc(void);
};



#endif // COLORDIFFERENCEFORM_H
