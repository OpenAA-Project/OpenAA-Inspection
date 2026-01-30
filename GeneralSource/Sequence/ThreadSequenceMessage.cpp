/*
 * Copyright (C) 2023
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

#include "XTypeDef.h"
#include<QFile>
#include<QMessageBox>
#include "ThreadSequence.h"
#include "XSequence.h"
#include "XCriticalFunc.h"
#include "swap.h"
#include "XServiceForLayers.h"



void	SignalOperandBase::ShowErrorMessage(const SeqErrorInfo &ErrorCode)
{
	QString	s=QString("Special Register ")
			+ GetSignalOperandClassName()
			+ QString(" ID:")
			+ QString::number(GetID());
	QString	Title;
	if(ErrorCode.Error==_SeqError_DuplicateID){
		Title= QString("Error - Duplicate ID");
		s+=QString(" - ") +ErrorCode.DupRegExplain;
	}
	QMessageBox::warning(NULL,Title,s);
}