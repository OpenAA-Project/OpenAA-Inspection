#ifndef SELECTLOTFORREVIEW_H
#define SELECTLOTFORREVIEW_H

#include "selectlotforreview_global.h"
#include "ui_SelectLotForm.h"

#include "XDLLOnly.h"

#include "../XGUICmdReviewCommon.h"

// プロパティ宣言開始

class SelectLotForReview;

template<>
class PropertyBase<SelectLotForReview>;

typedef PropertyBase<SelectLotForReview> SelectLotForReviewProperty;

namespace Ui{
class SelectLotForReviewPropertyClass;
}

// プロパティ宣言終了

// ロットの選択表示GUI
// 基本的にはコンパイル後に生成されたDLLを他のGUIなどでよみこみ、CreateInstanceで生成したインスタンスをGeneralDialogで表示する
class SELECTLOTFORREVIEW_EXPORT SelectLotForReview : public GUIFormBase
{
	Q_OBJECT

public:
	SelectLotForReview(LayersBase *Base,QWidget *parent);
	~SelectLotForReview();

	int	WidthFileName;
	int	WidthLotName;
	bool	SameWidth;
	
	virtual	void	Prepare(void)	override;

public:
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	//void	SetSide(Review::SideType side){ m_Side = side; };
	void	updateGUI(bool onlySelf=true);
	void	setGUIEnable(bool enable);
	
private:
	//void	ShowLotList(Review::SideType side, const QStringList &LotList, const QStringList &LotNameList);
	void	ShowLotList(Review::SideType side, const LotInfoList &lotList);

	class SelectLotForReviewLocker;
public slots:
	void	doubleClicked(int row, int column);
	void	okButtonClicked();
	void	cancelButtonClicked();
	void	updateLotList();

signals:
	void	SignalClose();// GeneralDialog用終了シグナル

private:
	Ui::SelectLotFormClass ui;
	//Review::SideType m_Side;

	int m_FrontMasterCode;
	int m_FrontMachineID;
	int m_BackMasterCode;
	int m_BackMachineID;
	QString m_FolderName;
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 開始-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// プロパティのメインバッファ(GUIに使用する情報とUiからの入出力に使用)
private:
	SelectLotForReviewProperty *m_property;

// プロパティ設定ダイアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::SelectLotForReviewPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const SelectLotForReviewProperty &getProperty() const { return *m_property; };
	SelectLotForReviewProperty *getPropertyPtr() { return m_property; }

private:// 編集可能は内部からのみ
	inline SelectLotForReviewProperty &getProperty() { return *m_property; };

// プロパティのバッファとプロパティ設定ダイアログへのアクセス関数
private:
	void setProperty(SelectLotForReviewProperty *property){ m_property = property; };
	void setPropertyUi(Ui::SelectLotForReviewPropertyClass *ui){ m_propertyUi = ui; };
	Ui::SelectLotForReviewPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティダイアログのシグナルaccepted()に対応するスロット
private slots:
	void slot_propertyModified();
	void slot_propertyRejected();

// プロパティのコピーとUiファイルとの連携
public:
	void setProperty(const SelectLotForReviewProperty &property);
private:
	void setPropertyToUi(const SelectLotForReviewProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(SelectLotForReviewProperty &property);
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

#endif // SELECTLOTFORREVIEW_H
