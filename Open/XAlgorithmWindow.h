/*
 * Copyright (C) 2022
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
#include "XServiceForLayers.h"
#include "XPasswordQWidget.h"
#include "XDataAlgorithm.h"
#include <QObject>
#include "XDisplaySimPanel.h"
#include "XDataAlgorithmList.h"

class QLineEdit;
class QCheckBox;
class QRadioButton;
class QDoubleSpinBox;
class QSpinBox;
class QComboBox;
class QToolButton;

class ItemMember : public QObject ,public NPList<ItemMember>
{
    Q_OBJECT

public:
	union{
		QLineEdit		*LineEdit;
		QCheckBox		*CheckBox;
		QRadioButton	*RadioButton;
		QDoubleSpinBox	*DoubleSpinBox;
		QSpinBox		*SpinBox;
		QComboBox		*ComboBox;
		QToolButton		*ToolButton;
	};
	enum _ControlType
	{
		 Enum_LineEdit		
		,Enum_CheckBox		
		,Enum_RadioButton	
		,Enum_DoubleSpinBox	
		,Enum_SpinBox		
		,Enum_ComboBox		
		,Enum_ToolButton		
	}ControlType;

	union{
		QString *StringMember;
		bool	*BoolMember;
		double	*DoubleMember;
		float	*FloatMember;
		int		*IntMember;
	};
	enum _MemberType
	{
		 Enum_QString 
		,Enum_bool	
		,Enum_double	
		,Enum_float	
		,Enum_int		
	}MemberType;

	ItemMember(QLineEdit *e ,QString *member);
	ItemMember(QCheckBox *e ,bool *member);
	ItemMember(QRadioButton *e ,bool *member);
	ItemMember(QDoubleSpinBox *e ,double *member);
	ItemMember(QDoubleSpinBox *e ,float *member);
	ItemMember(QSpinBox *e ,int *member);
	ItemMember(QComboBox *e ,int *member);
	ItemMember(QToolButton *e ,bool *member);

	void	Show(void);
	void	GetDataFromControl(void);
private slots:

};

class AlgorithmWindow : public ServiceForLayers ,public PasswordInQWodget
{
	ItemsByAlgorithm		Items;
	AlgorithmBase			*ABase;
	AlgorithmThreshold		*TempData;
	NPListPack<ItemMember>	ItemMemberContainer;
	ChangedMap				ChangedMapInThreshold;
	//DisplaySimPanel		SimPanel;

public:
	AlgorithmWindow(LayersBase *Base);
	virtual	~AlgorithmWindow(void);

	void	Initial(ItemsByAlgorithm &items);

	virtual	void	AllocateItemMember(AlgorithmThreshold *t)				=0;
	virtual	AlgorithmThreshold	*CreateThresholdInstance(AlgorithmBase *t)	=0;

	bool	SaveInLibrary(void);
	bool	LoadFromLibrary(void);
	bool	ReflectOne(void);
	bool	ReflectAll(void);
	bool	Test(void);

protected:
	void	AddItemMember(QLineEdit *e		,QString *member);
	void	AddItemMember(QCheckBox *e		,bool *member);
	void	AddItemMember(QRadioButton *e	,bool *member);
	void	AddItemMember(QDoubleSpinBox *e ,double *member);
	void	AddItemMember(QDoubleSpinBox *e ,float *member);
	void	AddItemMember(QSpinBox *e		,int *member);
	void	AddItemMember(QComboBox *e		,int *member);
	void	AddItemMember(QToolButton *e	,bool *member);

	virtual	void	GetDataInTempFromWindow(void);
	virtual	void	ShowDataInTempToWindow(void);
	virtual	void	ShowResultItemData(QByteArrayList &ResultItemDataList);
};