#pragma once

#include <QString>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QVector>
#include <QTextStream>


class PasswordFileOperator : public QObject
{
	Q_OBJECT

public:
	PasswordFileOperator(QObject *parent=0);
public:
	// 主機能(セーブロード)
	bool save(QString filename);
	bool load(QString filename);

	// パスワードを付けるオブジェクトの追加
	void addItem(QString objName);
	// パスワードを付けるオブジェクトの削除
	void delItem(QString objName);
	// クラスの追加
	void addClass(QString &ClassName, QString &Password, QVector<bool> *vFlags=NULL);
	bool delClass(int index);
	// 各クラスの設定
	// 名前
	void setClassName(int index, QString &Name);
	// パスワード
	void setPassword(int index, QString &Password);
	// 各オブジェクトの解放フラグ
	void setItemFlag(int nameIndex, int itemIndex, bool flag);
	
	// クラス数取得
	int getNumClass();
	// クラス名取得
	QString getClassName(int index);
	// クラスのパスワード取得
	QString getPassword(int index);
	// アイテム数取得
	int getNumItem();
	// アイテム名取得
	QString getItem(int index);
	// アイテム名一覧取得
	QStringList getItems();
	// 指定クラスの解除フラグ取得
	bool getItemFlag(int nameIndex, int itemIndex);
	// チェック用
	int hasClassName(QString &refName);// 戻り値はインデックス、ただしrefNameに一致するものが無ければ-1が返る
	int hasPassword(QString &refPassword);// 上記と同様
	int hasItem(QString &refItem);// 上記と同様

	static QString createItemName(QObject *obj);
public:
	class ClassContainer
	{
	public:
		ClassContainer():m_Name(/**/""), m_Password(/**/""), m_ItemFlags(0){};
	public:
		//セッタ
		void setName(QString &Name){
			m_Name = Name;
		};
		void setPassword(QString &Password){
			m_Password = Password;
		};
		void setItemFlags(QVector<bool> &itemFlags){
			m_ItemFlags = itemFlags;
		};
		void setItemFlag(int index, bool flag){
			if(index>=m_ItemFlags.size()){
				int oldsize = m_ItemFlags.size();
				m_ItemFlags.resize(index+1);
				for(int i=oldsize; i<index+1; i++){
					m_ItemFlags[i] = false;
				}
			}
			if(m_ItemFlags[index] != flag){
				m_ItemFlags[index] = flag;
			}
		};
		void addItemFlag(bool addFlag){
			m_ItemFlags.push_back(addFlag);
		}
		
		//ゲッタ
		QString getName(){ return m_Name; };
		QString getPassword(){ return m_Password; };
		QVector<bool> getItemFlags(){ return m_ItemFlags; };
		bool getItemFlag(int index){ return m_ItemFlags[index]; };

		//オペレータ
		const bool &operator[](int i){ return m_ItemFlags[i]; };
		
		//イテレータ
		QVector<bool>::iterator begin(){ return m_ItemFlags.begin(); };
		QVector<bool>::iterator end(){ return m_ItemFlags.end(); };
	private:
		QString m_Name;			//クラス名
		QString m_Password;		//このクラスのパスワード
		QVector<bool> m_ItemFlags;	//このクラスのオブジェクトに対するパスワードフラグ
	public:
		typedef QStringList::iterator iterator;
	};
signals:
	void dataChanged();
private:
	int m_version;
	QStringList m_itemList;//パスワードがかかったオブジェクト
	QVector<ClassContainer> m_classes;
};