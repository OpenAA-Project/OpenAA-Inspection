#ifndef LISTSTATISTICNG_H
#define LISTSTATISTICNG_H

#include "liststatisticng_global.h"

#include "ui_StatisticNGForm.h"

#include "XDLLOnly.h"

// プロパティ宣言開始
#include "XReviewPropertyBase.h"

class ListStatisticNG;

template<>
class PropertyBase<ListStatisticNG>;

typedef PropertyBase<ListStatisticNG> ListStatisticNGProperty;

namespace Ui{
class ListStatisticNGPropertyClass;
}
// プロパティ宣言終了

// 読み込んであるロットの基板をそれぞれ確認し、NGであるかどうかを調べ、NGならば、それに関連付けられているFキー情報を取得して合計値を出す
// OKならば基板:OKに追加する
// 
// ______|_NG_|_F1_|_F2_|_F3_|_～_|_F12_|_OK_|
// 基板表|____|____|____|____|____|_____|____|
// 基板裏|____|____|____|____|____|_____|____|
// _NG数_|____|____|____|____|____|_____|__0_|
// 
class LISTSTATISTICNG_EXPORT ListStatisticNG : public GUIFormBase
{
	Q_OBJECT

public:
	ListStatisticNG(LayersBase *Base,QWidget *parent);
	~ListStatisticNG();

public:
	// 更新要求を受け取り、リストを更新する.
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	void updateGUI();

public slots:
	void ResizeAction();

	void on_pbShowDetail_clicked();
	void on_pbSaveToFile_clicked();

public:
	QTableWidget *createDetailTableWidget(QString *errMsg=NULL);

private:
	//// 表関係
	//QList<int> FrontBoardWithFKeyList;	// F[i-1]キーの基板数 + Fキーなし
	//int FrontOKBoard;					// OKに属する基板数

	//QList<int> FrontNGWithFKeyList;		// F[i-1]キーに属するNG数の合計値 + Fキーなし


	//// 裏関係
	//QList<int> BackBoardWithFKeyList;	// F[i-1]キーの基板数 + Fキーなし
	//int BackOKBoard;					// OKに属する基板数

	//QList<int> BackNGWithFKeyList;		// F[i-1]キーに属するNG数の合計値 + Fキーなし

	Ui::StatisticNGClass ui;

private:
	QStringList m_FKeyDefinedNames;// F1~F12 & NoFKey

protected:
	void initFKeyDefinedNames();

public:
	inline QStringList getFKeyDefinedNames(bool fkeyOnly=false) const {
		if(fkeyOnly==false){
			return m_FKeyDefinedNames;
		}else{
			return m_FKeyDefinedNames.mid(0, m_FKeyDefinedNames.count()-2);
		}
	};
	inline QString *getFKeyDefinedNamesPtr(int index){ return &m_FKeyDefinedNames[index]; };
	QString getFKeyDefinedName(int index) const { return m_FKeyDefinedNames[index]; };

	int columnCount() const { return 14; };
	int rowCount() const { return 4; };

public:
	virtual	void Prepare(void)	override;
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 開始-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// プロパティのメインバッファ(GUIに使用する情報とUiからの入出力に使用)
private:
	ListStatisticNGProperty *m_property;

// プロパティ設定ダイアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::ListStatisticNGPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const ListStatisticNGProperty &getProperty() const { return *m_property; };
	ListStatisticNGProperty *getPropertyPtr() { return m_property; }

private:// 編集可能は内部からのみ
	inline ListStatisticNGProperty &getProperty() { return *m_property; };

// プロパティのバッファとプロパティ設定ダイアログへのアクセス関数
private:
	void setProperty(ListStatisticNGProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ListStatisticNGPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ListStatisticNGPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティダイアログのシグナルaccepted()に対応するスロット
private slots:
	void slot_propertyModified();

// プロパティのコピーとUiファイルとの連携
public:
	void setProperty(const ListStatisticNGProperty &property);
private:
	void setPropertyToUi(const ListStatisticNGProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ListStatisticNGProperty &property);
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

#endif // LISTSTATISTICNG_H
