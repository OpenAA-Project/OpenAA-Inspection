#ifndef CAMERAXTIUMCLHS_PX8_H
#define CAMERAXTIUMCLHS_PX8_H

#include <qglobal.h>
#include <QList>
#include <QRgb>
#include <QDialog>
#include "CLHS_PX8CommandCreater.h"
#include "CameraXtium_global.h"
#include "XCameraHandle.h"

class	saperaCtrl;

class AbstructOriginateClass
{
public:
	AbstructOriginateClass(bool original):m_isOriginal(original){};

public:
	void setOriginal(bool original){ m_isOriginal = original; };
	bool isOriginal() const { return m_isOriginal; };

public:
	AbstructOriginateClass &operator=(const AbstructOriginateClass &other)
	{
		setOriginal(false);
		return *this;
	};

private:
	bool m_isOriginal;
};

// GlobalGrabberState::stG_Grabber -> all LocalGrabbrState::stL_Grabber
// all LocalGrabbrState::stL_GrabEnd -> GlobalGrabberState::stG_GrabEnd
enum LocalGrabberState{
	stL_Idle=0,		// ‘Ò‹@
	stL_Grabber=1,	// B‘œ‘Ò‹@’†
	stL_GrabEnd=2	// B‘œI—¹
};

enum GlobalGrabberState{
	stG_Idle=0,		// ‘Ò‹@
	stG_Grabber=1	// B‘œ’†
};

class CameraXtiumCLHS_PX8 : public AbstructOriginateClass,public CameraHandle
{
public:
	CameraXtiumCLHS_PX8(int CamNo ,LayersBase *base ,bool original);
	~CameraXtiumCLHS_PX8();

public:
	int					DeviceID;
	CLHS_PX8Setting		Setting;
	saperaCtrl			*_sapera;
};

#endif // CAMERAXTIUMCLHS_PX8_H
