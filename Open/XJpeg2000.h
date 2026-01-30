/*
 * Copyright (C) 2016
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

#if	!defined(XJPEG2000_H)
#define	XJPEG2000_H


extern	"C"
{

struct	ConvertJpeg2000RawStruct
{
	int 		XLen;
	int 		YLen;
	unsigned char *RawData;
	int			RawDataByte;
	int			AllocatedRawDataByte;
};

struct	ConvertJpeg2000Struct
{
	int 		XLen;
	int 		YLen;
	unsigned char *Jp2kData;
	int			Jp2kDataByte;
	int			AllocatedJp2kDataByte;
};


bool	ConvertDataToJpeg2000Dim(struct	ConvertJpeg2000RawStruct InpData[]
								,struct	ConvertJpeg2000Struct JpegData[]
								,int DimCount);
/*
	�����̉摜�f�[�^��JPEG2000�ɕϊ�����
	����
		InpData	:	���͂����摜�����z���̃f�[�^�|�C���^
		JpegData:	�i�o�d�f�Q�O�O�O�f�[�^�̊i�[�̈��̔z���|�C���^���Z�b�g������
		DimCount:	�z����(�摜���j
	�ߒl
		�ϊ��ɐ��������ꍇ�Atrue

	�ϊ�����JPEG2000�f�[�^�T�C�Y��OutData��Jp2kDataByte�ɐݒ肷��
*/
bool	ConvertDataFromJpeg2000Dim(	 struct	ConvertJpeg2000Struct JpegData[]
									,struct	ConvertJpeg2000RawStruct RawData[]
									,int DimCount);
/*
	������JPEG2000���猳�摜�f�[�^�ɕϊ�����
	����
		JpegData:	�i�o�d�f�Q�O�O�O�f�[�^�̊i�[�̈��̔z���|�C���^���Z�b�g������
		RawData	:	�o�͂����摜�����z���̃f�[�^�|�C���^
		DimCount:	�z����(�摜���j
	�ߒl
		�ϊ��ɐ��������ꍇ�Atrue
*/

};

#endif

