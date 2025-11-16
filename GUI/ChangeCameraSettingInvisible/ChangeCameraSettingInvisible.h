#ifndef CHANGECAMERASETTINGINVISIBLE_H
#define CHANGECAMERASETTINGINVISIBLE_H

#include "changecamerasettinginvisible_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ChangeCameraSettingInvisible : public GUIFormBase
{
	Q_OBJECT

	bool	Initialized;
public:
	QString	CameraSettingFileName;

	ChangeCameraSettingInvisible(LayersBase *Base ,QWidget *parent);
	~ChangeCameraSettingInvisible(void);

	virtual void	BuildForShow(void)	override;
};

#endif // CHANGECAMERASETTINGINVISIBLE_H
