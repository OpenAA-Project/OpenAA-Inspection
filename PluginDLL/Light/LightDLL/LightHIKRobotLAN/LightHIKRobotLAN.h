#pragma once

#include "lighthikrobotlan_global.h"
#include <QIODevice>
#include "XTypeDef.h"
#include "XLightClass.h"
#include "MvCameraControl.h"

const	int		LEDCountInSheet=7;
const	int		SheetCountInSystem=30;
const	int		MaxBrightness		=4095;
class	QextSerialPort;


class LightSourceValue
{
public:
	int		Brightness;
	bool	ONMode;

	LightSourceValue();
	~LightSourceValue();

	LightSourceValue	&operator=(const LightSourceValue &src){
		Brightness=src.Brightness;
		ONMode=src.ONMode;
		return *this;
	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

};


class	LightHIKRobotLAN : public LightDLLBaseClass
{
	Q_OBJECT

private:
    void* m_handle;
    MV_CC_DEVICE_INFO_LIST m_deviceList; // 発見したデバイスのリストを保持
	QString modelName;
	QString userDefName;
public:
	int			DeviceNo;	
	int			ChannelCount;
	QStringList	ChannelNames;

	LightSourceValue	*LightDim;

	static const	char		*CommentFileName;
public:

	LightHIKRobotLAN(LayersBase *base,const QString &LightParamStr);
	~LightHIKRobotLAN(void);

	bool	Open(const QString &LightParamStr);
	bool	Close(void);

	bool	Save(QIODevice *f)	override;
	bool	Load(QIODevice *f)	override;
	bool	SaveCommon();
	bool	LoadCommon();


	virtual	bool	ShowSettingDialog(void)			override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param);
	virtual	bool	ReflectPhysical(void)		;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		;


	bool GetBrightnessRange(int channel, int &MaxBrightness,int &MinBrightness);
private:
    // デバイスの検索とリスト取得
    int enumerateDevices();
    QStringList getDeviceNames() const;
	int		SelectDevice(int deviceCount,const QString &LightParamStr);

    // 検索結果のインデックスからデバイスを開く
    bool	connectByIndex(int index);
    void	disconnectDevice();
	int		getChannelCount();

    // チャンネル制御
    bool setChannelState(int channel, bool isOn);
	
    bool setBrightness(int channel, int brightness);


signals:
    void errorOccurred(const QString &errorMsg);
};
