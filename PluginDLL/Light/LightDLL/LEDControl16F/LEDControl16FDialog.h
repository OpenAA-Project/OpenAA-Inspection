#ifndef LEDCONTROL16FDIALOG_H
#define LEDCONTROL16FDIALOG_H

#include <QDialog>
#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QScrollArea>
#include "mtToolButtonColored.h"
#include "XTypeDef.h"
#include "LEDControl16F.h"


namespace Ui {
class LEDControl16FDialog;
}


class	LineGroup : public QObject
{
	Q_OBJECT
public:
	LEDControl16FDialog	*Parent;
	int			Number;
	int32		ColorType;
	int32		LightID;
	mtToolButtonColored	Button;

	class	LineWindow
	{
	public:
		LEDControl16FPanel::DefUnit::DefBoard::DefLine	*PointerForDefLine;
		QLabel		*Label;
		QSpinBox	*EditValue;
		QLineEdit	*EditComment;

		LineWindow(QWidget *parent);
		virtual	~LineWindow(void);
		
		void	SetY(int n);
		void	Show(void);
	};
	LineWindow	*LineData[256];

	LineGroup(LEDControl16FDialog *p ,QWidget *parent);
	~LineGroup(void);
	void	Initial(int n);
	void	AddLine(LEDControl16FPanel::DefUnit::DefBoard::DefLine	*L ,QWidget *parent);

private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int n);
};

class LEDControl16FDialog : public QDialog
{
    Q_OBJECT
	LEDControl16FPanel	*Panel;

	LineGroup	*LineGroupData[16];
	int			LineGroupDataNumb;
	

	QScrollArea	*FrameArea[16];
	QWidget		*FrameAreaInside[16];
public:
    explicit LEDControl16FDialog(LEDControl16FPanel *p,QWidget *parent = 0);
    ~LEDControl16FDialog();

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

private:
    Ui::LEDControl16FDialog *ui;

	void SetPatternValue(int PatternNo);
	void GetPatternValue(int PatternNo);
	int	GetCurrentPatternNo(void)	{	return 0;	}
};

#endif // LEDCONTROL16FDIALOG_H
