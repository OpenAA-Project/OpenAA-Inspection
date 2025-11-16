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

	int	NLoopCount3 = GetArea().GetFLineLen(); // 検証エリア横走査本数

	int XLen = GetDotPerLine();
	int YLen = GetMaxLines();
	BYTE** BmpMas = MakeMatrixBuff(XLen, YLen);
	BYTE** BmpTmp = MakeMatrixBuff(XLen, YLen);
	MatrixBuffClear(BmpMas, 0, XLen, YLen);
	MatrixBuffClear(BmpTmp, 0, XLen, YLen);

	// 元画像を作業メモリにストア
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

	// 作業メモリを輝度差画像にストア
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
// 関数名
//         LineSearch           : 白黒256階調画像で暗い線状を周囲で差分強調して白黒反転
// 引数
//         BYTE** BmpMas        : 元画像ポインタ
//         BYTE** BmpTmp        : 生成差分画像格納ポインタ
//         int XLen             : 横幅
//         int YLen             : 縦幅
//         int CrackWidth       : 仮定線状幅
//         int CrackCenterValue : 暗い線状の輝度上限値
//         int SearchWidthMin   : 線状探索時で短線分を切り捨てる最小長
////////////////////////////////////////////////////////////////////////////////////////
void LineSearch(BYTE** BmpMas, BYTE** BmpTmp, int XLen, int YLen, int CrackWidth, int CrackCenterValue, int SearchWidthMin)
{
	// 元画像の全てのピクセルに対して、ピクセル周りの情報から、ピクセルが黒い線状の構成時の強調データ作成
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

			int v_pix, v_temp;
			int up_ct, up_sum, i_tmp, i_cmp, pass_ct;
			double d_tmp;
			BYTE* pix_line;

			int v_len = 8; // 8+1+8=17(17*17ｴﾘｱ) // 輝度差算出矩形定数
			int w_hibi = CrackWidth; // 仮定ひび割れ幅

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

					if (CrackCenterValue < v_pix) // 64(初期閾値)以上はひびとみなさない
						continue;

					// 差の乗数を算出する
					double ave_rate;

					if (((CrackCenterValue + 1) / 2) > v_pix)
					{
						ave_rate = (double)(v_pix + 1); // 0 ~ 31 : x1 ~ x32(初期閾値)
						ave_rate = sqrt(sqrt(sqrt(sqrt(sqrt(ave_rate)))));
					}
					else if (((CrackCenterValue + 1) / 2 - 1) < v_pix)
					{
						ave_rate = (double)((CrackCenterValue + 1) - v_pix); // 32 ~ 63 : x32 ~ x1(初期閾値)
						ave_rate = sqrt(sqrt(sqrt(sqrt(sqrt(ave_rate)))));
					}

					// 矩形内の輝度差を算出して平均の輝度差を求める
					for (int ky = ((-1) * v_len); ky < (v_len + 1); ky++)
					{
						BYTE* src = BmpMas[y + ky];

						for (int kx = ((-1) * v_len); kx < (v_len + 1); kx++)
						{
							if ((0 == ky) && (0 == kx))
							{
								++pass_ct; // 合計加算除外数加算
								continue;
							}

							i_tmp = (int)(src[x + kx]);

							// 周囲の単一ドットの輝度に強調倍率を掛けた値がひび割れ輝度仮定上限値の1.5倍を超えるときは、当該単一ドット輝度差を求めない
							if (((double)CrackCenterValue + ((double)CrackCenterValue / (double)2)) < ((double)i_tmp * ave_rate))
							{
								++pass_ct; // 合計加算除外数加算
								continue;
							}

							i_cmp = w_hibi / 2; // 少数切捨て

							if ((i_cmp >= abs(ky)) && (i_cmp >= abs(kx))) // ひびの幅は同明度を加算できる
							{
								if (i_tmp >= v_pix)
								{
									d_tmp = ((double)i_tmp - (double)v_pix) * ave_rate; // 差の強調（ドット間）
									i_tmp = (int)d_tmp;

									if (0.5 <= (d_tmp - (double)i_tmp)) // 四捨五入
										++i_tmp;

									up_sum += i_tmp; // 輝度差合計数加算
									++up_ct; // 合計加算ドット数加算
								}
								else
								{
									++pass_ct; // 合計加算除外数加算
								}
							}
							else
							{
								if (i_tmp > v_pix)
								{
									d_tmp = ((double)i_tmp - (double)v_pix) * ave_rate; // 差の強調（ドット間）
									i_tmp = (int)d_tmp;

									if (0.5 <= (d_tmp - (double)i_tmp)) // 四捨五入
										++i_tmp;

									up_sum += i_tmp; // 輝度差合計数加算
									++up_ct; // 合計加算ドット数加算
								}
								else
								{
									++pass_ct; // 合計加算除外数加算
								}
							}
						}
					}

					v_temp = 0;

					// 矩形内の仮定ひび割れの割合の算出
					i_tmp = (v_len + 1) * (v_len + 1) - pass_ct; // 289(v_len:8) - pass_ct

					d_tmp = (double)(w_hibi * (v_len + 1)) / (double)i_tmp;
					d_tmp = ((double)1 - d_tmp) * (double)100; // 82.352941176470588235294117647059(0 == pass_ct)
					d_tmp = (double)i_tmp / (double)100 * d_tmp;

					if (0 < up_ct)
					{
						if (d_tmp < (double)up_ct) // 仮定ひび割れの割合で、ひび割れの周囲と考えられる差を求めた数の比較
						{
							v_temp = up_sum / up_ct; // 平均の輝度差を求める
							d_tmp = (double)up_sum / (double)up_ct;

							if (0.5 <= (d_tmp - (double)v_temp)) // 四捨五入
								++v_temp;

							v_temp *= v_temp; // 強調
						}
					}

					if (255 < v_temp)
						v_temp = 255;
					else if (0 > v_temp)
						v_temp = 0;

					dst[x] = (BYTE)v_temp; // ひびの深さを明度として、明るいほど深い
				}
			}
		}
	}


	// 作業領域確保のため０ビット目を調整
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

			for (int x = 0; x < XLen; x++)
				if (0 < (dst[x] & 0x1))
				{
					// 0ビット目が1のとき1～7ビット目に加算
					if (254 > dst[x])
						dst[x] += 1;

					dst[x] &= 0xfe;
				}
		}
	}


	// ひびとは考えられない同明度集合(3*3)ピクセルを削除
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

			// 中心のドット1周りの輝度差を比較しすべて同じかカウントする
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

						// すべて同じ輝度差なら虚報除去マーキングをつける
						if (9 == ct)
							for (int yy = -1; yy < 2; yy++)
							{
								BYTE* dst2 = BmpTmp[y + yy];

								for (int xx = -1; xx < 2; xx++)
									dst2[x + xx] |= 0x1; // 集合マーキング添加
							}
					}
		}
	}


	// ひびとは考えられない同明度(16>n)集合(3*3)ピクセルを削除
	for (int y = 0; y < YLen; y++)
	{
		BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

		// 中心の1ドット周りの輝度差が15未満のドットをカウントする、虚報除去マーキングも含まれていればカウントする
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

					// カウントが1ドット周り（9ドット）と同じならなら虚報除去マーキングをつける
					if (9 == ct)
						for (int yy = -1; yy < 2; yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = -1; xx < 2; xx++)
								dst2[x + xx] |= 0x1; // 集合マーキング添加
						}
				}
	}


	// ひびとは考えられない同明度(27>n)集合(3*3)ピクセルを削除
	for (int y = 0; y < YLen; y++)
	{
		BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

		// 中心の1ドット周りの輝度差が15未満のドットをカウントする
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

					// カウントが1ドット周り（9ドット）と同じならなら虚報除去マーキングをつける
					if (9 == ct)
						for (int yy = -1; yy < 2; yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = -1; xx < 2; xx++)
								dst2[x + xx] |= 0x1; // 集合マーキング添加
						}
				}
	}


	// ひびとは考えられない同明度(+-16)集合(5*5)ピクセルを削除
	for (int y = 0; y < YLen; y++)
	{
		BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

		// 中心の2ドット周りの輝度差が+-16未満のドットをカウントする
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
								if ((ilen == abs(yy)) || (ilen == abs(xx))) // 外周のみ
									if ((0 < (dst2[x + xx] & 0xfe)) && (0 == (dst2[x + xx] & 0x1)))
										if ((((dst[x] & 0xfe) - 17) < (dst2[x + xx] & 0xfe)) && ((dst2[x + xx] & 0xfe) < ((dst[x] & 0xfe) + 17)))
											++ct;
						}

					// カウントが2ドット周り（25 - 1ドット）と同じならなら虚報除去マーキングをつける
					if (((ilen_base * 2 + 1) * (ilen_base * 2 + 1) - 1) == ct)
						for (int yy = (ilen_base * -1); yy < (ilen_base + 1); yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = (ilen_base * -1); xx < (ilen_base + 1); xx++)
								dst2[x + xx] |= 0x1; // 集合マーキング添加
						}
				}
	}


	// ひびとは考えられない同明度(+-32)集合(7*7)ピクセルを削除
	for (int y = 0; y < YLen; y++)
	{
		BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

		// 中心の3ドット周りの輝度差が+-32未満のドットをカウントする
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
								if ((ilen == abs(yy)) || (ilen == abs(xx))) // 外周のみ
									if ((0 < (dst2[x + xx] & 0xfe)) && (0 == (dst2[x + xx] & 0x1)))
										if ((((dst[x] & 0xfe) - 33) < (dst2[x + xx] & 0xfe)) && ((dst2[x + xx] & 0xfe) < ((dst[x] & 0xfe) + 33)))
											++ct;
						}

					// カウントが3ドット周り（49 - 1ドット）と同じならなら虚報除去マーキングをつける
					if (((ilen_base * 2 + 1) * (ilen_base * 2 + 1) - 1) == ct)
						for (int yy = (ilen_base * -1); yy < (ilen_base + 1); yy++)
						{
							BYTE* dst2 = BmpTmp[y + yy];

							for (int xx = (ilen_base * -1); xx < (ilen_base + 1); xx++)
								dst2[x + xx] |= 0x1; // 集合マーキング添加
						}
				}
	}


	// ひびとは考えられないマーキングと1周りを削除（輝度差画像を走査してマーキングのあるドットの輝度差を0にする）
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

			for (int x = 0; x < XLen; x++)
				if (0 < (dst[x] & 0x1))
					dst[x] = 0; // マーキングを削除
		}
	}


	// ひび明度差画像より元画像明度を減算する（元画像の矩形内にひびの暗い連続を残してそれ以外は減算する）
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

			int v_len = 1; // 1+1+1=3(3*3ｴﾘｱ) // 中心周囲探査エリア

			for (int x = 0; x < XLen; x++)
		        if ((v_len < y) && (y < (YLen - v_len)) && (v_len < x) && (x < (XLen - v_len)))
				{
					i_mct = 0;
					v_min = 255;
					s_y = -1 * v_len;
					s_x = -1 * v_len;

					// 中心の周囲の探査して輝度差0超の個数と0越の輝度差で最小輝度差と位置を探す
					for (int ky = (-1 * v_len); ky < (1 + v_len); ky++)
					{
						src = BmpMas[y + ky];

						for (int kx = (-1 * v_len); kx < (1 + v_len); kx++)
						{
							if ((1 == abs(ky)) || (1 == abs(kx))) // 外周のみ
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

					// 矩形内で中心が輝度差が一番低い場合以外は差画像から元画像の値を減算する
					if ((0 == s_y) && (0 == s_x) && (v_min == (int)(src[x])))
					{
						if (64 > (int)(src[x]))
							boo = false;
						else
							boo = true;
					}
					else
					{
						// i_mct の値が小さいほどひび割れのような輝度差集合の中
						if ((64 > (int)(src[x])) && (2 > i_mct))
							boo = false;
						else
							boo = true;
					}

					if (true == boo)
					{
						v_pix = (int)(dst[x]) - (int)(src[x]); // 元画像の輝度値を差し引く

						if (255 < v_pix)
							v_pix = 255;
						else if (0 > v_pix)
							v_pix = 0;

						dst2[x] = (BYTE)v_pix; // 輝度差を輝度差画像にストア
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
		// 浮遊単一ピクセルを削除
		#pragma omp parallel
		{
			#pragma omp for

			// 輝度差画像を走査
			for (int y = 0; y < YLen; y++)
			{
				BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

				// 中心のドット1周りがすべて輝度差0のときで中心が輝度差0越のとき虚報として輝度差0を設定
				for (int x = 0; x < XLen; x++)
					if ((0 < y) && (y < (YLen - 1)) && (0 < x) && (x < (XLen - 1)))
						if (0 < (dst[x] & 0xfe))
						{
							int ct = 0;

							for (int yy = -1; yy < 2; yy++)
							{
								BYTE* dst2 = BmpTmp[y + yy];

								for (int xx = -1; xx < 2; xx++)
									if ((1 == abs(yy)) || (1 == abs(xx))) // 外周のみ
										if (0 == (dst2[x + xx] & 0xfe))
											++ct; // 輝度差 0 のときカウント加算
							}

							// カウントが外周すべて(9 - 1)輝度差0のとき輝度差0を設定
							if (8 == ct)
								dst[x] = 0;
						}
			}
		}

		// 浮遊２結合ピクセルを削除
		#pragma omp parallel
		{
			#pragma omp for

			// 輝度差画像を走査
			for (int y = 0; y < YLen; y++)
			{
				BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

				// 中心よりドット2周りのなかで中心と結合したドットがあり、中心を含めて2ドットか判定
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

									// ドット別周回の輝度差0のカウントをする
									for (int xx = (ilen * -1); xx < (ilen + 1); xx++)
										if ((ilen == abs(yy)) || (ilen == abs(xx))) // 外周のみ
											if (0 == (dst2[x + xx] & 0xfe))
												++ct[ilen - 1];
								}

							// 判定
							if ((((ilen_base * 2 + 1) * 2) + ((ilen_base * 2 + 1 - 2) * 2)) == ct[1]) // 最外周ピクセルと同じ数か？
								if (((((ilen_base - 1) * 2 + 1) * 2) + (((ilen_base - 1) * 2 + 1 - 2) * 2)) <= (ct[0] + 1)) // 最内周ピクセルと同じ数又は1つ少ないか？
									dst[x] = 0; // 輝度差0を設定
						}
			}
		}
	}


	// 輝度差画像で単一のドットの連続を探査して、ドット長をカウントし、短いものは虚報として除去し、連続結合ピクセルの抜き出す
	BmpTmp2 = MakeMatrixBuff(XLen, YLen);

	// マーキングの削除
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

			for (int x = 0; x < XLen; x++)
				if (0 < (dst[x] & 0x1))
					dst[x] &= 0xfe; // マーキングを削除
		}
	}

	for (int y = 0; y < YLen; y++)
	{
		BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

		for (int x = 0; x < XLen; x++)
			if ((0 < (dst[x] & 0xfe)) && (0 == (dst[x] & 0x1)))
			{
				int ilen_base = 3; // 矩形幅基定数
				int i_tbl_yx[7][7]; // 3+1+3=7

				// 0 1 2
				// 3 4 5
				// 6 7 8
				int i_tbl_sum[9]; // 方向別明度合計数
				int i_tbl_cnt[9]; // 方向別ピクセル数

				int i_found = 0;
				int i_xlen, i_ylen, i_xline, i_yline, i_count;
				i_xlen = 0; // 平面座標幅x
				i_ylen = 0; // 平面座標幅y
				i_xline = 0; // 曲線性x
				i_yline = 0; // 曲線性y
				i_count = 0; // 結合数

				int x_2_base = x;
				int y_2_base = y;
				int x_2 = x;
				int y_2 = y;
				bool b_done = false; // 個別連続結合検索完了

				MatrixBuffClear(BmpTmp2, 0, XLen, YLen);

				// 2次探査ループ、探査ドットを移動して連続をカウントする
				while (false == b_done)
				{
					bool boo = false;

					// 探索ピクセルの更新
					BYTE* dst_2 = BmpTmp[y_2];
					BYTE* dst_3 = BmpTmp2[y_2];

					int x_save = 0;
					int y_save = 0;

					// 周囲に連続を探す
					if (((ilen_base - 1) < y_2) && (y_2 < (YLen - ilen_base)) && ((ilen_base - 1) < x_2) && (x_2 < (XLen - ilen_base)))
					{
						// 探査ドットを中心の周囲のドットのテーブルを作る
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

								if ((-2 < yy) && (2 > yy) && (-2 < xx) && (2 > xx)) // 最も近い外周のみ
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

						// 探査ドットを中心にして8方向の区域に分け、それぞれの輝度差の合計と輝度差0越のカウントをする
						// 左上エリア
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

						// 上エリア
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

						// 右上エリア
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

						// 左エリア
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

						// 右エリア
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

						// 左下エリア
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

						// 下エリア
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

						// 右下エリア
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

						// 方向テーブルのひび割れの連続しそうな方向へ探査ドットを移動する
						int d_000 = (double)-1, d_111;
						int i_000 = -1;
						int i_res = -1;

						for (int i_xx = 0; i_xx < 9; i_xx++)
							if (0 < i_tbl_cnt[i_xx])
							{
								d_111 = (double)i_tbl_sum[i_xx] / (double)i_tbl_cnt[i_xx];

								if (d_111 > d_000) // 明度平均が大きい方向
								{
									i_000 = i_tbl_cnt[i_xx];
									d_000 = d_111;
									i_res = i_xx; // 探査移動方向あり
								}
								else if (d_111 == d_000) // 平均の明度が同じのときは、カウントが大きい方向
								{
									if (i_tbl_cnt[i_xx] > i_000)
									{
										i_000 = i_tbl_cnt[i_xx];
										d_000 = d_111;
										i_res = i_xx; // 探査移動方向あり
									}
								}
							}

						// 見つけた探査移動方向で、連続するドットに移動するが、ドットが連続しなかった場合の迂回方向を探す
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
									if ((2 == i_ty) && (2 == i_tx)) // 左上エリア
									{
										i_ty = 3;
										i_tx = 2;

										if (0 < i_tbl_yx[3][2]) // 左エリア
										{
											boo2 = true;
											break;
										}

										i_ty = 2;
										i_tx = 3;

										if (0 < i_tbl_yx[2][3]) // 上エリア
										{
											boo2 = true;
											break;
										}
									}
									else if ((2 == i_ty) && (3 == i_tx)) // 上エリア
									{
										i_ty = 2;
										i_tx = 2;

										if (0 < i_tbl_yx[2][2]) // 左上エリア
										{
											boo2 = true;
											break;
										}

										i_ty = 2;
										i_tx = 4;

										if (0 < i_tbl_yx[2][4]) // 右上エリア
										{
											boo2 = true;
											break;
										}
									}
									else if ((2 == i_ty) && (4 == i_tx)) // 右上エリア
									{
										i_ty = 2;
										i_tx = 3;

										if (0 < i_tbl_yx[2][3]) // 上エリア
										{
											boo2 = true;
											break;
										}

										i_ty = 3;
										i_tx = 4;

										if (0 < i_tbl_yx[3][4]) // 右エリア
										{
											boo2 = true;
											break;
										}
									}
									else if ((3 == i_ty) && (2 == i_tx)) // 左エリア
									{
										i_ty = 4;
										i_tx = 2;

										if (0 < i_tbl_yx[4][2]) // 左下エリア
										{
											boo2 = true;
											break;
										}

										i_ty = 2;
										i_tx = 2;

										if (0 < i_tbl_yx[2][2]) // 左上エリア
										{
											boo2 = true;
											break;
										}
									}
									else if ((3 == i_ty) && (4 == i_tx)) // 右エリア
									{
										i_ty = 2;
										i_tx = 4;

										if (0 < i_tbl_yx[2][4]) // 右上エリア
										{
											boo2 = true;
											break;
										}

										i_ty = 4;
										i_tx = 4;

										if (0 < i_tbl_yx[4][4]) // 右下エリア
										{
											boo2 = true;
											break;
										}
									}
									else if ((4 == i_ty) && (2 == i_tx)) // 左下エリア
									{
										i_ty = 4;
										i_tx = 3;

										if (0 < i_tbl_yx[4][3]) // 下エリア
										{
											boo2 = true;
											break;
										}

										i_ty = 3;
										i_tx = 2;

										if (0 < i_tbl_yx[3][2]) // 左エリア
										{
											boo2 = true;
											break;
										}
									}
									else if ((4 == i_ty) && (3 == i_tx)) // 下エリア
									{
										i_ty = 4;
										i_tx = 4;

										if (0 < i_tbl_yx[4][4]) // 右下エリア
										{
											boo2 = true;
											break;
										}

										i_ty = 4;
										i_tx = 2;

										if (0 < i_tbl_yx[4][2]) // 左下エリア
										{
											boo2 = true;
											break;
										}
									}
									else if ((4 == i_ty) && (4 == i_tx)) // 右下エリア
									{
										i_ty = 3;
										i_tx = 4;

										if (0 < i_tbl_yx[3][4]) // 右エリア
										{
											boo2 = true;
											break;
										}

										i_ty = 4;
										i_tx = 3;

										if (0 < i_tbl_yx[4][3]) // 下エリア
										{
											boo2 = true;
											break;
										}
									}
								}
							}

							// 探査ドットが移動できるとき移動する
							if (true == boo2)
							{
								x_save = i_tx - 1 - 2;
								y_save = i_ty - 1 - 2;

								// 構成線分マーキング
								dst_3[x_2] = dst_2[x_2]; // 仮定マーキング
								dst_2[x_2] = 0;
								boo = true;
							}
						}
					}

					// 構成線分の長さと幅と蛇行をカウントする
					if (true == boo)
					{
						x_2 += x_save;
						y_2 += y_save;

						if (abs(x_2_base - x_2) > i_xlen)
							i_xlen = abs(x_2_base - x_2); // 平面座標幅x

						if (abs(y_2_base - y_2) > i_ylen)
							i_ylen = abs(y_2_base - y_2); // 平面座標幅y

						if (0 != x_save)
							++i_xline; // 曲線性x

						if (0 != y_save)
							++i_yline; // 曲線性y

						++i_count; // 結合数
					}

					if (false == boo)
						b_done = true; // 次の探査ドットが見つからなかったときには2次ループを終了する
				}

				// 開始ドットが１つのみで連続しないとき、ドットを輝度差0にして除去
				if (1 > i_count)
				{
					if (0 == i_found)
						dst[x_2] = 0;

					continue; // 結合数 0
				}

				b_done = false;

				// 連続結合のひび判定
				// ドットの連続カウントが6未満のときは虚報として除去
//				if (120 <= i_count)
//				if (60 <= i_count)
//				if (6 <= i_count)

				if (SearchWidthMin <= i_count)
					b_done = true; // 連続カウントでひび割れと判定

				if (true == b_done) // 結合線分はひび割れ？
				{
					#pragma omp parallel
					{
						#pragma omp for

						// 探査マーキングをひび割れマーキングに確定
						for (int y_t = 0; y_t < YLen; y_t++)
						{
							BYTE* dst_t = BmpTmp[y_t]; // 作業領域での横走査メモリ位置
							BYTE* dst_t2 = BmpTmp2[y_t]; // 作業領域での横走査メモリ位置

							for (int x_t = 0; x_t < XLen; x_t++)
								if (0 < dst_t2[x_t])
								{
									dst_t[x_t] = dst_t2[x_t];
									dst_t[x_t] |= 0x1; // 確定マーキング
								}
						}
					}
				}
			}
	}

	DeleteMatrixBuff(BmpTmp2, YLen);

	// マーキングの削除
	#pragma omp parallel
	{
		#pragma omp for

		for (int y = 0; y < YLen; y++)
		{
			BYTE* dst = BmpTmp[y]; // 作業領域での横走査メモリ位置

			for (int x = 0; x < XLen; x++)
				if (0 < (dst[x] & 0x1))
					dst[x] &= 0xfe; // マーキングを削除
		}
	}
}
