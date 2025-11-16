#ifndef SHOWITEMNAMERESULTSEQ_H
#define SHOWITEMNAMERESULTSEQ_H

#include "showitemnameresultseq_global.h"
#include "XGUIFormBase.h"
#include <QLabel>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QFont>

namespace Ui {
    class SetSpetialValueForm;
}

class	SignalOperandInt;
class	AlgorithmItemRoot;
class	ResultInItemRoot;

class ShowItemNameResultSeq : public GUIFormBase
{
    Q_OBJECT

	QLabel		LabelItemName;
	QLabel		LabelResult;
	SignalOperandInt	*ioItemValue;
	AlgorithmItemRoot	*Item;
	ResultInItemRoot	*LastResult;
	int			LastValue;
public:
	QString		ItemDLLRoot;
	QString		ItemDLLName;
	QString		ItemName;
	int32		SeqNo;
	bool		ShowItemName;
	volatile int	ShowingCount;

    explicit ShowItemNameResultSeq(LayersBase *Base,QWidget *parent = 0);
    ~ShowItemNameResultSeq();


	virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;

signals:
	void	SignalShowValue(int d);

private slots:
	void	ResizeAction();
	void	SlotSeqLoaded();
	void	SlotSeqChanged(int);
	void	SlotShowValue(int d);
};

#endif // SHOWITEMNAMERESULTSEQ_H
