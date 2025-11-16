#pragma once

#include <QString>
#include <QPair>

#include "CLHS_PX8CommandCreater.h"

class CLHS_PX8CommandAnalyzer
{
private:
	CLHS_PX8CommandAnalyzer();

public:
	static QPair<QList<bool>, CLHS_PX8Setting> analyze(const QString &str);
	static CLHS_PX8Type checkCmd(const QString &recieve);
	static bool checkValue(const QString &recieve, double &value1,double &value2);
	static void setData(CLHS_PX8Type type, CLHS_PX8Setting &buffer, double value);
	static void setData(CLHS_PX8Setting &buffer, const QPair<QList<bool>, CLHS_PX8Setting> &sorce);
	static void setData(CLHS_PX8Setting &buffer, const QString &recieve);
};