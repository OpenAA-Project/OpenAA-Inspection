/*
 * Copyright (C) 2025
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

#pragma once

#include "camerafromloadedimages_global.h"
#include <QStringList>
#include "XCameraCommon.h"
#include "XCameraHandle.h"
#include "XServiceForLayers.h"
#include "XMainSchemeMemory.h"

class LoadImageFilesForm;

class	CameraFromLoadedImages :public CameraHandle
{
	LoadImageFilesForm	*Form;
public:
	ImageBufferListContainer	*Images;
	int							PageCount;
	QStringList					ImageFiles;
	int							RPoint;

	CameraFromLoadedImages(LayersBase *Base);
	~CameraFromLoadedImages(void);

    void    ShowSetting(void);
	bool	LoadImages(const QStringList &List);
	bool	LoadPix(QIODevice *f,int N);

	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)	override;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

    void    ResetStrategicNumber();
    void    ResetScanPhaseNumber();
};