#pragma once
#include <QColor>
#include <QString>
#include<QCheckBox>

class RasterFileLayerLine
{
	QCheckBox	*ShownBox;
public:
	int	FileLayerID;
	QString	FileName;
	QColor	Color;

	RasterFileLayerLine(void);
	RasterFileLayerLine(const RasterFileLayerLine &src);

	QColor	GetColor(void)		{	return Color;	}
	void	SetShown(bool b);
	bool	GetShown(void);

	void	StoreFromWindow(void);
	void	ReflectToWindow(void);
	bool	SaveContent(QIODevice *f);
	bool	LoadContent(QIODevice *f);
};

