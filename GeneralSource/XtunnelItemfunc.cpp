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

#include "XTypeDef.h"
#include <cmath>
#include "XPointer.h"
#include "XtunnelItemfunc.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include "omp.h"


#if 0
// Sample @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	int	NLoopCount3 = GetArea().GetFLineLen(); // ���؃G���A�������{��

	int XLen = GetDotPerLine();
	int YLen = GetMaxLines();
	BYTE** BmpMas = MakeMatrixBuff(XLen, YLen);
	BYTE** BmpTmp = MakeMatrixBuff(XLen, YLen);
	MatrixBuffClear(BmpMas, 0, XLen, YLen);
	MatrixBuffClear(BmpTmp, 0, XLen, YLen);

	// ���摜�����ƃ������ɃX�g�A
	for (int i = 0; i < NLoopCount3; i++)
	{
		int y = GetArea().GetFLineAbsY(i);

		if ((y < 0) || (GetMaxLines() <= y))
			continue;

		int x1 = GetArea().GetFLineLeftX(i);
		int x2 = GetArea().GetFLineRightX(i);
		BYTE* src = GetTargetBuff().GetY(y);

		for (int x = x1; x < x2; x++)
		{
			BYTE* B = BmpMas[y];
			B[x] = src[x];
		}
	}

	int CrackWidth = 3;
	int CrackCenterValue = 63;
	int	SearchWidthMin = 20;

	LineSearch(BmpMas, BmpTmp, XLen, YLen, CrackWidth, CrackCenterValue, SearchWidthMin);

	// ���ƃ��������P�x���摜�ɃX�g�A
	for (int i = 0; i < NLoopCount3; i++)
	{
		int y = GetArea().GetFLineAbsY(i);

		if ((y < 0) || (GetMaxLines() <= y))
			continue;

		int x1 = GetArea().GetFLineLeftX(i);
		int x2 = GetArea().GetFLineRightX(i);
		BYTE* dst = TmpImage.GetY(y);

		for (int x = x1; x < x2; x++)
		{
			BYTE* B = BmpTmp[y];
			dst[x] = B[x];
		}
	}

	DeleteMatrixBuff(BmpMas, YLen);
	DeleteMatrixBuff(BmpTmp, YLen);
	return true;

// Sample @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif


////////////////////////////////////////////////////////////////////////////////////////
// �֐���
//         LineSearch           : ����256�K���摜�ňÂ����������͂ō����������Ĕ������]
// ����
//         BYTE** BmpMas        : ���摜�|�C���^
//         BYTE** BmpTmp        : ���������摜�i�[�|�C���^
//         int XLen             : ����
//         int YLen             : �c��
//         int CrackWidth       : ����������
//         int CrackCenterValue : �Â������̋P�x�����l
//         int SearchWidthMin   : �����T�����ŒZ�������؂��̂Ă��ŏ���
////////////////////////////////////////////////////////////////////////////////////////
void LineSearch(BYTE** BmpMas, BYTE** BmpTmp, int XLen, int YLen, int CrackWidth, int CrackCenterValue, int SearchWidthMin)
{
	// ���摜�̑S�Ẵs�N�Z���ɑ΂��āA�s�N�Z�������̏��񂩂��A�s�N�Z�������������̍\�����̋����f�[�^�쐬
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

			int v_pix, v_temp;
			int up_ct, up_sum, i_tmp, i_cmp, pass_ct;
			double d_tmp;
			BYTE* pix_line;

			int v_len = 8; // 8+1+8=17(17*17�ر) // �P�x���Z�o���`�萔
			int w_hibi = CrackWidth; // �����Ђъ��ꕝ

			for (int x = 0; x < XLen; x++)
			{
				dst[x] = 0;

				if (((v_len - 1) < y) && (y < (YLen - v_len)) && ((v_len - 1) < x) && (x < (XLen - v_len)))
				{
					pix_line = BmpMas[y];
					v_pix = (int)(pix_line[x]);

					up_ct = 0;
					up_sum = 0;
					pass_ct = 0;

					if (CrackCenterValue < v_pix) // 64(����臒l)�ȏ��͂ЂтƂ݂Ȃ��Ȃ�
						continue;

					// ���̏搔���Z�o����
					double ave_rate;

					if (((CrackCenterValue + 1) / 2) > v_pix)
					{
						ave_rate = (double)(v_pix + 1); // 0 ~ 31 : x1 ~ x32(����臒l)
						ave_rate = sqrt(sqrt(sqrt(sqrt(sqrt(ave_rate)))));
					}
					else if (((CrackCenterValue + 1) / 2 - 1) < v_pix)
					{
						ave_rate = (double)((CrackCenterValue + 1) - v_pix); // 32 ~ 63 : x32 ~ x1(����臒l)
						ave_rate = sqrt(sqrt(sqrt(sqrt(sqrt(ave_rate)))));
					}

					// ���`���̋P�x�����Z�o���ĕ��ς̋P�x�������߂�
					for (int ky = ((-1) * v_len); ky < (v_len + 1); ky++)
					{
						BYTE* src = BmpMas[y + ky];

						for (int kx = ((-1) * v_len); kx < (v_len + 1); kx++)
						{
							if ((0 == ky) && (0 == kx))
							{
								++pass_ct; // ���v���Z���O�����Z
								continue;
							}

							i_tmp = (int)(src[x + kx]);

							// ���͂̒P���h�b�g�̋P�x�ɋ����{�����|�����l���Ђъ����P�x���������l��1.5�{�𒴂����Ƃ��́A���Y�P���h�b�g�P�x�������߂Ȃ�
							if (((double)CrackCenterValue + ((double)CrackCenterValue / (double)2)) < ((double)i_tmp * ave_rate))
							{
								++pass_ct; // ���v���Z���O�����Z
								continue;
							}

							i_cmp = w_hibi / 2; // �����؎̂�

							if ((i_cmp >= abs(ky)) && (i_cmp >= abs(kx))) // �Ђт̕��͓����x�����Z�ł���
							{
								if (i_tmp >= v_pix)
								{
									d_tmp = ((double)i_tmp - (double)v_pix) * ave_rate; // ���̋����i�h�b�g�ԁj
									i_tmp = (int)d_tmp;

									if (0.5 <= (d_tmp - (double)i_tmp)) // �l�̌ܓ�
										++i_tmp;

									up_sum += i_tmp; // �P�x�����v�����Z
									++up_ct; // ���v���Z�h�b�g�����Z
								}
								else
								{
									++pass_ct; // ���v���Z���O�����Z
								}
							}
							else
							{
								if (i_tmp > v_pix)
								{
									d_tmp = ((double)i_tmp - (double)v_pix) * ave_rate; // ���̋����i�h�b�g�ԁj
									i_tmp = (int)d_tmp;

									if (0.5 <= (d_tmp - (double)i_tmp)) // �l�̌ܓ�
										++i_tmp;

									up_sum += i_tmp; // �P�x�����v�����Z
									++up_ct; // ���v���Z�h�b�g�����Z
								}
								else
								{
									++pass_ct; // ���v���Z���O�����Z
								}
							}
						}
					}

					v_temp = 0;

					// ���`���̉����Ђъ����̊����̎Z�o
					i_tmp = (v_len + 1) * (v_len + 1) - pass_ct; // 289(v_len:8) - pass_ct

					d_tmp = (double)(w_hibi * (v_len + 1)) / (double)i_tmp;
					d_tmp = ((double)1 - d_tmp) * (double)100; // 82.352941176470588235294117647059(0 == pass_ct)
					d_tmp = (double)i_tmp / (double)100 * d_tmp;

					if (0 < up_ct)
					{
						if (d_tmp < (double)up_ct) // �����Ђъ����̊����ŁA�Ђъ����̎��͂ƍl�������鍷�����߂����̔��r
						{
							v_temp = up_sum / up_ct; // ���ς̋P�x�������߂�
							d_tmp = (double)up_sum / (double)up_ct;

							if (0.5 <= (d_tmp - (double)v_temp)) // �l�̌ܓ�
								++v_temp;

							v_temp *= v_temp; // ����
						}
					}

					if (255 < v_temp)
						v_temp = 255;
					else if (0 > v_temp)
						v_temp = 0;

					dst[x] = (BYTE)v_temp; // �Ђт̐[���𖾓x�Ƃ��āA���邢�قǐ[��
				}
			}
		}
	}


	// ���Ɨ̈��m�ۂ̂��߂O�r�b�g�ڂ𒲐�
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

			for (int x = 0; x < XLen; x++)
				if (0 < (dst[x] & 0x1))
				{
					// 0�r�b�g�ڂ�1�̂Ƃ�1�`7�r�b�g�ڂɉ��Z
					if (254 > dst[x])
						dst[x] += 1;

					dst[x] &= 0xfe;
				}
		}
	}


	// �ЂтƂ͍l�������Ȃ������x�W��(3*3)�s�N�Z�����폜
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

			// ���S�̃h�b�g1�����̋P�x�������r�����ׂē������J�E���g����
			for (int x = 0; x < XLen; x++)
				if ((0 < y) && (y < (YLen - 1)) && (0 < x) && (x < (XLen - 1)))
					if (0 < (dst[x] & 0xfe))
					{
						int ct = 0;

						for (int yy = -1; yy < 2; yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = -1; xx < 2; xx++)
								if ((dst2[x + xx] & 0xfe) == (dst[x] & 0xfe))
									++ct;
						}

						// ���ׂē����P�x���Ȃ狕�񏜋��}�[�L���O������
						if (9 == ct)
							for (int yy = -1; yy < 2; yy++)
							{
								BYTE* dst2 = BmpTmp[y + yy];

								for (int xx = -1; xx < 2; xx++)
									dst2[x + xx] |= 0x1; // �W���}�[�L���O�Y��
							}
					}
		}
	}


	// �ЂтƂ͍l�������Ȃ������x(16>n)�W��(3*3)�s�N�Z�����폜
	for (int y = 0; y < YLen; y++)
	{
		BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

		// ���S��1�h�b�g�����̋P�x����15�����̃h�b�g���J�E���g�����A���񏜋��}�[�L���O���܂܂��Ă����΃J�E���g����
		for (int x = 0; x < XLen; x++)
			if ((0 < y) && (y < (YLen - 1)) && (0 < x) && (x < (XLen - 1)))
				if ((16 > (dst[x] & 0xfe)) || (0 < (dst[x] & 0x1)))
				{
					int ct = 0;

					for (int yy = -1; yy < 2; yy++)
					{
						BYTE* dst2 = BmpTmp[y + yy];

						for (int xx = -1; xx < 2; xx++)
							if ((16 > (dst2[x + xx] & 0xfe)) || (0 < (dst2[x + xx] & 0x1)))
									++ct;
					}

					// �J�E���g��1�h�b�g�����i9�h�b�g�j�Ɠ����Ȃ��Ȃ狕�񏜋��}�[�L���O������
					if (9 == ct)
						for (int yy = -1; yy < 2; yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = -1; xx < 2; xx++)
								dst2[x + xx] |= 0x1; // �W���}�[�L���O�Y��
						}
				}
	}


	// �ЂтƂ͍l�������Ȃ������x(27>n)�W��(3*3)�s�N�Z�����폜
	for (int y = 0; y < YLen; y++)
	{
		BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

		// ���S��1�h�b�g�����̋P�x����15�����̃h�b�g���J�E���g����
		for (int x = 0; x < XLen; x++)
			if ((0 < y) && (y < (YLen - 1)) && (0 < x) && (x < (XLen - 1)))
				if ((0 < (dst[x] & 0xfe)) && (27 > (dst[x] & 0xfe)) && (0 == (dst[x] & 0x1)))
				{
					int ct = 0;

					for (int yy = -1; yy < 2; yy++)
					{
						BYTE* dst2 = BmpTmp[y + yy];

						for (int xx = -1; xx < 2; xx++)
							if ((0 < (dst2[x + xx] & 0xfe)) && (27 > (dst2[x + xx] & 0xfe)) && (0 == (dst2[x + xx] & 0x1)))
								++ct;
					}

					// �J�E���g��1�h�b�g�����i9�h�b�g�j�Ɠ����Ȃ��Ȃ狕�񏜋��}�[�L���O������
					if (9 == ct)
						for (int yy = -1; yy < 2; yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = -1; xx < 2; xx++)
								dst2[x + xx] |= 0x1; // �W���}�[�L���O�Y��
						}
				}
	}


	// �ЂтƂ͍l�������Ȃ������x(+-16)�W��(5*5)�s�N�Z�����폜
	for (int y = 0; y < YLen; y++)
	{
		BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

		// ���S��2�h�b�g�����̋P�x����+-16�����̃h�b�g���J�E���g����
		int ilen_base = 2;

		for (int x = 0; x < XLen; x++)
			if (((ilen_base - 1) < y) && (y < (YLen - ilen_base)) && ((ilen_base - 1) < x) && (x < (XLen - ilen_base)))
				if ((0 < (dst[x] & 0xfe)) && (0 == (dst[x] & 0x1)))
				{
					int ct = 0;

					for (int ilen = 1; ilen < (ilen_base + 1); ilen++)
						for (int yy = (ilen * -1); yy < (ilen + 1); yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = (ilen * -1); xx < (ilen + 1); xx++)
								if ((ilen == abs(yy)) || (ilen == abs(xx))) // �O���̂�
									if ((0 < (dst2[x + xx] & 0xfe)) && (0 == (dst2[x + xx] & 0x1)))
										if ((((dst[x] & 0xfe) - 17) < (dst2[x + xx] & 0xfe)) && ((dst2[x + xx] & 0xfe) < ((dst[x] & 0xfe) + 17)))
											++ct;
						}

					// �J�E���g��2�h�b�g�����i25 - 1�h�b�g�j�Ɠ����Ȃ��Ȃ狕�񏜋��}�[�L���O������
					if (((ilen_base * 2 + 1) * (ilen_base * 2 + 1) - 1) == ct)
						for (int yy = (ilen_base * -1); yy < (ilen_base + 1); yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = (ilen_base * -1); xx < (ilen_base + 1); xx++)
								dst2[x + xx] |= 0x1; // �W���}�[�L���O�Y��
						}
				}
	}


	// �ЂтƂ͍l�������Ȃ������x(+-32)�W��(7*7)�s�N�Z�����폜
	for (int y = 0; y < YLen; y++)
	{
		BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

		// ���S��3�h�b�g�����̋P�x����+-32�����̃h�b�g���J�E���g����
		int ilen_base = 3;

		for (int x = 0; x < XLen; x++)
			if (((ilen_base - 1) < y) && (y < (YLen - ilen_base)) && ((ilen_base - 1) < x) && (x < (XLen - ilen_base)))
				if ((0 < (dst[x] & 0xfe)) && (0 == (dst[x] & 0x1)))
				{
					int ct = 0;

					for (int ilen = 1; ilen < (ilen_base + 1); ilen++)
						for (int yy = (ilen * -1); yy < (ilen + 1); yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = (ilen * -1); xx < (ilen + 1); xx++)
								if ((ilen == abs(yy)) || (ilen == abs(xx))) // �O���̂�
									if ((0 < (dst2[x + xx] & 0xfe)) && (0 == (dst2[x + xx] & 0x1)))
										if ((((dst[x] & 0xfe) - 33) < (dst2[x + xx] & 0xfe)) && ((dst2[x + xx] & 0xfe) < ((dst[x] & 0xfe) + 33)))
											++ct;
						}

					// �J�E���g��3�h�b�g�����i49 - 1�h�b�g�j�Ɠ����Ȃ��Ȃ狕�񏜋��}�[�L���O������
					if (((ilen_base * 2 + 1) * (ilen_base * 2 + 1) - 1) == ct)
						for (int yy = (ilen_base * -1); yy < (ilen_base + 1); yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = (ilen_base * -1); xx < (ilen_base + 1); xx++)
								dst2[x + xx] |= 0x1; // �W���}�[�L���O�Y��
						}
				}
	}


	// �ЂтƂ͍l�������Ȃ��}�[�L���O��1�������폜�i�P�x���摜�𑖍����ă}�[�L���O�̂����h�b�g�̋P�x����0�ɂ����j
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

			for (int x = 0; x < XLen; x++)
				if (0 < (dst[x] & 0x1))
					dst[x] = 0; // �}�[�L���O���폜
		}
	}


	// �Ђі��x���摜���茳�摜���x�����Z�����i���摜�̋��`���ɂЂт̈Â��A�����c���Ă����ȊO�͌��Z�����j
	BYTE** BmpTmp2 = MakeMatrixBuff(XLen, YLen);
	MatrixBuffClear(BmpTmp2, 0, XLen, YLen);

	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			int v_min, s_y, s_x, i_mct, v_pix;

			BYTE* src;
			BYTE* dst = BmpTmp[y];
			BYTE* dst2 = BmpTmp2[y];

			int v_len = 1; // 1+1+1=3(3*3�ر) // ���S���͒T���G���A

			for (int x = 0; x < XLen; x++)
		        if ((v_len < y) && (y < (YLen - v_len)) && (v_len < x) && (x < (XLen - v_len)))
				{
					i_mct = 0;
					v_min = 255;
					s_y = -1 * v_len;
					s_x = -1 * v_len;

					// ���S�̎��͂̒T�����ċP�x��0���̌���0�z�̋P�x���ōŏ��P�x���ƈʒu���T��
					for (int ky = (-1 * v_len); ky < (1 + v_len); ky++)
					{
						src = BmpMas[y + ky];

						for (int kx = (-1 * v_len); kx < (1 + v_len); kx++)
						{
							if ((1 == abs(ky)) || (1 == abs(kx))) // �O���̂�
								if (0 < (int)(dst2[x + kx]))
									++i_mct;

							if ((int)(src[x + kx]) < v_min)
								if (0 < (int)(src[x + kx]))
								{
									s_y = ky;
									s_x = kx;
									v_min = (int)(src[x + kx]);
								}
						}
					}

					bool boo;

					// ���`���Œ��S���P�x�������ԒႢ�ꍇ�ȊO�͍��摜���猳�摜�̒l�����Z����
					if ((0 == s_y) && (0 == s_x) && (v_min == (int)(src[x])))
					{
						if (64 > (int)(src[x]))
							boo = false;
						else
							boo = true;
					}
					else
					{
						// i_mct �̒l���������قǂЂъ����̂悤�ȋP�x���W���̒�
						if ((64 > (int)(src[x])) && (2 > i_mct))
							boo = false;
						else
							boo = true;
					}

					if (true == boo)
					{
						v_pix = (int)(dst[x]) - (int)(src[x]); // ���摜�̋P�x�l����������

						if (255 < v_pix)
							v_pix = 255;
						else if (0 > v_pix)
							v_pix = 0;

						dst2[x] = (BYTE)v_pix; // �P�x�����P�x���摜�ɃX�g�A
					}
				}
		}
	}

	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y];
			BYTE* dst2 = BmpTmp2[y];

			for (int x = 0; x < XLen; x++)
				if (0 < dst2[x])
					dst[x] = dst2[x];
		}
	}

	DeleteMatrixBuff(BmpTmp2, YLen);


	for (int i_loop = 0; i_loop < 2; i_loop++)
	{
		// ���V�P���s�N�Z�����폜
		#pragma omp parallel
		{
			#pragma omp for

			// �P�x���摜�𑖍�
			for (int y = 0; y < YLen; y++)
			{
				BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

				// ���S�̃h�b�g1���肪���ׂċP�x��0�̂Ƃ��Œ��S���P�x��0�z�̂Ƃ������Ƃ��ċP�x��0���ݒ�
				for (int x = 0; x < XLen; x++)
					if ((0 < y) && (y < (YLen - 1)) && (0 < x) && (x < (XLen - 1)))
						if (0 < (dst[x] & 0xfe))
						{
							int ct = 0;

							for (int yy = -1; yy < 2; yy++)
							{
								BYTE* dst2 = BmpTmp[y + yy];

								for (int xx = -1; xx < 2; xx++)
									if ((1 == abs(yy)) || (1 == abs(xx))) // �O���̂�
										if (0 == (dst2[x + xx] & 0xfe))
											++ct; // �P�x�� 0 �̂Ƃ��J�E���g���Z
							}

							// �J�E���g���O�����ׂ�(9 - 1)�P�x��0�̂Ƃ��P�x��0���ݒ�
							if (8 == ct)
								dst[x] = 0;
						}
			}
		}

		// ���V�Q�����s�N�Z�����폜
		#pragma omp parallel
		{
			#pragma omp for

			// �P�x���摜�𑖍�
			for (int y = 0; y < YLen; y++)
			{
				BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

				// ���S�����h�b�g2�����̂Ȃ��Œ��S�ƌ��������h�b�g�������A���S���܂߂�2�h�b�g������
				int ilen_base = 2;

				for (int x = 0; x < XLen; x++)
					if (((ilen_base - 1) < y) && (y < (YLen - ilen_base)) && ((ilen_base - 1) < x) && (x < (XLen - ilen_base)))
						if (0 < (dst[x] & 0xfe))
						{
							int ct[2];

							ct[0] = 0;
							ct[1] = 0;

							for (int ilen = 1; ilen < (ilen_base + 1); ilen++)
								for (int yy = (ilen * -1); yy < (ilen + 1); yy++)
								{
									BYTE* dst2 = BmpTmp[y + yy];

									// �h�b�g�ʎ����̋P�x��0�̃J�E���g������
									for (int xx = (ilen * -1); xx < (ilen + 1); xx++)
										if ((ilen == abs(yy)) || (ilen == abs(xx))) // �O���̂�
											if (0 == (dst2[x + xx] & 0xfe))
												++ct[ilen - 1];
								}

							// ����
							if ((((ilen_base * 2 + 1) * 2) + ((ilen_base * 2 + 1 - 2) * 2)) == ct[1]) // �ŊO���s�N�Z���Ɠ��������H
								if (((((ilen_base - 1) * 2 + 1) * 2) + (((ilen_base - 1) * 2 + 1 - 2) * 2)) <= (ct[0] + 1)) // �œ����s�N�Z���Ɠ���������1���Ȃ����H
									dst[x] = 0; // �P�x��0���ݒ�
						}
			}
		}
	}


	// �P�x���摜�ŒP���̃h�b�g�̘A�����T�����āA�h�b�g�����J�E���g���A�Z�����̂͋����Ƃ��ď������A�A�������s�N�Z���̔����o��
	BmpTmp2 = MakeMatrixBuff(XLen, YLen);

	// �}�[�L���O�̍폜
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

			for (int x = 0; x < XLen; x++)
				if (0 < (dst[x] & 0x1))
					dst[x] &= 0xfe; // �}�[�L���O���폜
		}
	}

	for (int y = 0; y < YLen; y++)
	{
		BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

		for (int x = 0; x < XLen; x++)
			if ((0 < (dst[x] & 0xfe)) && (0 == (dst[x] & 0x1)))
			{
				int ilen_base = 3; // ���`�����萔
				int i_tbl_yx[7][7]; // 3+1+3=7

				// 0 1 2
				// 3 4 5
				// 6 7 8
				int i_tbl_sum[9]; // �����ʖ��x���v��
				int i_tbl_cnt[9]; // �����ʃs�N�Z����

				int i_found = 0;
				int i_xlen, i_ylen, i_xline, i_yline, i_count;
				i_xlen = 0; // ���ʍ��W��x
				i_ylen = 0; // ���ʍ��W��y
				i_xline = 0; // �Ȑ���x
				i_yline = 0; // �Ȑ���y
				i_count = 0; // ������

				int x_2_base = x;
				int y_2_base = y;
				int x_2 = x;
				int y_2 = y;
				bool b_done = false; // �ʘA��������������

				MatrixBuffClear(BmpTmp2, 0, XLen, YLen);

				// 2���T�����[�v�A�T���h�b�g���ړ����ĘA�����J�E���g����
				while (false == b_done)
				{
					bool boo = false;

					// �T���s�N�Z���̍X�V
					BYTE* dst_2 = BmpTmp[y_2];
					BYTE* dst_3 = BmpTmp2[y_2];

					int x_save = 0;
					int y_save = 0;

					// ���͂ɘA�����T��
					if (((ilen_base - 1) < y_2) && (y_2 < (YLen - ilen_base)) && ((ilen_base - 1) < x_2) && (x_2 < (XLen - ilen_base)))
					{
						// �T���h�b�g�𒆐S�̎��͂̃h�b�g�̃e�[�u��������
						// Table Clear
						for (int i_yy = 0; i_yy < 7; i_yy++) // 7:(ilen_base * 2 + 1)
							for (int i_xx = 0; i_xx < 7; i_xx++) // 7:(ilen_base * 2 + 1)
								i_tbl_yx[i_yy][i_xx] = 0;

						// Table Set
						for (int yy = (ilen_base * -1); yy < (ilen_base + 1); yy++)
						{
							BYTE* dst2 = BmpTmp[y_2 + yy];

							for (int xx = (ilen_base * -1); xx < (ilen_base + 1); xx++)
							{
								if ((0 < (dst2[x_2 + xx] & 0xfe)) && (0 == (dst2[x_2 + xx] & 0x1)))
									i_tbl_yx[yy + ilen_base][xx + ilen_base] = dst2[x_2 + xx];

								if ((-2 < yy) && (2 > yy) && (-2 < xx) && (2 > xx)) // �ł��߂��O���̂�
									if (0 < (abs(yy) + abs(xx)))
										if ((0 < (dst2[x_2 + xx] & 0xfe)) && (0x1 == (dst2[x_2 + xx] & 0x1)))
											++i_found;
							}
						}

						// Sum Count Clear
						for (int i_xx = 0; i_xx < 9; i_xx++)
						{
							i_tbl_sum[i_xx] = 0;
							i_tbl_cnt[i_xx] = 0;
						}

						// �T���h�b�g�𒆐S�ɂ���8�����̋����ɕ����A���ꂼ���̋P�x���̍��v�ƋP�x��0�z�̃J�E���g������
						// �����G���A
						i_tbl_sum[0] = i_tbl_yx[0][0]
									 + i_tbl_yx[0][1]
									 + i_tbl_yx[1][0]
									 + i_tbl_yx[1][1]
									 + i_tbl_yx[1][2]
									 + i_tbl_yx[2][1]
									 + i_tbl_yx[2][2];

						i_tbl_cnt[0] = !(!(i_tbl_yx[0][0]))
									 + !(!(i_tbl_yx[0][1]))
									 + !(!(i_tbl_yx[1][0]))
									 + !(!(i_tbl_yx[1][1]))
									 + !(!(i_tbl_yx[1][2]))
									 + !(!(i_tbl_yx[2][1]))
									 + !(!(i_tbl_yx[2][2]));

						// ���G���A
						i_tbl_sum[1] = i_tbl_yx[0][2]
									 + i_tbl_yx[0][3]
									 + i_tbl_yx[0][4]
									 + i_tbl_yx[1][2]
									 + i_tbl_yx[1][3]
									 + i_tbl_yx[1][4]
									 + i_tbl_yx[2][3];

						i_tbl_cnt[1] = !(!(i_tbl_yx[0][2]))
									 + !(!(i_tbl_yx[0][3]))
									 + !(!(i_tbl_yx[0][4]))
									 + !(!(i_tbl_yx[1][2]))
									 + !(!(i_tbl_yx[1][3]))
									 + !(!(i_tbl_yx[1][4]))
									 + !(!(i_tbl_yx[2][3]));

						// �E���G���A
						i_tbl_sum[2] = i_tbl_yx[0][5]
									 + i_tbl_yx[0][6]
									 + i_tbl_yx[1][4]
									 + i_tbl_yx[1][5]
									 + i_tbl_yx[1][6]
									 + i_tbl_yx[2][4]
									 + i_tbl_yx[2][5];

						i_tbl_cnt[2] = !(!(i_tbl_yx[0][5]))
									 + !(!(i_tbl_yx[0][6]))
									 + !(!(i_tbl_yx[1][4]))
									 + !(!(i_tbl_yx[1][5]))
									 + !(!(i_tbl_yx[1][6]))
									 + !(!(i_tbl_yx[2][4]))
									 + !(!(i_tbl_yx[2][5]));

						// ���G���A
						i_tbl_sum[3] = i_tbl_yx[2][0]
									 + i_tbl_yx[2][1]
									 + i_tbl_yx[3][0]
									 + i_tbl_yx[3][1]
									 + i_tbl_yx[3][2]
									 + i_tbl_yx[4][0]
									 + i_tbl_yx[4][1];

						i_tbl_cnt[3] = !(!(i_tbl_yx[2][0]))
									 + !(!(i_tbl_yx[2][1]))
									 + !(!(i_tbl_yx[3][0]))
									 + !(!(i_tbl_yx[3][1]))
									 + !(!(i_tbl_yx[3][2]))
									 + !(!(i_tbl_yx[4][0]))
									 + !(!(i_tbl_yx[4][1]));

						// �E�G���A
						i_tbl_sum[5] = i_tbl_yx[2][5]
									 + i_tbl_yx[2][6]
									 + i_tbl_yx[3][4]
									 + i_tbl_yx[3][5]
									 + i_tbl_yx[3][6]
									 + i_tbl_yx[4][5]
									 + i_tbl_yx[4][6];

						i_tbl_cnt[5] = !(!(i_tbl_yx[2][5]))
									 + !(!(i_tbl_yx[2][6]))
									 + !(!(i_tbl_yx[3][4]))
									 + !(!(i_tbl_yx[3][5]))
									 + !(!(i_tbl_yx[3][6]))
									 + !(!(i_tbl_yx[4][5]))
									 + !(!(i_tbl_yx[4][6]));

						// �����G���A
						i_tbl_sum[6] = i_tbl_yx[4][1]
									 + i_tbl_yx[4][2]
									 + i_tbl_yx[5][0]
									 + i_tbl_yx[5][1]
									 + i_tbl_yx[5][2]
									 + i_tbl_yx[6][0]
									 + i_tbl_yx[6][1];

						i_tbl_cnt[6] = !(!(i_tbl_yx[4][1]))
									 + !(!(i_tbl_yx[4][2]))
									 + !(!(i_tbl_yx[5][0]))
									 + !(!(i_tbl_yx[5][1]))
									 + !(!(i_tbl_yx[5][2]))
									 + !(!(i_tbl_yx[6][0]))
									 + !(!(i_tbl_yx[6][1]));

						// ���G���A
						i_tbl_sum[7] = i_tbl_yx[4][3]
									 + i_tbl_yx[5][2]
									 + i_tbl_yx[5][3]
									 + i_tbl_yx[5][4]
									 + i_tbl_yx[6][2]
									 + i_tbl_yx[6][3]
									 + i_tbl_yx[6][4];

						i_tbl_cnt[7] = !(!(i_tbl_yx[4][3]))
									 + !(!(i_tbl_yx[5][2]))
									 + !(!(i_tbl_yx[5][3]))
									 + !(!(i_tbl_yx[5][4]))
									 + !(!(i_tbl_yx[6][2]))
									 + !(!(i_tbl_yx[6][3]))
									 + !(!(i_tbl_yx[6][4]));

						// �E���G���A
						i_tbl_sum[8] = i_tbl_yx[4][4]
									 + i_tbl_yx[4][5]
									 + i_tbl_yx[5][4]
									 + i_tbl_yx[5][5]
									 + i_tbl_yx[5][6]
									 + i_tbl_yx[6][5]
									 + i_tbl_yx[6][6];

						i_tbl_cnt[8] = !(!(i_tbl_yx[4][4]))
									 + !(!(i_tbl_yx[4][5]))
									 + !(!(i_tbl_yx[5][4]))
									 + !(!(i_tbl_yx[5][5]))
									 + !(!(i_tbl_yx[5][6]))
									 + !(!(i_tbl_yx[6][5]))
									 + !(!(i_tbl_yx[6][6]));

						// �����e�[�u���̂Ђъ����̘A���������ȕ����֒T���h�b�g���ړ�����
						int d_000 = (double)-1, d_111;
						int i_000 = -1;
						int i_res = -1;

						for (int i_xx = 0; i_xx < 9; i_xx++)
							if (0 < i_tbl_cnt[i_xx])
							{
								d_111 = (double)i_tbl_sum[i_xx] / (double)i_tbl_cnt[i_xx];

								if (d_111 > d_000) // ���x���ς��傫������
								{
									i_000 = i_tbl_cnt[i_xx];
									d_000 = d_111;
									i_res = i_xx; // �T���ړ���������
								}
								else if (d_111 == d_000) // ���ς̖��x�������̂Ƃ��́A�J�E���g���傫������
								{
									if (i_tbl_cnt[i_xx] > i_000)
									{
										i_000 = i_tbl_cnt[i_xx];
										d_000 = d_111;
										i_res = i_xx; // �T���ړ���������
									}
								}
							}

						// �������T���ړ������ŁA�A�������h�b�g�Ɉړ����邪�A�h�b�g���A�����Ȃ������ꍇ�̉I���������T��
						if (-1 < i_res)
						{
							x_save = (i_res % 3) - 1;
							y_save = (i_res / 3) - 1;

							int i_ty = y_save + 1 + 2;
							int i_tx = x_save + 1 + 2;

							bool boo2 = true;

							if (1 > i_tbl_yx[i_ty][i_tx])
							{
								boo2 = false;

								for (int i_lp = 0; i_lp < 8; i_lp++)
								{
									if ((2 == i_ty) && (2 == i_tx)) // �����G���A
									{
										i_ty = 3;
										i_tx = 2;

										if (0 < i_tbl_yx[3][2]) // ���G���A
										{
											boo2 = true;
											break;
										}

										i_ty = 2;
										i_tx = 3;

										if (0 < i_tbl_yx[2][3]) // ���G���A
										{
											boo2 = true;
											break;
										}
									}
									else if ((2 == i_ty) && (3 == i_tx)) // ���G���A
									{
										i_ty = 2;
										i_tx = 2;

										if (0 < i_tbl_yx[2][2]) // �����G���A
										{
											boo2 = true;
											break;
										}

										i_ty = 2;
										i_tx = 4;

										if (0 < i_tbl_yx[2][4]) // �E���G���A
										{
											boo2 = true;
											break;
										}
									}
									else if ((2 == i_ty) && (4 == i_tx)) // �E���G���A
									{
										i_ty = 2;
										i_tx = 3;

										if (0 < i_tbl_yx[2][3]) // ���G���A
										{
											boo2 = true;
											break;
										}

										i_ty = 3;
										i_tx = 4;

										if (0 < i_tbl_yx[3][4]) // �E�G���A
										{
											boo2 = true;
											break;
										}
									}
									else if ((3 == i_ty) && (2 == i_tx)) // ���G���A
									{
										i_ty = 4;
										i_tx = 2;

										if (0 < i_tbl_yx[4][2]) // �����G���A
										{
											boo2 = true;
											break;
										}

										i_ty = 2;
										i_tx = 2;

										if (0 < i_tbl_yx[2][2]) // �����G���A
										{
											boo2 = true;
											break;
										}
									}
									else if ((3 == i_ty) && (4 == i_tx)) // �E�G���A
									{
										i_ty = 2;
										i_tx = 4;

										if (0 < i_tbl_yx[2][4]) // �E���G���A
										{
											boo2 = true;
											break;
										}

										i_ty = 4;
										i_tx = 4;

										if (0 < i_tbl_yx[4][4]) // �E���G���A
										{
											boo2 = true;
											break;
										}
									}
									else if ((4 == i_ty) && (2 == i_tx)) // �����G���A
									{
										i_ty = 4;
										i_tx = 3;

										if (0 < i_tbl_yx[4][3]) // ���G���A
										{
											boo2 = true;
											break;
										}

										i_ty = 3;
										i_tx = 2;

										if (0 < i_tbl_yx[3][2]) // ���G���A
										{
											boo2 = true;
											break;
										}
									}
									else if ((4 == i_ty) && (3 == i_tx)) // ���G���A
									{
										i_ty = 4;
										i_tx = 4;

										if (0 < i_tbl_yx[4][4]) // �E���G���A
										{
											boo2 = true;
											break;
										}

										i_ty = 4;
										i_tx = 2;

										if (0 < i_tbl_yx[4][2]) // �����G���A
										{
											boo2 = true;
											break;
										}
									}
									else if ((4 == i_ty) && (4 == i_tx)) // �E���G���A
									{
										i_ty = 3;
										i_tx = 4;

										if (0 < i_tbl_yx[3][4]) // �E�G���A
										{
											boo2 = true;
											break;
										}

										i_ty = 4;
										i_tx = 3;

										if (0 < i_tbl_yx[4][3]) // ���G���A
										{
											boo2 = true;
											break;
										}
									}
								}
							}

							// �T���h�b�g���ړ��ł����Ƃ��ړ�����
							if (true == boo2)
							{
								x_save = i_tx - 1 - 2;
								y_save = i_ty - 1 - 2;

								// �\�������}�[�L���O
								dst_3[x_2] = dst_2[x_2]; // �����}�[�L���O
								dst_2[x_2] = 0;
								boo = true;
							}
						}
					}

					// �\�������̒����ƕ��Ǝ֍s���J�E���g����
					if (true == boo)
					{
						x_2 += x_save;
						y_2 += y_save;

						if (abs(x_2_base - x_2) > i_xlen)
							i_xlen = abs(x_2_base - x_2); // ���ʍ��W��x

						if (abs(y_2_base - y_2) > i_ylen)
							i_ylen = abs(y_2_base - y_2); // ���ʍ��W��y

						if (0 != x_save)
							++i_xline; // �Ȑ���x

						if (0 != y_save)
							++i_yline; // �Ȑ���y

						++i_count; // ������
					}

					if (false == boo)
						b_done = true; // ���̒T���h�b�g���������Ȃ������Ƃ��ɂ�2�����[�v���I������
				}

				// �J�n�h�b�g���P�݂̂ŘA�����Ȃ��Ƃ��A�h�b�g���P�x��0�ɂ��ď���
				if (1 > i_count)
				{
					if (0 == i_found)
						dst[x_2] = 0;

					continue; // ������ 0
				}

				b_done = false;

				// �A�������̂Ђє���
				// �h�b�g�̘A���J�E���g��6�����̂Ƃ��͋����Ƃ��ď���
//				if (120 <= i_count)
//				if (60 <= i_count)
//				if (6 <= i_count)

				if (SearchWidthMin <= i_count)
					b_done = true; // �A���J�E���g�łЂъ����Ɣ���

				if (true == b_done) // ���������͂Ђъ����H
				{
					#pragma omp parallel
					{
						#pragma omp for

						// �T���}�[�L���O���Ђъ����}�[�L���O�Ɋm��
						for (int y_t = 0; y_t < YLen; y_t++)
						{
							BYTE* dst_t = BmpTmp[y_t]; // ���Ɨ̈��ł̉������������ʒu
							BYTE* dst_t2 = BmpTmp2[y_t]; // ���Ɨ̈��ł̉������������ʒu

							for (int x_t = 0; x_t < XLen; x_t++)
								if (0 < dst_t2[x_t])
								{
									dst_t[x_t] = dst_t2[x_t];
									dst_t[x_t] |= 0x1; // �m���}�[�L���O
								}
						}
					}
				}
			}
	}

	DeleteMatrixBuff(BmpTmp2, YLen);

	// �}�[�L���O�̍폜
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // ���Ɨ̈��ł̉������������ʒu

			for (int x = 0; x < XLen; x++)
				if (0 < (dst[x] & 0x1))
					dst[x] &= 0xfe; // �}�[�L���O���폜
		}
	}
}