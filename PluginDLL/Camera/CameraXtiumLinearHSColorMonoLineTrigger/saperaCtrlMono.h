#pragma once
/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
   fileid : saperaCtrl.cpp
  subject : Sapera SDK control functions
////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#include "XCameraHandle.h"
#include "XMainSchemeMemory.h"
#include <QThread>
#include <QMutex>

#define	DEF_FRAME_WAIT	50000		// Frame read fixed wait time.(msec)
//#define	HalfMode


class SapBuffer;
class SapAcquisition;
class SapAcqDevice;
class SapBuffer;
class SapTransfer;
class SapView;
class SapBayer;
class SapFeature;
class SapGio;
class SapLut;

class ImageBuffer;

class SapXferCallbackInfo;
class SapGioCallbackInfo;
class CameraXtiumLinearHSMono;

class featureCtrl;

const int	CamMonoStackNumb=2;

class saperaCtrlMono : public QThread ,public CameraHandle
{
	/* ----------------------------------------------------------------------------
	 CONST
	---------------------------------------------------------------------------- */
//	static const int CONST_MAX_WIDTH = 3252;
//	static const int CONST_MAX_HEIGHT = 1024;
	static const int CONST_MAX_WIDTH = 16384;
	static const int CONST_MAX_HEIGHT = 25000;
	static const unsigned long GVSP_PIX_BAYRG8 = (0x01000000 | 0x00080000 | 0x0009);
	static const int STRING_LENGTH = 256;
	static const int MAX_CALIBRATION_ITERATION = 100;
	double CONST_MAX_COEF;

	static const int CONST_IO_PIN_NUM = 1;

	// STATUS BIT
	static const int CONST_STS_READY_IMAGE		= 0x0000;	// READY
	static const int CONST_STS_PREP_CAPTURE		= 0x0001;	// Bit0	1:Preparing for capturing
	static const int CONST_STS_GRAB_FRAME		= 0x0002;	// Bit1	1:Grabed frame
	static const int CONST_STS_TRANSMIT_IMAGE	= 0x0004;	// Bit2	1:Transmitting image data by DMA
	static const int CONST_STS_OVERRUN_ERROR	= 0x0008;	// Bit3	1:Over-run error occured. Error bit must be kept till DLL_ClearError function
	static const int CONST_STS_OTHER_ERROR		= 0x0010;	// Bit4	1:Other error occured.  Error bit must be kept till DLL_ClearError function

	/* ----------------------------------------------------------------------------
	 ENUM
	---------------------------------------------------------------------------- */
	// control status
	enum EN_CTRLSTS {
		EN_CTRLSTS_IDLE,
		EN_CTRLSTS_PRECAPTURE,
		EN_CTRLSTS_CAPTURE,
		EN_CTRLSTS_GRABED,
		EN_CTRLSTS_MAX
	};

	// LUT MODE
	enum EN_LUT_MODE {
		EN_LUT_MODE_NORMAL,
		EN_LUT_MODE_ARITHMENTIC,
		EN_LUT_MODE_BINARY,
		EN_LUT_MODE_BOOLEAN,
		EN_LUT_MODE_GAMMA,
		EN_LUT_MODE_REVERS,
		EN_LUT_MODE_ROLL,
		EN_LUT_MODE_SHIFT,
		EN_LUT_MODE_SLOPE,
		EN_LUT_MODE_SINGLE,
		EN_LUT_MODE_DOUBLE,
		EN_LUT_MODE_MAX
	};

public:
	ImageBuffer		ImageStack[CamMonoStackNumb];
	ImageBuffer		TRImageStack[CamMonoStackNumb];
	char			ConfigFileName[256];

protected:
	QMutex	MutexSwapImage;
	QMutex	MutexStackImage;

public:
	int		StackedNumb;
	int		CurrentWTop;
	int		CurrentRTop;
	int		GCount;
	int		CurrentGPos;
	volatile	bool	Terminated;
	volatile	bool	Halted;
	bool	Calibrated;

	/* ----------------------------------------------------------------------------
	 PUBLIC FUNCTIONS
	---------------------------------------------------------------------------- */
public:
	/* ----------------------------------------------------------------------------
	 PUIBLIC FUNCTIONS
	---------------------------------------------------------------------------- */
	saperaCtrlMono(int CamNo ,LayersBase *base ,CameraXtiumLinearHSMono *parent);
	~saperaCtrlMono(void);

	bool link(char* pConfigFilepath);
	bool unlink(void);
	bool ControlCamera(void);
	bool	SetCalibration(void);
	bool ChangeLineCount(int YCount);
	bool startCapture(void);
	bool startCaptureInside(void);
	bool stopCapture(void);
	bool updateLUT(SapBuffer* Buffers, SapLut* m_pLut, char *chAcqLutName, int unLutMode);
	bool updateGain(double dBlue, double dGreen, double dRed);
	bool saperaAutoWhiteBalance(char *pConfigFilename);
	bool getImage(ImageBuffer *Buff ,ImageBuffer *TRBuff);
	bool getImageInside(ImageBuffer *Buff,ImageBuffer *TRBuff
							,void	*SrcAddress
							,int	BuffWidth
							,int width
							,int height);
	bool getImageInsideBasic(ImageBuffer *Buff,ImageBuffer *TRBuff
							,void	*SrcAddress
							,int	BuffWidth
							,int width
							,int height);
	bool getPartialImageInside(int Index ,ImageBuffer *Buff,ImageBuffer *TRBuff
									,int StartLine , int EndLine
									,void	*SrcAddress
									,int	BuffWidth
									,int width
									,int height);
	bool getPartialImageInsideBasic(int Index ,ImageBuffer *Buff,ImageBuffer *TRBuff
									,int StartLine , int EndLine
									,void	*SrcAddress
									,int	BuffWidth
									,int width
									,int height);
	bool prepareCapture(void);
	void AllocateBuff(void);
	int getStatus(void);
	int getStatusInside(void);

private:
	/* ----------------------------------------------------------------------------
	 PRIVATE FUNCTIONS
	---------------------------------------------------------------------------- */
	static void acqCallback(SapXferCallbackInfo *pInfo);
	static void gioCallback(SapGioCallbackInfo *pInfo);

	bool FreeHandles(SapAcqDevice *AcqDevice, SapBuffer *Buffers, SapTransfer *Xfer, SapView *View,SapBayer *Bayer,SapFeature *FeatureInfo);
	bool ComputeGain(char* Name, SapAcqDevice* AcqDevice, SapFeature* featureInfo, double coefGain);
	void GrabCallback(SapXferCallbackInfo *pInfo);
	bool ValidateWhiteBalance(int value, int minValue, int maxValue);
	bool GetOptions(int argc, char *argv[], char *acqServerName, ulong *pAcqDeviceIndex);
	bool GetOptionsFromCommandLine(int argc, char *argv[], char *acqServerName, ulong *pAcqDeviceIndex);

public:
	featureCtrl		*fc;
	SapAcquisition	*_Acq;
	SapAcqDevice	*_AcqDevice;
	SapBuffer		*_Buffers;
	SapView			*_View;
	SapBayer		*_Bayer;
	SapFeature		*_FeatureInfo;
	SapTransfer		*_Xfer;
	SapGio			*_Gio; // General IO objects
	bool _bLinked;
	int _nStatus;		// ï‘êMóp
	int _nCtrlStatus;	// êßå‰óp
	int _nGioDev;
	int _nStartReserve;

	double _gainMax;
	double _gainMin;
	double _currentGain;

	CameraXtiumLinearHSMono	*Parent;

	int		*MatrixRX	;
	int		dyR			;
	int		dxR			;
	
	double	GainRedL	;
	int		OffsetRedL	;
	double	GainRedR	;
	int		OffsetRedR	;
	bool	LeftRight	;
	BYTE	*GainOffsetTableRL;
	BYTE	*GainOffsetTableRR;

public:
	//featureCtrl *fc;
	int		Index;
	bool	FirstCapture;
	BYTE	*ClearCenterLine(int index);
	void	RemoveCenterBlack(ImageBuffer *Buff);

protected:
	virtual	void	run();
	bool RemoveLineNoise(int x1, int XLen,ImageBuffer *Buff
								,int StartLine , int EndLine);
	bool RemoveVerticalStripe(ImageBuffer *Buff);
private:
	void	CopyParam(void);
};


