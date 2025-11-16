#ifndef CAMERAPROVIDER_H
#define CAMERAPROVIDER_H

#include <QMainWindow>
#include "ui_CameraProvider.h"
#include "XServiceForLayers.h"
#include "XIntClass.h"
#include "XCameraClass.h"
#include "XCameraProviderCommon.h"

class	CameraProvider;

class	ThreadCamProcess : public QThread
{
	CameraProvider	*Parent;
public:
	bool	Terminated;
	ThreadCamProcess(CameraProvider *parent);

	virtual void run ();
};



class CameraProvider : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	CameraClass	*Cam[100];
	int			AllocatedCamNumb;
	CameraProviderHandle	*Handle[100];
	bool		CamFlag[100];
	int			CountOfCamera;
	DWORD		FirstAccessTime[100];

	int		CamNoTable[100];

	ThreadCamProcess	ThreadCamProcessInst;
public:
	CameraProvider(int CountOfCamera ,const QString &CameraDLLFileName ,LayersBase *base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~CameraProvider();

	void	ProcessInThread(void);
	CameraClass	*GetCam(int n)	{		return Cam[n];	}
	void	ShowSetting(int n);
	bool	LoadSettingFile(void);
	bool	SaveSettingFile(void);
	void	SetCamNo(int n ,int camNo);
	int		GetCamPointNumber(int camNo);
private:
	Ui::CameraProviderClass ui;

signals:
	void	SignalShowSetting(int Number);
	void	SignalIncrease();
private slots:
	void	SlotShowSetting(int Number);
	void	SlotIncrease();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
};

#endif // CAMERAPROVIDER_H
