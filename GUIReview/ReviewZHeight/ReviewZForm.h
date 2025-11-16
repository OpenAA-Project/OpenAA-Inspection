#ifndef REVIEWZFORM_H
#define REVIEWZFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ReviewZForm;
}
class SignalOperandInt;
class SignalOperandBit;

class ReviewZForm : public GUIFormBase
{
    Q_OBJECT
    
	SignalOperandInt	*oValueZ;
	SignalOperandBit	*oSetZ;	
	GUIFormBase			*VRSOpe;

	int32		ZScrewPitch;	//	Micron
	int32		ZPulsePerRotation;
	int32		ZOffsetPulse;
	int32		ZMultiply;
public:
    explicit ReviewZForm(LayersBase *base ,QWidget *parent = 0);
    ~ReviewZForm();
    
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

	int32		SysValueZ;
	int32		SysSetZ;

private slots:
    void on_pushButtonSet_clicked();
    void on_pushButton10Up_clicked();
    void on_pushButton10Dn_clicked();
    void on_pushButton100Up_clicked();
    void on_pushButton100Dn_clicked();

    void on_spinBox_valueChanged(int arg1);
	void	OperandChanged();
private:
    Ui::ReviewZForm *ui;
};

#endif // REVIEWZFORM_H
