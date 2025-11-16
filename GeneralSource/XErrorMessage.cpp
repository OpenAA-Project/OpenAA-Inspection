#include "XTypeDef.h"
#include "XErrorMessage.h"
#include <QMessageBox>

void	SendErrorMessage(const QString &Message)
{
	QMessageBox::critical(NULL,/**/"Error",Message);
}

