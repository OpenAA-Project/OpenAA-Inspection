#include "XXRay3D.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"


extern	const	char *sRoot;
extern	const	char *sName;

// 2次元配列を用いるバイラテラルフィルタ関数
void applyBilateralFilter2D(ImageBuffer &srcImage, ImageBuffer &dstImage, 
                            int radius, double sigma_space, double sigma_color) {
    
    // 画像サイズの取得
    int height = srcImage.GetHeight();
    if (height == 0) return;
    int width = srcImage.GetWidth();

    // 出力先画像のメモリを確保し、0で初期化
    dstImage.Set(0,0,width,height);
    
    // 計算速度向上のため、空間距離と色差の重みを事前に計算してテーブル化
    int kernel_size = radius * 2 + 1;
    std::vector<std::vector<double>> space_weight(kernel_size, std::vector<double>(kernel_size));
    for (int dy = -radius; dy <= radius; ++dy) {
        for (int dx = -radius; dx <= radius; ++dx) {
            space_weight[dy + radius][dx + radius] = std::exp(-(dx * dx + dy * dy) / (2.0 * sigma_space * sigma_space));
        }
    }
    
    std::vector<double> color_weight(256);
    for (int i = 0; i < 256; ++i) {
        color_weight[i] = std::exp(-(i * i) / (2.0 * sigma_color * sigma_color));
    }

    // メインのフィルタリング処理
    // OpenMPが有効な場合は並列処理化
    #pragma omp parallel for
    for (int y = 0; y < height; ++y) {
		BYTE *srcLine = srcImage.GetY(y);
		BYTE *dstLine = dstImage.GetY(y);

        for (int x = 0; x < width; ++x) {
            double weight_sum = 0.0;
            double pixel_sum = 0.0;
            
            // 2次元配列 Image[y][x] の形式で中心ピクセルにアクセス
            int center_val = srcLine[x];
            
            for (int dy = -radius; dy <= radius; ++dy) {
                for (int dx = -radius; dx <= radius; ++dx) {
                    // 周辺ピクセルの座標 (画像端の処理は clamp で範囲内に収める)
                    int ny = std::clamp(y + dy, 0, height - 1);
                    int nx = std::clamp(x + dx, 0, width - 1);
                    BYTE *nLine = srcImage.GetY(ny);
                    // 周辺ピクセルにも [ny][nx] でアクセス
                    int neighbor_val = nLine[nx];
                    int color_diff = std::abs(center_val - neighbor_val);
                    
                    // 空間重みと輝度差重みの掛け算
                    double w = space_weight[dy + radius][dx + radius] * color_weight[color_diff];
                    
                    pixel_sum += neighbor_val * w;
                    weight_sum += w;
                }
            }
            // 正規化して出力用2次元配列へ代入
            dstLine[x] = Clipping((int)std::round(pixel_sum / weight_sum),0,255);
        }
    }
}


void	XRay3DInPage::ExeSmooth(ImageBuffer *Img)
{
// パラメータの設定
    int radius = 10;           
    double sigma_space = 10.0; 
    double sigma_color = 30.0;

	ImageBuffer dstImage;
	applyBilateralFilter2D(*Img,dstImage,radius,sigma_space,sigma_color);
	*Img = dstImage; // 結果を元の画像にコピー
}


// エッジ強調（鮮鋭化）フィルタ関数
void applyEdgeEnhancement2D(ImageBuffer &srcImage, ImageBuffer &dstImage) {
    int height = srcImage.GetHeight();
    if (height == 0) return;
    int width = srcImage.GetWidth();

    // 出力画像を0で初期化してメモリ確保
    dstImage.Set(0,0,width,height);

    // 3x3 鮮鋭化カーネル（8近傍）
    // 中央の画素の重みを大きくし、周囲との差分を強調します
    int kernel[3][3] = {
        {-1, -1, -1},
        {-1,  9, -1},
        {-1, -1, -1}
    };

    // 画像の端（1ピクセル）は3x3カーネルがはみ出すため、内側だけループ処理
    #pragma omp parallel for
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int sum = 0;

            // 3x3の畳み込み演算（コンボリューション）
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    // srcImage[y][x] 形式でアクセスし、カーネルの重みを掛ける
					BYTE *nLine = srcImage.GetY(y + ky);
                    sum += nLine[x + kx] * kernel[ky + 1][kx + 1];
                }
            }

            // 計算結果はマイナスや255を超えることがあるため、0〜255の範囲にクランプ(制限)する
            dstImage[y][x] = static_cast<uint8_t>(std::clamp(sum, 0, 255));
        }
    }

    // 画像の端（外周1ピクセル）の処理: 元の画素値をそのままコピーして補完
    for (int y = 0; y < height; ++y) {
		BYTE *srcLine = srcImage.GetY(y);
		BYTE *dstLine = dstImage.GetY(y);
        dstLine[0] = srcLine[0];
        dstLine[width - 1] = srcLine[width - 1];
    }
    for (int x = 0; x < width; ++x) {
        {
            BYTE    *srcLine = srcImage.GetY(0);
            BYTE    *dstLine = dstImage.GetY(0);
            dstLine[x] = srcLine[x];
        }
        {
            BYTE    *srcLine = srcImage.GetY(height - 1);
			BYTE    *dstLine = dstImage.GetY(height - 1);
            dstLine[x] = srcLine[x];
        }
    }
}
void	XRay3DInPage::ExeEmphasize(ImageBuffer *Img)
{
    ImageBuffer dstImage;
    applyEdgeEnhancement2D(*Img, dstImage);
	*Img = dstImage; // 結果を元の画像にコピー
}

double	XRay3DInPage::ExeMatch(ImageBuffer &Src,ImageBuffer &L,int &X,int &Y)
{
    int height = Src.GetHeight();
    if (height == 0) return 0.0;
    int width = Src.GetWidth();
    int templateHeight = L.GetHeight();
    int templateWidth = L.GetWidth();

    double bestScore = -1.0;
    int bestX = 0;
    int bestY = 0;
    // テンプレートマッチングのループ
    for (int y = 0; y <= height - templateHeight; ++y) {
        for (int x = 0; x <= width - templateWidth; ++x) {
            double score = 0.0;
            // テンプレートと画像の重なり部分の類似度を計算
            for (int j = 0; j < templateHeight; ++j) {
                BYTE *srcLine = Src.GetY(y + j);
                BYTE *templateLine = L.GetY(j);
                for (int i = 0; i < templateWidth; ++i) {
                    int diff = srcLine[x + i] - templateLine[i];
                    score += diff * diff; // 二乗誤差
                }
            }
            // 類似度が高い（スコアが低い）場合は更新
            if (bestScore < 0 || score < bestScore) {
                bestScore = score;
                bestX = x;
                bestY = y;
            }
        }
    }
    X = bestX;
    Y = bestY;
	return bestScore;
}