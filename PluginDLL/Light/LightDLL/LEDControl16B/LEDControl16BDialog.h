#ifndef LEDCONTROL16BDIALOG_H
#define LEDCONTROL16BDIALOG_H

#include <QDialog>
#include "LEDControl16B.h"
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QScrollArea>
#include "mtToolButtonColored.h"

namespace Ui {
class LEDControl16BDialog;
}
class	LineGroup : public QObject
{
	Q_OBJECT
public:
	LEDControl16BDialog	*Parent;
	int			Number;
	int32		ColorType;
	int32		LightID;
	mtToolButtonColored	Button;

	class	LineWindow
	{
	public:
		LEDControl16BPanel::DefUnit::DefBoard::DefLine	*PointerForDefLine;
		QLabel		*Label;
		QSpinBox	*EditValue;
		QLineEdit	*EditComment;

		LineWindow(QWidget *parent);
		virtual	~LineWindow(void);
		
		void	SetY(int n);
		void	Show(void);
	};
	LineWindow	*LineData[256];

	LineGroup(LEDControl16BDialog *p ,QWidget *parent);
	~LineGroup(void);
	void	Initial(int n);
	void	AddLine(LEDControl16BPanel::DefUnit::DefBoard::DefLine	*L ,QWidget *parent);

private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int n);
};

class LEDControl16BDialog : public QDialog
{
    Q_OBJECT

	LEDControl16BPanel	*Panel;


	LineGroup	*LineGroupData[16];
	int			LineGroupDataNumb;
	

	QScrollArea	*FrameArea[16];
	QWidget		*FrameAreaInside[16];
public:
    explicit LEDControl16BDialog(LEDControl16BPanel *p,QWidget *parent = 0);
    ~LEDControl16BDialog();

	QProgressBar	*GetBar(void);
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonTransfer_clicked();
    void on_toolButtonON_clicked();
    void on_pushButtonDefinition_clicked();
    void on_pushButtonWriteEPROM_clicked();
    void on_pushButtonShowIO_clicked();
    void on_pushButtonShowAD_clicked();

	void	SlotClicked(int n);

    void on_pushButtonReqVolume_clicked();
    void on_toolButtonManual_clicked();

    void on_pushButtonShowSpecial_clicked();

private:
    Ui::LEDControl16BDialog *ui;

	void SetPatternValue(int PatternNo);
	void GetPatternValue(int PatternNo);
	int	GetCurrentPatternNo(void)	{	return 0;	}
};

#endif // LEDCONTROL16BDIALOG_H
