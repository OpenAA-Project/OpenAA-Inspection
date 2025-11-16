#if	!defined(XLightDLLRemoteController_h)
#define	XLightDLLRemoteController_h


#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include <QLocalSocket>
#include <QLocalServer>


class	XLightDLLRemoteController : public LightDLLBaseClass
{
	Q_OBJECT

	bool	Opened;
	QString Param;
	int32		LightID;
	QLocalSocket	*Socket;
	QByteArray		Received;
public:

	QString		VersionStr;


	XLightDLLRemoteController(LayersBase *base ,const QString &LightParamStr);
	~XLightDLLRemoteController(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	ShowSettingDialog(void)				override;

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;
private slots:
	void	SlotReadyRead();
};


#endif