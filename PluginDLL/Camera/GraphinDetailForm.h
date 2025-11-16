#ifndef GRAPHINDETAILFORM_H
#define GRAPHINDETAILFORM_H

#include <QDialog>
#include "ui_GraphinDetailForm.h"

class GraphinDetailForm : public QDialog
{
	Q_OBJECT

public:
	GraphinDetailForm(Qt::HANDLE handle, const QString &CameraConfigFileName, const QString &DllFileName, QWidget *parent = 0);
	~GraphinDetailForm();

	QString cameraDLLFileName() const { return m_CameraDLLFileName; };
	void setCameraDLLFileName(const QString &dllName){ m_CameraDLLFileName = _convertYenToSlash( dllName ); ui.leCameraDLL->setText(m_CameraDLLFileName); };

	QString deviceName() const { return m_DeviceName; };
	void setDeviceName(const QString &name){ m_DeviceName = name; ui.leDeviceName->setText(name); };

	QString deviceRevision() const { return m_DeviceRevision; };
	void setDeviceRevision(const QString &revision){ m_DeviceRevision = revision; ui.leDeviceRevision->setText(revision); };

	QString deviceDLLVersion() const { return m_DeviceDLLVersion; };
	void setDeviceDLLVersion(const QString &version){ m_DeviceDLLVersion = version; ui.leDeviceDllVersion->setText(version); };

	QString deviceDLLFileName() const { return m_DeviceDLLFileName; };
	void setDeviceDLLFileName(const QString &filename){ m_DeviceDLLFileName = _convertYenToSlash( filename ); ui.leDeviceDLL->setText(m_DeviceDLLFileName); };
	
	QString cameraConfigFileName() const { return m_CameraConfigFileName; };
	void setCameraConfigFileName(const QString &filename){ m_CameraConfigFileName = _convertYenToSlash( filename ); ui.leConfigFile->setText(m_CameraConfigFileName); };

	QString deviceState() const { return m_DeviceState; };
	void setDeviceState(const QString &state){ m_DeviceState = state; ui.leDeviceState->setText(state); };

	int exposureTime() const { return m_expTime; };
	void setExposureTime(int expTime){	m_expTime = expTime;	};

	int *redCustomLut() const { return m_RCustomLut; };
	int redCustomLut(int i) const { return m_RCustomLut[i]; };
	void setRedCustomLut(int *lutArray){ m_RCustomLut = lutArray;	};
	int *greenCustomLut() const { return m_GCustomLut; };
	int greenCustomLut(int i) const { return m_RCustomLut[i]; };
	void setGreenCustomLut(int *lutArray){ m_GCustomLut = lutArray;	};
	int *blueCustomLut() const { return m_BCustomLut; };
	int blueCustomLut(int i) const { return m_RCustomLut[i]; };
	void setBlueCustomLut(int *lutArray){ m_BCustomLut = lutArray;	};

	QString proofDataFileName() const { return m_ProofDataFileName; };
	void setProofDataFileName(const QString &filename){	m_ProofDataFileName	= _convertYenToSlash( filename );	};

	int isRToL() const { return m_RtL; };
	void setRtoL(int enable){ m_RtL = enable;	};

	bool isEnable32bitMode() const { return m_E32bitMode; };
	void setEnable32bitMode(bool enable){ m_E32bitMode = enable;	};

	QString cRxLineBuff() const { return m_BuffcRxLine; };
	void setcRxLineBuff(const QString &str){ m_BuffcRxLine = str;	};

	int dllLogCounter() const { return m_DLLLogCnt; };
	void setDLLLogCounter(int cnt){ m_DLLLogCnt	=cnt; };

	QStringList dllLogString() const { return m_DLLLogStr; };
	//void SetDllLogString	(char Value[][64])	{	memcpy(DllLogStr,Value,256*64);	};
	void setDLLLogString(const QStringList &list){ m_DLLLogStr = list; };

private:
	Ui::GraphinDetailFormClass ui;

	QString m_CameraDLLFileName;
	QString m_DeviceName;
	QString m_DeviceRevision;
	QString m_DeviceDLLVersion;
	QString m_DeviceDLLFileName;
	QString m_CameraConfigFileName;
	QString m_DeviceState;

	int		m_expTime;
	int		*m_RCustomLut;
	int		*m_GCustomLut;
	int		*m_BCustomLut;
	QString	m_ProofDataFileName;
	int		m_RtL;
	bool	m_E32bitMode;
	QString	m_BuffcRxLine;
	int		m_DLLLogCnt;
	//char	DllLogStr[256][64];
	QStringList m_DLLLogStr;

private:
	QString _convertYenToSlash(const QString &sorce){
		QString ret = sorce;
		ret.replace(QChar('\\'), QChar('/'));
		return ret;
	};

private slots:
	void on_pbOutputLog_clicked();
	void on_pbClose_clicked();
};

#endif // GRAPHINDETAILFORM_H
