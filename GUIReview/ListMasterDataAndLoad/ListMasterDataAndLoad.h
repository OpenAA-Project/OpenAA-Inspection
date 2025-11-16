#ifndef LISTMASTERDATAANDLOAD_H
#define LISTMASTERDATAANDLOAD_H

#include "listmasterdataandload_global.h"

#include "XDLLOnly.h"

#include "ListMaster.h"

// プロパティ宣言開始
#include "XReviewPropertyBase.h"

class ListMasterDataAndLoad;

template<>
class PropertyBase<ListMasterDataAndLoad>;

typedef PropertyBase<ListMasterDataAndLoad> ListMasterDataAndLoadProperty;

namespace Ui{
class ListMasterDataAndLoadPropertyClass;
}
// プロパティ宣言終了

class LISTMASTERDATAANDLOAD_EXPORT ListMasterDataAndLoad : public GUIFormBase
{
	Q_OBJECT

public:
	ListMasterDataAndLoad(LayersBase *Base,QWidget *parent);
	~ListMasterDataAndLoad();

	virtual	void	Prepare(void)	override;
public:
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

public:
	ListMasterForm m_ListMasterForm;// メインフォーム

public slots:
	void ResizeAction();//ウィンドウサイズ変更時の動作
	void updateTable();
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 開始-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// プロパティのメインバッファ(GUIに使用する情報とUiからの入出力に使用)
private:
	ListMasterDataAndLoadProperty *m_property;

// プロパティ設定ダイアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::ListMasterDataAndLoadPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const ListMasterDataAndLoadProperty &getProperty() const { return *m_property; };
	ListMasterDataAndLoadProperty *getPropertyPtr() { return m_property; }

private:// 編集可能は内部からのみ
	inline ListMasterDataAndLoadProperty &getProperty() { return *m_property; };

// プロパティのバッファとプロパティ設定ダイアログへのアクセス関数
private:
	void setProperty(ListMasterDataAndLoadProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ListMasterDataAndLoadPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ListMasterDataAndLoadPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティダイアログのシグナルaccepted()に対応するスロット
private slots:
	void slot_propertyModified();
	void showMachineIDFilterDialog();

// プロパティのコピーとUiファイルとの連携
public:
	void setProperty(const ListMasterDataAndLoadProperty &property);
private:
	void setPropertyToUi(const ListMasterDataAndLoadProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ListMasterDataAndLoadProperty &property);
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

#endif // LISTMASTERDATAANDLOAD_H
