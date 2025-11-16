#ifndef LIVECAMERAALGONTSC_H
#define LIVECAMERAALGONTSC_H

#include "livecameraalgontsc_global.h"

#include <QPushButton>
#include <QThread>

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"

#include "CameraSettingForm.h"

// プロパティ宣言開始
#include "XReviewPropertyBase.h"

class LiveCameraAlgoNTSC;

template<>
class PropertyBase<LiveCameraAlgoNTSC>;

typedef PropertyBase<LiveCameraAlgoNTSC> LiveCameraAlgoNTSCProperty;

namespace Ui{
class LiveCameraAlgoNTSCPropertyClass;
}
// プロパティ宣言終了


// 表示更新スレッド
class ThreadView : public QThread
{
	Q_OBJECT

public:
	ThreadView():m_flg_updateEnable(true),m_flg_stop(false),m_intervalTime(50){};
	ThreadView(int IntervalTime):m_flg_stop(false),m_intervalTime(IntervalTime){};

public:
	void setStopFlag(bool flg){ m_flg_stop = flg; };
	void setUpdateEnable(bool flg){ m_flg_updateEnable = flg; }
	void stop(){ m_flg_stop = true; };
	void setIntervalTime(int time){ m_intervalTime = time; };

protected:
	void run();

private:
	volatile bool m_flg_updateEnable;
	volatile bool m_flg_stop;
	int m_intervalTime;

signals:
	void update();
};

// 表示画面
// カメラ映像を表示する
// todo signal
//  clicked(QPoint)    -> 微動
//  setParameter(RGB)  -> RGBバイアス
class CameraView : public QLabel
{
	Q_OBJECT

public:
	CameraView(QWidget *parent, bool EditMode=false, int refleshTime=50);
	~CameraView();

public:
	void Resize(int width, int height);
	bool Open();
	bool Close();
	bool StartLive();
	bool StopLive();
	bool SingleShot();
	void Restart();
	void SetBrightness(int BArray[]);
	bool CreateImageBuffer(int width, int height);
	int *GetPlusRedPtr();
	int *GetPlusGreenPtr();
	int *GetPlusBluePtr();
	int GetPlusRed();
	int GetPlusGreen();
	int GetPlusBlue();
	void ShowSettingForm();
	bool GetCameraImage(QImage *image);

public slots:
	void GetCameraImageFast();
	void GetCameraImageModify();
	void Update();
	void StartUpdate();
	void StopUpdate();
	void SetRGB(int r, int g, int b);
	void SetWindow(QLabel *target);

private:
	QVector<QVector<unsigned char*> >	m_iData;
	QImage m_Image;
	ThreadView *m_Thread;
	int m_CapXLen, m_CapYLen;
	int m_BrightArray[256];
	int m_PlusRed, m_PlusGreen, m_PlusBlue;
	CameraSettingForm *m_SettingForm;

	bool m_EditMode;
	QLabel *m_paintWidget;
};


// GUI本体
class LIVECAMERAALGONTSC_EXPORT LiveCameraAlgoNTSC : public GUIFormBase
{
	Q_OBJECT

public:
	LiveCameraAlgoNTSC(LayersBase *Base ,QWidget *parent);
	~LiveCameraAlgoNTSC(void);
	
	virtual void	Prepare(void)	override;

	bool	StartLive();//再生
	bool	StopLive();//停止
	bool	SingleShot();//スナップショット撮影
	bool	Close();//デバイスをクローズ
	bool	Open();//デバイスをオープン
	bool	Init();//初期化

	void	SetBrightness(int BArray[]);//輝度アレイを設定 255
	void	SetPlusRGB(int Red,int Green,int Blue);//各RGBのバイアス値設定

	int		GetWidth()	{	return(640);	}//横方向サイズ
	int		GetHeight()	{	return(480);	}//縦方向サイズ

public slots:
	void	ResizeAction();//ウィンドウサイズ変更時の動作
	void	SettingAction();
	void	RestartAction();//カメラデバイスの再オープン
	void	SnapAction();
	bool	Save();
	bool	Load();
	
public:
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	void	contextMenuEvent(QContextMenuEvent * event )	override;
	virtual	void	mousePressEvent(QMouseEvent *)	override;

private:
	CameraView	m_CameraView;	//カメラ映像表示ウィジェット(GUIのメインウィジェット)
	int m_PlusRed,m_PlusGreen,m_PlusBlue;
	int m_BrightArray[256];
	//ThreadView *m_ThreadView;
	QWidget	*m_parent;
	QMenu	*m_ContextMenu;
	QAction	*m_SettingAction;
	QAction	*m_ResetAction;
	QAction *m_SnapAction;

/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 開始-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// プロパティのメインバッファ(GUIに使用する情報とUiからの入出力に使用)
private:
	LiveCameraAlgoNTSCProperty *m_property;

// プロパティ設定ダイアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::LiveCameraAlgoNTSCPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const LiveCameraAlgoNTSCProperty &getProperty() const { return *m_property; };
	LiveCameraAlgoNTSCProperty *getPropertyPtr() { return m_property; }

private:// 編集可能は内部からのみ
	inline LiveCameraAlgoNTSCProperty &getProperty() { return *m_property; };

// プロパティのバッファとプロパティ設定ダイアログへのアクセス関数
private:
	void setProperty(LiveCameraAlgoNTSCProperty *property){ m_property = property; };
	void setPropertyUi(Ui::LiveCameraAlgoNTSCPropertyClass *ui){ m_propertyUi = ui; };
	Ui::LiveCameraAlgoNTSCPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティダイアログのシグナルaccepted()に対応するスロット
private slots:
	void slot_propertyModified();

// プロパティのコピーとUiファイルとの連携
public:
	void setProperty(const LiveCameraAlgoNTSCProperty &property);
private:
	void setPropertyToUi(const LiveCameraAlgoNTSCProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(LiveCameraAlgoNTSCProperty &property);
	void setPropertyFromUi();

// コンストラクタで使用するプロパティの初期化
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 終了-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
};

#endif // LIVECAMERAALGONTSC_H
