#ifndef SHOWVRSOPERATION_H
#define SHOWVRSOPERATION_H

#include "showvrsoperation_global.h"

#include "XDLLOnly.h"

#include "ui_ShowVRSOperationForm.h"

// プロパティ宣言開始
#include "XReviewPropertyBase.h"

class ShowVRSOperation;

template<>
class PropertyBase<ShowVRSOperation>;

typedef PropertyBase<ShowVRSOperation> ShowVRSOperationProperty;

namespace Ui{
class ShowVRSOperationPropertyClass;
}

// プロパティ宣言終了

// VRSの手動による移動要求を行うコンポーネント
// 今までは画面をクリックすることによる移動しか手動での移動方法が無かったため、アライメントに手間がかかりました
// これを使用することにより、その手間を大幅に軽減させます
class SHOWVRSOPERATION_EXPORT ShowVRSOperation : public GUIFormBase
{
	Q_OBJECT

public:
	ShowVRSOperation(LayersBase *Base,QWidget *parent);
	~ShowVRSOperation();

private:
	Ui::ShowVRSOperationClass ui;

public:
	bool showVRSSettingButton;
	QString passwordForSettingButton;

private:
	bool	settingButtonIsFree;

public:
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void Prepare(void)	override;

public slots:
	void on_pbVRSSetting_clicked();
	void on_pbAlignmentManager_clicked();
	void on_pbSetZDiastance_clicked();
	void on_pbOrigin_clicked();
	void on_pbEscape_clicked();
	void on_pbMoveUp_clicked();
	void on_pbMoveDown_clicked();
	void on_pbMoveLeft_clicked();
	void on_pbMoveRight_clicked();
	void on_cbYReverse_toggled(bool);
	void on_cbXReverse_toggled(bool);
	void on_sbZDistanceStep_valueChanged(int);

	//void on_pbTest_clicked();
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 開始-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// プロパティのメインバッファ(GUIに使用する情報とUiからの入出力に使用)
private:
	ShowVRSOperationProperty *m_property;

// プロパティ設定ダイアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::ShowVRSOperationPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const ShowVRSOperationProperty &getProperty() const { return *m_property; };
	ShowVRSOperationProperty *getPropertyPtr() { return m_property; }

private:// 編集可能は内部からのみ
	inline ShowVRSOperationProperty &getProperty() { return *m_property; };

// プロパティのバッファとプロパティ設定ダイアログへのアクセス関数
private:
	void setProperty(ShowVRSOperationProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ShowVRSOperationPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ShowVRSOperationPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティダイアログのシグナルaccepted()に対応するスロット
private slots:
	void slot_propertyModified();

// プロパティのコピーとUiファイルとの連携
public:
	void setProperty(const ShowVRSOperationProperty &property);
private:
	void setPropertyToUi(const ShowVRSOperationProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ShowVRSOperationProperty &property);
	void setPropertyFromUi();

// コンストラクタで使用するプロパティの初期化
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 終了-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

private slots:
	void updateMoveLength(int value);
	void updateZDistanceStep(int value);
	void updateSequencePosition();

private:
	QTimer m_seqenceUpdateTime;

private:
	QTimer &sequenceUpdateTime(){ return m_seqenceUpdateTime; };
};

#endif // SHOWVRSOPERATION_H
