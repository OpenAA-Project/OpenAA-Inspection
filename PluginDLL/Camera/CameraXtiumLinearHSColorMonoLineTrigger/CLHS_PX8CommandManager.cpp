#include "CLHS_PX8CommandManager.h"

#include <QStringList>
#include <QVector>

QPair<QList<bool>, CLHS_PX8Setting> CLHS_PX8CommandAnalyzer::analyze(const QString &str)
{
	QStringList ComStep = str.split(QChar((char)0x04), QString::SkipEmptyParts);// 各コマンド終端区切りで分割(0x04)

	CLHS_PX8Setting setting;
	QList<bool> flagList = QVector<bool>(TYPE_ENUM_COUNT, false).toList();
	
	for(int cs=0; cs<ComStep.count(); cs++){
		QStringList list = ComStep[cs].split('\r', QString::SkipEmptyParts);// コマンド返信区分けで分割(CR)

		// 例){>OK>r200, >CMD OVR ERR!, EOF}
		for(int i=0; i<list.count(); i++){
			QStringList parts = list[i].split('>');// コマンドの開始文字で分割('>')
			if(parts.isEmpty()==false){
				if(parts.contains("CMD ERR!") || list.contains("CMD OVR ERR!") || list.contains("VAL ERR!") || list.contains("MEM ERR!")){
					continue;// エラーにより次のコマンド返答へ
				}else{
					if(parts.count()>=2){// 2個目が本命
						CLHS_PX8Type type = checkCmd(parts[1]);// タイプ選別
						if(type==TYPE_ENUM_COUNT)continue;
						double value1;
						double value2=-99999999;
						if(checkValue(parts[1], value1,value2)==true){// 値取得
							// 書込み
							flagList[type] = true;
							if(value2>-99999999){
								setData(type, setting, value2);
							}
							else{
								setData(type, setting, value1);
							}
						}
					}
				}
			}
		}
	}

	return QPair<QList<bool>, CLHS_PX8Setting>(flagList, setting);
}

CLHS_PX8Type CLHS_PX8CommandAnalyzer::checkCmd(const QString &recieve)
{
	QString cmdStr;

	QString trmStr = recieve.trimmed();

	for(int i=0; i<trmStr.count(); i++){
		if(trmStr[i].isNumber()==true){// 数値
			break;
		}
		if(trmStr[i]==QChar(' ')){// マイナス値
			break;
		}
		cmdStr.append(recieve[i]);
	}

	if(cmdStr=="gax"){
		return TYPE_AnalogGain;
	}else if(cmdStr=="gdx"){
		return TYPE_DigitalGain;
	}else if(cmdStr=="odx"){
		return TYPE_DigitalOffset;
	}else if(cmdStr=="inm"){
		return TYPE_ExposureMode;
	}else if(cmdStr=="int"){
		return TYPE_ExposureTime;
	}else if(cmdStr=="tpn"){
		return TYPE_UseTestPattern;
	}else if(cmdStr=="rev"){
		return TYPE_ScanDirection;
	}else{
		return TYPE_ENUM_COUNT;
	}
}

bool CLHS_PX8CommandAnalyzer::checkValue(const QString &recieve, double &value1,double &value2)
{
	int index = recieve.indexOf('>');// コマンド開始点

	// 数値まで飛ばす
	for(index = index+1; index<recieve.count(); index++){
		if(recieve[index].isNumber()==true){// 数値
			break;
		}
		if(recieve[index]==QChar(' ')){// マイナス値
			break;
		}
	}

	QString valueStr;
	for(index++; index<recieve.count(); index++){
		if(recieve[index]!='.' && recieve[index].isNumber()==false && recieve[index]!=QChar('-')){// 数値もしくはマイナス値
			break;
		}
		valueStr.append(recieve[index]);
	}

	bool ok;
	value1 = valueStr.toDouble(&ok);
	
	if(recieve[index]==','|| recieve[index]==' '){
		QString valueStr2;
		for(index++; index<recieve.count(); index++){
			if(recieve[index]!='.' && recieve[index].isNumber()==false && recieve[index]!=QChar('-')){// 数値もしくはマイナス値
				break;
			}
			valueStr2.append(recieve[index]);
		}
		value2 = valueStr2.toDouble(&ok);
	}
	

	return ok;
}

void CLHS_PX8CommandAnalyzer::setData(CLHS_PX8Type type, CLHS_PX8Setting &buffer, double value)
{
	switch(type){
	case TYPE_AnalogGain:
		buffer.AnalogGain = value;
		break;
	case TYPE_DigitalGain:
		buffer.DigitalGain = value;
		break;
	case TYPE_DigitalOffset:
		buffer.DigitalOffset = value;
		break;

	case TYPE_ExposureMode:
		buffer.ExposureMode = value;
		break;
	case TYPE_ExposureTime:
		buffer.ExposureTime = value;
		break;
	case TYPE_UseTestPattern:
		buffer.EnableTestPattern = ((value==0) ? false : true);
		break;
	case TYPE_ScanDirection:
		buffer.ScanDirection = ((value==0) ? true : false);
		break;
	default:
		break;
	}
}

void CLHS_PX8CommandAnalyzer::setData(CLHS_PX8Setting &buffer, const QPair<QList<bool>, CLHS_PX8Setting> &sorce)
{
	if(sorce.first.count()!=TYPE_ENUM_COUNT)return;

	for(int i=0; i<sorce.first.count(); i++){
		if(sorce.first[i]==true){
			setData( (CLHS_PX8Type)i, buffer, sorce.second.getData((CLHS_PX8Type)i) );
		}
	}
}

void CLHS_PX8CommandAnalyzer::setData(CLHS_PX8Setting &buffer, const QString &recieve)
{
	setData(buffer, analyze(recieve));
}
