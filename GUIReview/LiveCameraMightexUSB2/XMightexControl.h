#if	!defined(XMightexControl_h)
#define	XMightexControl_h

#include "NList.h"
#include <QRgb>
#include <QString>
#include <QIODevice>
#include <QImage>
typedef	unsigned char	byte;
#include "BUF_USBCamera_SDK.h"
#include "XTypeDef.h"

// GlobalGrabberState::stG_Grabber -> all LocalGrabbrState::stL_Grabber
// all LocalGrabbrState::stL_GrabEnd -> GlobalGrabberState::stG_GrabEnd
enum LocalGrabberState{
	stL_Idle=0,		// ë“ã@
	stL_Grabber=1,	// éBëúë“ã@íÜ
	stL_GrabEnd=2	// éBëúèIóπ
};

enum GlobalGrabberState{
	stG_Idle=0,		// ë“ã@
	stG_Grabber=1	// éBëúíÜ
};



class	CameraItem : public QObject ,public NPList<CameraItem>
{
    Q_OBJECT

	quint8				m_gainR, m_gainG, m_gainB;
	int					m_exposureTime;
	LocalGrabberState	m_grabberState;
	TProcessedDataProperty m_processedDataProperty;
	QString				m_moduleNo;
	QString				m_serialNo;
	int					m_resolution;
	unsigned char		*m_frameMem;
	int					m_frameSize;
	bool				m_isTriggerMode;
	bool				m_isEnable;
	double				m_Gamma;
	BYTE				GammaTable[256];
public:
	QImage				*Img;

	CameraItem(QObject *parent);

	void setGainR(quint8 val)	{ m_gainR = val;	};// must be 1..64 all
	quint8 gainR() const		{ return m_gainR;	};

	void setGainG(quint8 val)	{ m_gainG = val;	};// must be 1..64 all
	quint8 gainG() const		{ return m_gainG;	};
	
	void setGainB(quint8 val)	{ m_gainB = val;	};// must be 1..64 all
	quint8 gainB() const		{ return m_gainB;	};

	void setExposureTime(int time)	{ m_exposureTime = time; };
	int exposureTime() const		{ return m_exposureTime; };

	void	setGamma(double val);
	double	gamma(void)				{	return m_Gamma;	}

	void setGrabberState(LocalGrabberState state){ m_grabberState = state; };
	LocalGrabberState grabberState() const { return m_grabberState; };

	void resetGrabberState();
	void startGrabber()		;
	void endGrabber()		;

	void setProcessedDataProperty(const TProcessedDataProperty &prop);
	inline const TProcessedDataProperty &processedDataProperty() const;
	inline TProcessedDataProperty &processedDataProperty();

	void setModuleNoSerialNo(const QString &module, const QString &serial){ m_moduleNo = module; m_serialNo = serial; };
	QString moduleNo() const { return m_moduleNo; };
	QString serialNo() const { return m_serialNo; };

	bool setResolution(int index);
	quint8	resolution(void)	{	return m_resolution;	}

	const unsigned char *frameMem() const { return m_frameMem; };
	unsigned char *frameMem(){ return m_frameMem; };
	int frameSize() const { return m_frameSize; };

	void setTriggerMode(bool trigger){ m_isTriggerMode = trigger; };
	bool isTriggerMode() const { return m_isTriggerMode; };

	void setEnable(bool enable){
		if(m_isEnable==false && enable==true){
			m_isEnable = enable;
			setResolution(resolution());
		}else{
			m_isEnable = enable;
		}
	};
	bool isEnable() const { return m_isEnable; };
	int resolution() const { return m_resolution; };

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	MakeImage(void);
	void	CommandDraw(void);

	CameraItem	&operator=(CameraItem &src);
	CameraItem	&operator=(const CameraItem &src);

signals:
	void	SignalDraw();

private:
	void _setFrameMem(unsigned char *ptr){ m_frameMem = ptr; };
	void _setFrameSize(int size){ m_frameSize = size; };
	bool	bayerToBMP(const unsigned char *bayer, unsigned char *bmp, int width, int height);

private:
};



class MightexCameraContainer : public NPListPack<CameraItem>
{
	GlobalGrabberState m_grabberState;
	QWidget	*Parent;
public:
	MightexCameraContainer(QWidget *parent);
	~MightexCameraContainer();

public:
	int deviceNumb();

	bool hasDeviceID(int id);
	bool hasDeviceHandle(Qt::HANDLE handle);
	
	CameraItem &fromDeviceID(int id);

	void setData(int deviceID, const CameraItem &data);
	void setSavedData(int deviceID, const CameraItem &data);
	void setGrabberState(int deviceID, LocalGrabberState state);

	void resetGrabber(int deviceID);
	void startGrabber(int deviceID);
	void endGrabber(int deviceID);

	bool isCameraGrabber() const ;
	int enableCameraCount() const;

	int grabberCameraCount() const;

	void setGrabberState(GlobalGrabberState state);
	GlobalGrabberState grabberState() const;
	void startGrabber();
	void stopGrabber();
	bool isGrabber() const;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#endif