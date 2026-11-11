#pragma once
#include <vector>

class CubicSpline1D {
private:

    struct Point {
        double x, y;
        bool operator<(const Point& other) const { return x < other.x; }
    };

    std::vector<double> x_vals;
    // S(x) = a + b(x-xi) + c(x-xi)^2 + d(x-xi)^3
    std::vector<double> a, b, c, d;

public:
    CubicSpline1D(const std::vector<double>& x, const std::vector<double>& y);

    // ”CˆÓ‚Ì x ‚É‘Î‚·‚é y ‚Ì•âŠÔ’l‚ğŒvZ‚·‚éŠÖ”
    double interpolate(double target_x) const;
};
