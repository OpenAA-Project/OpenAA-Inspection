#ifndef DISPLACEMENTMETERFORM_H
#define DISPLACEMENTMETERFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class DisplacementMeterForm;
}
class	QextSerialPort;

class SignalOperandInt;

class DisplacementMeterForm : public GUIFormBase
{
    Q_OBJECT
    
	QextSerialPort		*sio;
	int					SysMeasuredNo;
	SignalOperandInt	*oMeasured;
public:
	int				CommPort;

	explicit DisplacementMeterForm(LayersBase *base ,QWidget *parent = 0);
    ~DisplacementMeterForm();
    
	virtual	void	Prepare(void)	override;

	bool	OpenPort(int port);
	bool	ClosePort(void);
private slots:
    void on_pushButtonZero_clicked();
    void on_pushButtonMeasure_clicked();

private:
    Ui::DisplacementMeterForm *ui;
private:
	int		GetChar(void);
	void	SendChar(unsigned char d);

	bool	SendStr(char *s);
	bool	GetStr(char buff[] ,int maxlen);
};

#endif // DISPLACEMENTMETERFORM_H
