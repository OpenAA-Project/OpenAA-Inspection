#include "CLHS_PX8CommandCreater.h"

QString CLHS_PX8CommandCreater::setAnalogGain(double gain/* 280 to 530 */)
{
	return makeCommand("gax", gain, 0, 15);
}

QString CLHS_PX8CommandCreater::setDigitalGain(int gain/* 280 to 530 */)
{
	return makeCommand("gdx", gain, 0, 511);
}

QString CLHS_PX8CommandCreater::setDigitalOffset(int offset/* 220 to 470 */)
{
	return makeCommand("odx", offset, -127, 127);
}

QString CLHS_PX8CommandCreater::initialOnFactory(void)
{
	return makeCommand("rst");
}
QString CLHS_PX8CommandCreater::loadFromMemory(void)
{
	return makeCommand("rfd");
}
QString CLHS_PX8CommandCreater::saveToMemory(void)
{
	return makeCommand("sav");
}

QString CLHS_PX8CommandCreater::setExposureMode(int type/* 0:FreeRun, 1:Edge, 2:virtual expose fix by time on edge, 3:virtual expose fix by time on level */)
{
	return makeCommand("inm", type, 0, 2);
}
QString CLHS_PX8CommandCreater::setExposureTime(int exposure/* 56 to 32767 */)
{
	return makeCommand2("int", 0,exposure, 972, 1048575);
}
QString CLHS_PX8CommandCreater::setTestPatternOutput(bool useTest/* true:setTest, false:defaultOut */)
{
	if(useTest==true){
		return makeCommand("tpn", 1);
	}else{
		return makeCommand("tpn", 0);
	}
}
QString CLHS_PX8CommandCreater::setScanDirection(bool forward/* true:forward, false:reverse */)
{
	if(forward==true){
		return makeCommand("rev", 0);
	}else{
		return makeCommand("rev", 1);
	}
}
QString CLHS_PX8CommandCreater::createFixCommandFromStruct(const CLHS_PX8Setting &data)// this command is able to use soon after created.
{
	QString ret;

	ret += setAnalogGain(data.AnalogGain);
	ret += setDigitalGain(data.DigitalGain);
	ret += setDigitalOffset(data.DigitalOffset);
	ret += setExposureMode(data.ExposureMode);
	ret += setExposureTime(data.ExposureTime);
	ret += setTestPatternOutput(data.EnableTestPattern);
	ret += setScanDirection(data.ScanDirection);

	return ret;
}
// èÓïÒéÊìæ
QString CLHS_PX8CommandCreater::getCurrentCameraState()
{
	return makeCommand("sta");
}

QString CLHS_PX8CommandCreater::makeCommand(const QString &CMD, double value, double min, double max)
{
	double val = qBound(min, value, max);
	return makeCommand(CMD, value);
}
QString CLHS_PX8CommandCreater::makeCommand2(const QString &CMD, double value1, double value2, double min, double max)
{
	double val1 = qBound(min, value1, max);
	double val2 = qBound(min, value2, max);
	return makeCommand2(CMD, value1,value2);
}

QString CLHS_PX8CommandCreater::makeCommand(const QString &CMD, double value)
{
	QString	ret= QString("%1 %2\r").arg(CMD).arg(value);
	return ret;
}
QString CLHS_PX8CommandCreater::makeCommand2(const QString &CMD, double value1, double value2)
{
	QString	ret= QString("%1 %2 %3\r").arg(CMD).arg(value1).arg(value2);
	return ret;
}

QString CLHS_PX8CommandCreater::makeCommand(const QString &CMD)
{
	return QString("%1\r").arg(CMD);
}