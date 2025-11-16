#pragma once

#include "XTypeDef.h"
#include <QIODevice>

class LayersBase;

class MultiLayerColor
{
	int32	LayerCount;
	uint16	*Brightness;
public:
	MultiLayerColor(void);
	MultiLayerColor(LayersBase *Base);
	MultiLayerColor(const MultiLayerColor &src);
	virtual ~MultiLayerColor();

	void	Allocate(int LayerNumb);
	int		GetLayerNumb(void)				const	{	return LayerCount;			}
	uint16	GetBrightness(int layer)		const	{	return Brightness[layer];	}
	void	SetBrightness(int layer ,int c)			{	Brightness[layer]=c;		}

	void	Clear(int c=0);

	MultiLayerColor	&operator=(const MultiLayerColor &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
private:

};
