#ifndef LEDCONTROL16CDIALOG_H
#define LEDCONTROL16CDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include "mtToolButtonColored.h"
#include "XTypeDef.h"
#include "LEDControl16C.h"
#include <QScrollArea>
#include <QProgressBar>

namespace Ui {
class LEDControl16CDialog;
}

class	LineGroup : public QObject
{
	Q_OBJECT
public:
	LEDControl16CDialog	*Parent;
	int			Number;
	int32		ColorType;
	int32		LightID;
	mtToolButtonColored	Button;

	class	LineWindow
	{
	public:
		LEDControl16CPanel::DefUnit::DefBoard::DefLine	*PointerForDefLine;
		QLabel		*Label;
		QSpinBox	*EditValue;
		QLineEdit	*EditComment;

		LineWindow(QWidget *parent);
		virtual	~LineWindow(void);
		
		void	SetY(int n);
		void	Show(void);
	};
	LineWindow	*LineData[256];

	LineGroup(LEDControl16CDialog *p ,QWidget *parent);
	~LineGroup(void);
	void	Initial(int n);
	void	AddLine(LEDControl16CPanel::DefUnit::DefBoard::DefLine	*L ,QWidget *parent);

private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int n);
};

class LEDControl16CDialog : public QDialog
{
    Q_OBJECT
	LEDControl16CPanel	*Panel;

	LineGroup	*LineGroupData[16];
	int			LineGroupDataNumb;
	

	QScrollArea	*FrameArea[16];
	QWidget		*FrameAreaInside[16];
public:
    explicit LEDControl16CDialog(LEDControl16CPanel *p,QWidget *parent = 0);
    ~LEDControl16CDialog();

	QProgressBar	*GetBar(void);
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonTransfer_clicked();
    void on_toolButtonON_clicked();
    void on_pushButtonDefinition_clicked();
    void on_pushButtonShowIO_clicked();
    void on_pushButtonShowAD_clicked();
    void on_pushButtonShowSpecial_clicked();

	void	SlotClicked(int n);

    void on_pushButtonIODeliverer_clicked();

private:
    Ui::LEDControl16CDialog *ui;

	void SetPatternValue(int PatternNo);
	void GetPatternValue(int PatternNo);
	int	GetCurrentPatternNo(void)	{	return 0;	}
};

#endif // LEDCONTROL16CDIALOG_H
