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

#ifndef XAffinH
#define XAffinH
//---------------------------------------------------------------------------
bool    GetAffin(int x1,int y1
                ,int x2,int y2          //�}�X�^�[�摜���̃A���C�����g��ʒu
                ,double cx, double cy   //���]���S
                ,int X1 ,int Y1
                ,int X2 ,int Y2     //�T���������ʂ̃A���C�������g�ʒu
                ,double &ResultPx,double &ResultPy  //���s�ړ���
                ,double &ResultS                    //���]�ʁi���W�A���j
                ,double &ResultAlpha);              //�g�嗦

bool	GetAffinDecompose(double m[6] 
						,double &A ,double &B, double &Tx ,double &Ty ,double &S ,double &R);

#endif