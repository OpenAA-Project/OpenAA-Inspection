#ifndef SHOWSIZEPANELSEQFORM_H
#define SHOWSIZEPANELSEQFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandInt;


namespace Ui {
class ShowSizePanelSeqForm;
}

class ShowSizePanelSeqForm : public GUIFormBase
{
    Q_OBJECT

	SignalOperandInt	*iRegLengthSize;		//Unit:um
	SignalOperandInt	*iRegWidthSize;		
	SignalOperandInt	*iRegHeightSize;
public:
	int32		LimitMaxLength;				//Unit:um
	int32		LimitMaxWidth;
	int32		LimitMaxHeight;
	int32		SizeLength;					//Unit:um
	int32		SizeWidth;
	int32		SizeHeight;
	int32		SysRegisterNoLength;
	int32		SysRegisterNoWidth;
	int32		SysRegisterNoHeight;
	
	explicit ShowSizePanelSeqForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowSizePanelSeqForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

private slots:
    void on_pushButtonChange_clicked();

private:
    Ui::ShowSizePanelSeqForm *ui;
};

#endif // SHOWSIZEPANELSEQFORM_H
