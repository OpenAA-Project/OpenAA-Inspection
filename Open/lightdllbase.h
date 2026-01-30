/*
 * Copyright (C) 2023
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

//---------------------------------------------------------------------------

#ifndef LightDLLBaseH
#define LightDLLBaseH
//---------------------------------------------------------------------------

//#include "XLightBase.h"
#include <QIODevice>
//class   XAIPLightBase : public XLightBase
class   LightDLLBase
{
public:
	LightDLLBase(){}
	virtual ~LightDLLBase(){}

	virtual LightDLLBase &operator=(LightDLLBase &src)	=0;
	virtual bool		operator!=(LightDLLBase &src2)	=0;
	virtual bool		operator==(LightDLLBase &src2){	return !operator!=(src2);	}

	virtual char		*GetName()						=0;
	virtual bool		LEDSave(QIODevice &str)			=0;
	virtual bool		LEDLoad(QIODevice &str)			=0;
	virtual bool		LEDSaveDefault()				=0;
	virtual bool		LEDLoadDefault()				=0;

	virtual void	   *InitialLED()					=0;		//�����ҏW������������
//	virtual void		TransferLED(TProgressBar *PBar)	=0;		//�����ϐ����k�d�c�R���g���[���ɓ]������
	virtual void		TransferLED()					=0;		//�����ϐ����k�d�c�R���g���[���ɓ]������
	virtual void		Clear()							=0;		//�����ϐ��̃N���A

	virtual bool		LEDConditionSave(QIODevice &str)=0;
	virtual bool		LEDConditionLoad(QIODevice &str)=0;

	virtual bool		GetLighting()					=0;		//�o�͂d�����������M���̏��Ԃ��Ԃ�
	virtual void		SetLighting(bool mode)			=0;		//�o�͂d�����������M����mode�ɏ]���ďo�͂���

	virtual bool		IsEnabled()						=0;		//�����̂k�d�c�ϐ����S�ĂO�̂Ƃ�false

	virtual int			GetBarCount()					=0;
	virtual void		SetLEDBarBright(int BarID ,int brightness)	=0;		//�P�񕪂��_��������
	virtual void		GetNowLEDBarAveragedLevel(int BarLevel[100])=0;
	virtual int			GetMaxLEDLevel()							=0;		//�ő��P�x�l���Ԃ�
	virtual int			GetMaxBrightness(int BarID , int LEDID)		=0;		//�ŗL�̂k�d�c�P�x�l���Ԃ�
	virtual int			GetMaxSheetNumb()							=0;		//�����ŕۗL�ł����V�[�g�����Ԃ�
	virtual bool		SetDisplaySheet(int sheet)					=0;		//�\���V�[�g���ݒ�
			void		SetPowerRateAll(double rate);						//�Ɩ��̏o�͋��x���ύX����
	virtual void		SetPowerRate(int BarID,double rate)			=0;		//�Ɩ��̏o�͋��x���ύX����
	virtual double		GetPowerRate(int BarID)						=0;
	virtual void		ResetPowerRate()							=0;
	virtual int			GetBarComment(int BarID,char *Buff)			=0;

	virtual int			GetOneBrightDirectly(int sheet ,int row, int col)		=0;
	virtual void		SetOneBrightDirectly(int sheet ,int row, int col ,int b)=0;

	virtual void		SetWaitTime(int WaitTime)		=0;

	virtual bool		LightOn()						=0;
	virtual bool		LightOff()						=0;
};

#endif