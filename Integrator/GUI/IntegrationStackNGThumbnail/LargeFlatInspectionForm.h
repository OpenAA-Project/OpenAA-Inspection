#ifndef LARGEFLATINSPECTIONFORM_H
#define LARGEFLATINSPECTIONFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XLearningRegist.h"
#include "XPasswordQWidget.h"

namespace Ui {
class	LargeFlatInspectionForm;
}
namespace LargeFlatInspection {
class	FrameLargeWindow;
class	FrameMasterWindow;
}

class	ThumbnailPanel;
class	LargeFlatInspectionForm;

class	LargeFlatInspection::FrameLargeWindow : public QWidget
{
    Q_OBJECT
		
	friend	class LargeFlatInspectionForm;

	LargeFlatInspectionForm	*Parent;
	bool	ShowingMasterImage;
	QTimer	FlipTimer;
public:
	FrameLargeWindow(LargeFlatInspectionForm *p);

	void	StartTimer(void);
private slots:
	void	SlotTimeOut();


private:
	virtual	void	paintEvent(QPaintEvent *event) override;
};

class	LargeFlatInspection::FrameMasterWindow : public QWidget
{
    Q_OBJECT
		
	friend	class LargeFlatInspectionForm;

	LargeFlatInspectionForm	*Parent;

public:
	FrameMasterWindow(LargeFlatInspectionForm *p);

private:
	virtual	void	paintEvent(QPaintEvent *event) override;
};

class LargeFlatInspectionForm : public QWidget,public ServiceForLayers,public PasswordInQWodget
{
    Q_OBJECT
	friend	class	ThumbnailPanel;
	friend	class	LargeFlatInspection::FrameLargeWindow;
	friend	class	LargeFlatInspection::FrameMasterWindow;

	Qt::WindowFlags	SavedFlag;
	ThumbnailPanel	*Parent;
	QImage	NGImage;
	QImage	NGMarkImage;
	QImage	MasterImage;
	LearningMenu	LearningMenuDim[100];
	int				LearningMenuDimNumb;
	LargeFlatInspection::FrameLargeWindow	ImagePanel;
	LargeFlatInspection::FrameMasterWindow	MasterPanel;

public:
    explicit LargeFlatInspectionForm(ThumbnailPanel *p ,QWidget *parent = nullptr);
    ~LargeFlatInspectionForm();

	void	Initial(void);
	bool	ShowDrawNGMark(void);

signals:
	void	SignalShowDetail();

private slots:
    void on_PushButtonOKbyColorWhole_clicked();
    void on_PushButtonOKbyShiftWhole_clicked();
    void on_PushButtonOKbySizeWhole_clicked();
    void on_toolButtonShowNGMark_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::LargeFlatInspectionForm *ui;

	virtual	void	showEvent(QShowEvent *event) override;
	virtual	void	closeEvent ( QCloseEvent * event ) override;
};

#endif // LARGEFLATINSPECTIONFORM_H
