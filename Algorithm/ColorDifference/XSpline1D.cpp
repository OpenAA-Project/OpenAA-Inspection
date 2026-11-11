#include "XSpline1D.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>


CubicSpline1D::CubicSpline1D(const std::vector<double>& x, const std::vector<double>& y)
{
    if (x.size() != y.size() || x.size() < 3) {
        throw std::invalid_argument("入力配列のサイズが一致しないか、データ点が3つ未満です。");
    }

    size_t n = x.size();

    // Xの昇順になるようにデータをソート（入力がランダムな順序でも対応可能にするため）
    std::vector<Point> pts(n);
    for (size_t i = 0; i < n; ++i) {
        pts[i] = {x[i], y[i]};
    }
    std::sort(pts.begin(), pts.end());

    x_vals.resize(n);
    a.resize(n);
    for (size_t i = 0; i < n; ++i) {
        x_vals[i] = pts[i].x;
        a[i] = pts[i].y; // 係数aはYの値そのもの
    }

    b.resize(n, 0.0);
    c.resize(n, 0.0);
    d.resize(n, 0.0);

    // 各区間の幅 h を計算
    std::vector<double> h(n - 1);
    for (size_t i = 0; i < n - 1; ++i) {
        h[i] = x_vals[i+1] - x_vals[i];
        if (h[i] == 0.0) {
            throw std::invalid_argument("Xの値に重複があります。");
        }
    }

    // 連立方程式の構築（自然スプライン：両端の2階微分を0とする）
    std::vector<double> alpha(n - 1, 0.0);
    for (size_t i = 1; i < n - 1; ++i) {
        alpha[i] = 3.0 / h[i] * (a[i+1] - a[i]) - 3.0 / h[i-1] * (a[i] - a[i-1]);
    }

    std::vector<double> l(n, 1.0), mu(n, 0.0), z(n, 0.0);
    for (size_t i = 1; i < n - 1; ++i) {
        l[i] = 2.0 * (x_vals[i+1] - x_vals[i-1]) - h[i-1] * mu[i-1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i];
    }

    // 後退代入による係数 c, b, d の計算
    for (int i = n - 2; i >= 0; --i) {
        c[i] = z[i] - mu[i] * c[i+1];
        b[i] = (a[i+1] - a[i]) / h[i] - h[i] * (c[i+1] + 2.0 * c[i]) / 3.0;
        d[i] = (c[i+1] - c[i]) / (3.0 * h[i]);
    }
}

// 任意の x に対する y の補間値を計算する関数
double CubicSpline1D::interpolate(double target_x) const
{
    if (x_vals.empty()) return 0.0;
    
    size_t n = x_vals.size();

    // --- 外挿処理（Xが最小値より小さい場合） ---
    // 最初の点 x_0 での傾きはスプライン関数の性質上 b[0] となります。
    if (target_x < x_vals.front()) {
        double dx = target_x - x_vals.front();
        return a.front() + b.front() * dx;
    }

    // --- 外挿処理（Xが最大値より大きい場合） ---
    // 最後の区間（インデックス n-2）における、最後の点（n-1）での接線の傾きを計算します。
    // S'(x) = b + 2cx + 3dx^2
    if (target_x > x_vals.back()) {
        double dx_last = x_vals.back() - x_vals[n - 2];
        double slope = b[n - 2] + 2.0 * c[n - 2] * dx_last + 3.0 * d[n - 2] * dx_last * dx_last;
        
        double dx = target_x - x_vals.back();
        return a.back() + slope * dx;
    }

    // --- 内挿処理（入力範囲内の場合） ---
    // target_x がどの区間に含まれるかを二分探索で探す
    auto it = std::lower_bound(x_vals.begin(), x_vals.end(), target_x);
    int i;
    
    // 境界にぴったり一致する場合のインデックス調整
    if (it == x_vals.begin()) {
        i = 0;
    } else if (it == x_vals.end()) {
        i = n - 2;
    } else {
        i = std::distance(x_vals.begin(), it) - 1;
    }

    // 3次式による補間値の計算
    double dx = target_x - x_vals[i];
    return a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
}

//// --- 実行テスト用 ---
//int main() {
//    // 入力データ (Xi, Yi)
//    std::vector<double> X = {0.0, 1.0, 2.0, 3.0, 4.0};
//    std::vector<double> Y = {0.0, 0.5, 2.0, 1.5, 0.0};
//
//    try {
//        // クラスのインスタンス生成（ここで係数がすべて事前計算される）
//        CubicSpline1D spline(X, Y);
//
//        std::cout << "--- 補間結果 ---" << std::endl;
//        
//        // X = 1.0 のとき（入力値と完全に一致するか確認）
//        std::cout << "X = 1.0 -> Y = " << spline.interpolate(1.0) << " (期待値: 0.5)" << std::endl;
//        
//        // X = 1.5 のとき（中間の滑らかな値を出力）
//        std::cout << "X = 1.5 -> Y = " << spline.interpolate(1.5) << std::endl;
//
//        // 細かくXを変化させて出力してみる
//        std::cout << "\nXを0.5刻みで連続して出力:" << std::endl;
//        for (double x = 0.0; x <= 4.0; x += 0.5) {
//            std::cout << "X = " << x << ", Y = " << spline.interpolate(x) << std::endl;
//        }
//
//    } catch (const std::exception& e) {
//        std::cerr << "エラー: " << e.what() << std::endl;
//    }
//
//    return 0;
//}