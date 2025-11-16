#ifndef REALTIMEGRAPHMEASURE1FORM_H
#define REALTIMEGRAPHMEASURE1FORM_H

#include "XGUIFormBase.h"
#include "ui_RealtimeGraphMeasure1Form.h"

class	ThreadFocus;

class RealtimeGraphMeasure1Form : public GUIFormBase
{
	Q_OBJECT

	ThreadFocus		*ThreadDim[3][3];
	GUIFormBase		*PropertyRealtimeGraphPointer;
public:
	volatile	int		CamNo;
	volatile	bool	Calclating;
	QMutex		MutexCalc;

	RealtimeGraphMeasure1Form(LayersBase *Base ,QWidget *parent = 0);
	~RealtimeGraphMeasure1Form();

	virtual void	AfterStartSequence(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual void	ShowInScanning(int64 shownInspectionID=-1)	override;

private:
	Ui::RealtimeGraphMeasure1FormClass ui;

	void	CalcFocus(void);

private slots:
	void	ResizeAction();
};

#endif // REALTIMEGRAPHMEASURE1FORM_H
