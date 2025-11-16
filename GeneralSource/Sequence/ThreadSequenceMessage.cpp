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