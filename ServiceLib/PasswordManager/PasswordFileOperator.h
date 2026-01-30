/*
 * Copyright (C) 2015
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
	// ���@�\(�Z�[�u���[�h)
	bool save(QString filename);
	bool load(QString filename);

	// �p�X���[�h���t�����I�u�W�F�N�g�̒ǉ�
	void addItem(QString objName);
	// �p�X���[�h���t�����I�u�W�F�N�g�̍폜
	void delItem(QString objName);
	// �N���X�̒ǉ�
	void addClass(QString &ClassName, QString &Password, QVector<bool> *vFlags=NULL);
	bool delClass(int index);
	// �e�N���X�̐ݒ�
	// ���O
	void setClassName(int index, QString &Name);
	// �p�X���[�h
	void setPassword(int index, QString &Password);
	// �e�I�u�W�F�N�g�̉����t���O
	void setItemFlag(int nameIndex, int itemIndex, bool flag);
	
	// �N���X���擾
	int getNumClass();
	// �N���X���擾
	QString getClassName(int index);
	// �N���X�̃p�X���[�h�擾
	QString getPassword(int index);
	// �A�C�e�����擾
	int getNumItem();
	// �A�C�e�����擾
	QString getItem(int index);
	// �A�C�e�����ꗗ�擾
	QStringList getItems();
	// �w���N���X�̉����t���O�擾
	bool getItemFlag(int nameIndex, int itemIndex);
	// �`�F�b�N�p
	int hasClassName(QString &refName);// �߂��l�̓C���f�b�N�X�A������refName�Ɉ��v�������̂���������-1���Ԃ�
	int hasPassword(QString &refPassword);// ���L�Ɠ��l
	int hasItem(QString &refItem);// ���L�Ɠ��l

	static QString createItemName(QObject *obj);
public:
	class ClassContainer
	{
	public:
		ClassContainer():m_Name(/**/""), m_Password(/**/""), m_ItemFlags(0){};
	public:
		//�Z�b�^
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
		
		//�Q�b�^
		QString getName(){ return m_Name; };
		QString getPassword(){ return m_Password; };
		QVector<bool> getItemFlags(){ return m_ItemFlags; };
		bool getItemFlag(int index){ return m_ItemFlags[index]; };

		//�I�y���[�^
		const bool &operator[](int i){ return m_ItemFlags[i]; };
		
		//�C�e���[�^
		QVector<bool>::iterator begin(){ return m_ItemFlags.begin(); };
		QVector<bool>::iterator end(){ return m_ItemFlags.end(); };
	private:
		QString m_Name;			//�N���X��
		QString m_Password;		//���̃N���X�̃p�X���[�h
		QVector<bool> m_ItemFlags;	//���̃N���X�̃I�u�W�F�N�g�ɑ΂����p�X���[�h�t���O
	public:
		typedef QStringList::iterator iterator;
	};
signals:
	void dataChanged();
private:
	int m_version;
	QStringList m_itemList;//�p�X���[�h�����������I�u�W�F�N�g
	QVector<ClassContainer> m_classes;
};