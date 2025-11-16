#if	!defined(CaptureThreadForRealtimeGraph_H)
#define	CaptureThreadForRealtimeGraph_H

#include "XExecuteInspectBase.h"
#include "XMainSchemeMemory.h"
#include <QThread>

#define	TempMaxLines	1000

class	CameraClass;

class	CaptureThreadForRealtimeGraph: public QThread ,public ServiceForLayers
{
	Q_OBJECT

	class	TmpBufferPerCam :public ServiceForLayers
	{
		int32						CamNo;
		ExecuteInspectBase			*Executer;
		CameraClass					*CamPointer;

		ImageBufferListContainer	IBuffer;		//本当に割り当てた画像領域
		ImageBuffer					**IBuffPointer;	//画像領域へのポインタ
		bool						ModeCamChangedInfo;
	public:
		TmpBufferPerCam(int32 camNo ,LayersBase *base);
		~TmpBufferPerCam(void);

		void	Allocate(void);

		void	StartCapture(void);
		int		GetStatus(void);
		void	GetImage(void);
		void	RestoreCamInfo(void);
	};

	int				TotalCameraNumb;
	TmpBufferPerCam	**CamBuffer;
	volatile	bool	Terminated;

public:
	CaptureThreadForRealtimeGraph(LayersBase *base);
	~CaptureThreadForRealtimeGraph(void);

	void	Initialize(void);

	void	StartRepeatableCapture(void);
	void	StopRepeatableCapture(void);

	virtual void run ();

private:
	void	AllocMemory(void);
	void	StartCapture(void);
	int		GetStatus(void);
	void	GetImage(void);

signals:
	void	CamErrorOccurs(int status);
};


#endif