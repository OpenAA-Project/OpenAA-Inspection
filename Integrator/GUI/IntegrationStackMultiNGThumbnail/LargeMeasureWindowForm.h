#ifndef LARGEMEASUREWINDOWFORM_H
#define LARGEMEASUREWINDOWFORM_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include "XServiceForLayers.h"
#include "XLearningRegist.h"
#include "XPasswordQWidget.h"

namespace Ui {
class LargeMeasureWindowForm;
}
class	LargeMeasureWindowForm;
class	ThumbnailPanel;

class LargeMeasureWindowForm : public QWidget,public ServiceForLayers,public PasswordInQWodget
{
    Q_OBJECT
  
	friend	class	ThumbnailPanel;
	friend	class	FrameLargeWindow;
	friend	class	FrameMasterWindow;

	Qt::WindowFlags	SavedFlag;
	ThumbnailPanel	*Parent;
	QImage	MasterImage;
	QImage	MasterSide1Image;
	QImage	MasterSide2Image;
	QImage	TargetImage;
	QImage	TargetSide1Image;
	QImage	TargetSide2Image;
	QImage	NGTargetImage;
	QImage	NGTargetSide1Image;
	QImage	NGTargetSide2Image;
	QImage	TargetImageWithLine		;
	QImage	TargetSide1ImageWithLine;
	QImage	TargetSide2ImageWithLine;

	QLabel	LabelMasterImage		;
	QLabel	LabelMasterSide1Image	;
	QLabel	LabelMasterSide2Image	;
	QLabel	LabelTargetImage		;
	QLabel	LabelTargetSide1Image	;
	QLabel	LabelTargetSide2Image	;

	QPixmap	PixmapMasterImage		;
	QPixmap	PixmapMasterSide1Image	;
	QPixmap	PixmapMasterSide2Image	;
	QPixmap	PixmapTargetImage		;
	QPixmap	PixmapTargetSide1Image	;
	QPixmap	PixmapTargetSide2Image	;

	LearningMenu	LearningMenuDim[100];
	int				LearningMenuDimNumb;
	QTimer	FlipTimer;
	bool	ShowingMasterImage;
public:
    explicit LargeMeasureWindowForm(ThumbnailPanel *p ,QWidget *parent = 0);
    ~LargeMeasureWindowForm();

	void	Initial(void);
	bool	ShowDrawNGMark(void);

signals:
	void	SignalShowDetail();
private slots:
    void on_PushButtonExpand1Side_clicked();
    void on_PushButtonExpand2Side_clicked();
    void on_PushButtonOKbyDistance_clicked();
    void on_pushButtonClose_clicked();
	void	SlotTimeOut();
private:
    Ui::LargeMeasureWindowForm *ui;

	//virtual	void	showEvent(QShowEvent *event) override;
	void	SendLearning(int LearningMenuID, bool AllItems);
	virtual	void	closeEvent ( QCloseEvent * event ) override;
};

//-------------------------------------------------------------------------------------

#endif // LARGEMEASUREWINDOWFORM_H
