#if	!defined(XNORMAL_H)
#define	XNORMAL_H

#include "XTypeDef.h"
/*
  NormalDistribution : 正規分布
*/
class NormalDistribution
{
  double _mu;  // 平均
  double _var; // 分散

public:

  /*
    コンストラクタ

    double mu : 平均
    double sigma : 標準偏差
  */
  NormalDistribution( double mu, double sigma );

  // 確率変数 a における確率密度を返す
  double operator[]( double x ) const;

  // 区間 (-∞,a] における確率を返す
  double lower_p( double a ) const;

  // 区間 [a,b] における確率を返す
  double p( double a, double b ) const;

  double average() const { return( _mu ); }   // 平均値
  double variance() const { return( _var ); } // 分散
};

double qnorm(double u);
double pnorm(double qn);


#endif
