#ifndef LEDControl16HDIALOG_H
#define LEDControl16HDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QScrollArea>
#include "mtToolButtonColored.h"
#include "XTypeDef.h"
#include "LEDControl16HioPrn.h"


namespace Ui {
class LEDControl16HDialog;
}


class	LineGroup : public QObject
{
	Q_OBJECT
public:
	LEDControl16HDialog	*Parent;
	int			Number;
	int32		ColorType;
	int32		LightID;
	mtToolButtonColored	Button;

	class	LineWindow
	{
	public:
		struct		LightLineUnit	*PointerForDefLine;
		QLabel		*Label;
		QSpinBox	*EditValue;
		QLineEdit	*EditComment;

		LineWindow(QWidget *parent);
		virtual	~LineWindow(void);
		
		void	SetY(int n);
		void	Show(void);
	};
	LineWindow	*LineData[256];
	int			LineNumb;

	LineGroup(LEDControl16HDialog *p ,QWidget *parent);
	~LineGroup(void);
	void	Initial(int n);
	void	AddLine(struct LightLineUnit *L ,QWidget *parent);

private slots:
	void	SlotClicked();

signals:
	void	SignalClicked(int n);
};

class LEDControl16HDialog : public QDialog
{
    Q_OBJECT
	LEDControl16HioPanel	*Panel;

	LineGroup	*LineGroupData[16];
	int			LineGroupDataNumb;
	

	QScrollArea	*FrameArea[16];
	QWidget		*FrameAreaInside[16];
public:
    explicit LEDControl16HDialog(LEDControl16HioPanel *p,QWidget *parent = 0);
    ~LEDControl16HDialog();

	QProgressBar	*GetBar(void);
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonTransfer_clicked();
    void on_toolButtonON_clicked();
    void on_pushButtonDefinition_clicked();
    void on_pushButtonShowIO_clicked();
    void on_pushButtonShowSpecial_clicked();

	void	SlotClicked(int n);

    void on_pushButtonIODeliverer_clicked();
    void on_pushButtonSetTestLED_clicked();

private:
    Ui::LEDControl16HDialog *ui;

	void SetPatternValue(int PatternNo);
	void GetPatternValue(int PatternNo);
	int	GetCurrentPatternNo(void)	{	return 0;	}
};

#endif // LEDControl16HDIALOG_H
