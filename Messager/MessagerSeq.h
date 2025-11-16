//---------------------------------------------------------------------------

#ifndef MESAGERSEQ_H
#define MESAGERSEQ_H
//---------------------------------------------------------------------------
#include <QtGui>
#include <time.h>
#include "ThreadSequence.h"

void    _XSeqLocalInit(SeqLocalParam *param ,SeqControl *seqControl);

void    _SetDataSpecialOperand			(SeqLocalParam *param ,int ID, int d);
int     _GetDataSpecialOperand			(SeqLocalParam *param ,int ID);

void    _SetDataSpecialBitOperand		(SeqLocalParam *param ,int ID, bool d);
bool     _GetDataSpecialBitOperand		(SeqLocalParam *param ,int ID);

QString  _GetDataSpecialStringOperand	(SeqLocalParam *param ,int ID);
void	_SetDataSpecialStringOperand	(SeqLocalParam *param ,int ID, QString d);

void	_SetDataSpecialFloatOperand		(SeqLocalParam *param ,int ID, double d);
double  _GetDataSpecialFloatOperand		(SeqLocalParam *param ,int ID);

class   SeqMessagerParam : public QObject,public SeqLocalParam
{
    Q_OBJECT

public:

	SeqMessagerParam(LayersBase *Base);

	volatile    bool    FoundForm;
	volatile	bool	DoneControlGUI;

	virtual	void	SetDataSpecialOperand(int ID, int d);
	virtual	int		GetDataSpecialOperand(int ID)		const;
	virtual	void	SetDataSpecialBitOperand(int ID, bool d);
	virtual	bool	GetDataSpecialBitOperand(int ID)	const;
	virtual	void	SetDataSpecialStringOperand(int ID, QString d);
	virtual	QString GetDataSpecialStringOperand(int ID)	const;
	virtual	void	SetDataSpecialFloatOperand(int ID, double d);
	virtual	double	GetDataSpecialFloatOperand(int ID)	const;
signals:
	void	SignalButtonClick(QString formname ,QString controlname);
	void	SignalTableWidgetSelect(QString formname ,QString controlname,int row ,int col);
	void	SignalInputEdit(QString formname ,QString controlname,QString data);
	void	SignalInputValue(QString formname ,QString controlname,int data);
	void	SignalCheckDown(QString formname ,QString controlname);
	void	SignalCheckUp(QString formname ,QString controlname);
	void	SignalCheckToggle(QString formname ,QString controlname);
	void	SignalSearchForm(QString formname);
	void	SignalVisilize(QString formname ,QString controlname);
	void	SignalInvisilize(QString formname ,QString controlname);
	void	SignalEnable(QString formname ,QString controlname);
	void	SignalDisable(QString formname ,QString controlname);

	void	SignalClosePopup();

private slots:
	void	SlotButtonClick(QString formname ,QString controlname);
	void	SlotTableWidgetSelect(QString formname ,QString controlname,int row ,int col);
	void	SlotInputEdit(QString formname ,QString controlname,QString data);
	void	SlotInputValue(QString formname ,QString controlname,int data);
	void	SlotCheckDown(QString formname ,QString controlname);
	void	SlotCheckUp(QString formname ,QString controlname);
	void	SlotCheckToggle(QString formname ,QString controlname);
	void	SlotSearchForm(QString formname);
	void	SlotVisilize(QString formname ,QString controlname);
	void	SlotInvisilize(QString formname ,QString controlname);
	void	SlotEnable(QString formname ,QString controlname);
	void	SlotDisable(QString formname ,QString controlname);

	void	SlotClosePopup();
};

extern  SeqMessagerParam *SeqMessagerParamData;

#endif
