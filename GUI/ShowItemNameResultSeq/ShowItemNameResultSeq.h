/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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