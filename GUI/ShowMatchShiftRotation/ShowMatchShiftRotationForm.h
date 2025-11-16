#ifndef SHOWMATCHSHIFTROTATIONFORM_H
#define SHOWMATCHSHIFTROTATIONFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ShowMatchShiftRotationForm;
}

class	SignalOperandInt;
class	SignalOperandFloat;
class	SignalOperandBit;

class ShowMatchShiftRotationForm : public GUIFormBase
{
    Q_OBJECT

	SignalOperandFloat	*iAngle;
	SignalOperandInt	*iShiftX;
	SignalOperandInt	*iShiftY;
	SignalOperandBit	*iDone;
public:
	double	RegNo_Angle;
	int		RegNo_ShiftX;
	int		RegNo_ShiftY;
	int		RegNo_Done;

	double	CurrentAngle;
	int		CurrentShiftX;
	int		CurrentShiftY;
	bool	CurrnetDone;

    explicit ShowMatchShiftRotationForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowMatchShiftRotationForm();

	virtual void	Prepare(void) override;
	virtual void	ShowInPlayer(int64 shownInspectionID) override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
private:
    Ui::ShowMatchShiftRotationForm *ui;
};

//======================================================================
class	GUICmdReqRotation : public GUICmdPacketBase
{
public:
	int		AreaID;

	GUICmdReqRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendRotation : public GUICmdPacketBase
{
public:
	double	Angle;
	int		ShiftX;
	int		ShiftY;
	bool	Found;

	GUICmdSendRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // SHOWMATCHSHIFTROTATIONFORM_H
