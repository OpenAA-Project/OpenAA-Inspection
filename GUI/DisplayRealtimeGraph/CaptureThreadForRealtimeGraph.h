/*
 * Copyright (C) 2012
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

		ImageBufferListContainer	IBuffer;		//�{���Ɋ��蓖�Ă��摜�̈�
		ImageBuffer					**IBuffPointer;	//�摜�̈��ւ̃|�C���^
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