/*
 * Copyright (C) 2021
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