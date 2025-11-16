#include <QtGui>
#define	_USE_MATH_DEFINES
#include <math.h>
#include <QString>
#include <QStringList>

#include "mtFrameDraw.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include <QtGlobal>

void	mtFrameDraw::RepaintAll(void)
{
	update();
}

