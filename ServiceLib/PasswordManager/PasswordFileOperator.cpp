#include "XTypeDef.h"
#include "PasswordFileOperator.h"

PasswordFileOperator::PasswordFileOperator(QObject *parent)
:QObject(parent)
{
	m_version = 10;
	m_itemList.clear();
	m_classes.clear();
}

bool PasswordFileOperator::save(QString filename)
{
	QFileInfo info(filename);
	QFile file(info.absoluteFilePath());
	file.open(QIODevice::WriteOnly);
	if(!file.isOpen())
		return false;

	QTextStream stream(&file);

	stream << "version1.0" << Qt::endl;

	for(int itemIndex=0; itemIndex<m_itemList.size(); itemIndex++){
		if(itemIndex!=0)stream << ",";
		stream << m_itemList[itemIndex];
	}

	stream << Qt::endl;

	if(m_classes.size()==0)
	{
		stream << Qt::endl;
		return true;
	}

	for(QVector<ClassContainer>::iterator classCategory=m_classes.begin(); classCategory!=m_classes.end(); classCategory++){
		
		stream << classCategory->getName() + ";" + classCategory->getPassword() + ";";

		for(int i = 0; i < classCategory->getItemFlags().size(); i++){
			if(i!=0) stream << ",";
			stream << (classCategory->getItemFlag(i) == false ? 0 : 1);
		}
		
		stream << Qt::endl;
	}
	file.close();
	return true;
}



bool PasswordFileOperator::load(QString filename)
{
	QFileInfo info(filename);
	QFile file(info.absoluteFilePath());

	file.open(QIODevice::ReadOnly);
	if(!file.isOpen())// ファイルが無ければ新しく作る
	{
		save(info.absoluteFilePath());
		return true;
	}

	QTextStream stream(&file);
	QString line;

	// バージョン情報取得
	line = stream.readLine();
	if(line == "version1.0"){
		m_version = 10;
	} else {
		return false;
	}

	// パスワード設定オブジェクト名取得
	line = stream.readLine();
	if(line!=/**/"")m_itemList = line.split(',');

	// 各クラスの名前、パスワード、パスワード解除項目の取得
	m_classes.clear();
	for(int classID=0; stream.atEnd() == 0; classID++){
		ClassContainer addCont;

		line = stream.readLine();

		QStringList list = line.split(';');

		if(list.size() != 3)return false;

		setClassName(classID, list[0]);
		setPassword(classID, list[1]);
		if(m_itemList.size()==0)continue;
		QStringList vFlags = list[2].split(',');
		for(int itemNo=0; itemNo<vFlags.size(); itemNo++){
			if(vFlags[itemNo] == "0")
				setItemFlag(classID, itemNo, false);
			else if(vFlags[itemNo] == "1")
				setItemFlag(classID, itemNo, true);
			else
				setItemFlag(classID, itemNo, false);
		}
	}

	return true;
}

void PasswordFileOperator::addItem(QString objName)
{
	qDebug("Enter addItem(QString objName)");
	if(!m_itemList.contains(objName)){
		m_itemList.push_back(objName);
		for(int i=0; i<m_classes.size(); i++)
			m_classes[i].addItemFlag(false);
		emit dataChanged();
	}
	qDebug("Exit addItem(QString objName)");
}

// パスワードを付けるオブジェクトの削除
void PasswordFileOperator::delItem(QString objName)
{
	qDebug("Enter delItem(QString objName)");
	int delIndex = m_itemList.indexOf(objName);
	if(delIndex==-1)return;
	m_itemList.removeAt(delIndex);
	for(int i=0; i<m_classes.size(); i++){
		QVector<bool> vFlags = m_classes[i].getItemFlags();
		vFlags.remove(delIndex);
		m_classes[i].setItemFlags(vFlags);
	}
	emit dataChanged();
	qDebug("Exit delItem(QString objName)");
}

// クラスの追加
void PasswordFileOperator::addClass(QString &ClassName, QString &Password, QVector<bool> *vFlags)
{
	ClassContainer addClass;
	addClass.setName(ClassName);
	addClass.setPassword(Password);

	if(vFlags==NULL){
		QVector<bool> vIns = QVector<bool>(m_itemList.size(), false);
		addClass.setItemFlags(vIns);

		m_classes.push_back(addClass);
		return;
	}

	QVector<bool> vInit(*vFlags);

	if(vInit.size()<m_itemList.size()){
		int oldsize = vInit.size();
		vInit.resize(m_itemList.size());
		for(int i=oldsize; i<m_itemList.size(); i++)
			vInit[i] = false;
	}
	addClass.setItemFlags(vInit);
	m_classes.push_back(addClass);
}

bool PasswordFileOperator::delClass(int index)
{
	if(index<0 || index>=m_classes.size())return false;
	m_classes.remove(index);
	return true;
}

// 各クラスの設定
// 名前
void PasswordFileOperator::setClassName(int index, QString &Name){
	if(index >= m_classes.size())m_classes.resize(index+1);
	if(m_classes[index].getName()==Name)return;
	m_classes[index].setName(Name);
}

// パスワード
void PasswordFileOperator::setPassword(int index, QString &Password){
	if(index >= m_classes.size())m_classes.resize(index+1);
	if(m_classes[index].getPassword()==Password)return;
	m_classes[index].setPassword(Password);
}

// 各オブジェクトの解放フラグ
void PasswordFileOperator::setItemFlag(int nameIndex, int itemIndex, bool flag){
	if(nameIndex >= m_classes.size())m_classes.resize(nameIndex+1);
	m_classes[nameIndex].setItemFlag(itemIndex, flag);
}


int PasswordFileOperator::getNumClass(){
	return m_classes.size();
}

QString PasswordFileOperator::getClassName(int index){ Q_ASSERT(index < m_classes.size()); return m_classes[index].getName(); }
QString PasswordFileOperator::getPassword(int index){ Q_ASSERT(index < m_classes.size()); return m_classes[index].getPassword(); }
int PasswordFileOperator::getNumItem(){ return m_itemList.size(); }
QString PasswordFileOperator::getItem(int index){ return m_itemList[index]; }
QStringList PasswordFileOperator::getItems(){ return m_itemList; }
bool PasswordFileOperator::getItemFlag(int nameIndex, int itemIndex)
{
	Q_ASSERT(nameIndex < m_classes.size());
	return m_classes[nameIndex].getItemFlag(itemIndex);
}

// チェック用
int PasswordFileOperator::hasClassName(QString &refName){
	for(int i=0; i<m_classes.size(); i++){
		if(m_classes[i].getName()==refName)return i;
	}
	return -1;
}
int PasswordFileOperator::hasPassword(QString &refPassword){
	for(int i=0; i<m_classes.size(); i++){
		if(m_classes[i].getPassword()==refPassword)return i;
	}
	return -1;
}

int PasswordFileOperator::hasItem(QString &refItem){
	return m_itemList.indexOf(refItem);
}

QString PasswordFileOperator::createItemName(QObject *obj)
{
		QStringList list;
		QObject *_obj = obj;
		for(_obj=_obj->parent(); _obj!=NULL; _obj=_obj->parent())
			list.push_front(_obj->metaObject()->className());

		QString myName;
		for(int i=0; i<list.size(); i++){
			myName += list[i];
			if(i!=list.size()-1)
				myName += "/";
		}
		return myName;
}