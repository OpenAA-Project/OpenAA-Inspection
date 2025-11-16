/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinellib\Sentinellib\Sentinellib.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <windows.h>
#include "spromeps.h"
#include "sentinellib.h"
#include "sentinel_PnDid.h"

Sentinellib::Sentinellib()
{
	IsInitialized = 0;
	ApiPacket = &ApiPack;
	bFirstSession = false;
	ReadArray.clear();
}

Sentinellib::~Sentinellib()
{
}

bool Sentinellib::SentinelLogin()
{
	if (0 < IsInitialized)
		return true;

    SP_STATUS status;

	status = RNBOsproFormatPacket(ApiPacket, sizeof(ApiPack));

	if (SP_SUCCESS != status)
		return false;

	status = RNBOsproInitialize(ApiPacket);

	if (SP_SUCCESS != status)
		return false;

	return true;
}

bool Sentinellib::Session()
{
	SP_STATUS status;

	if (false == bFirstSession)
	{
		status = RNBOsproFindFirstUnit(ApiPacket, DeveloperID);

		if (SP_SUCCESS != status)
			return false;

		bFirstSession = true;
	}
	else
	{
		status = RNBOsproFindNextUnit(ApiPacket);

		if (SP_SUCCESS != status)
			return false;
	}

	return true;
}

bool Sentinellib::ReadSentinel()
{
	RB_WORD rData;
	RB_BYTE rAccessCode;
	SP_STATUS status;

	for (int ict = 0; ict < 56; ict++)
		MemCell[ict] = 0;

	int isum = 0;

	for (int ict = 8; ict < 64; ict++)
	{
		status = RNBOsproExtendedRead(ApiPacket, (RB_WORD)ict, &rData, &rAccessCode);

		if (SP_SUCCESS != status)
		{
			if (0 < isum)
				break;

			return false;
		}

		MemCell[ict - 8] = rData;
		++isum;
	}

	for (int ict = 0; ict < 56; ict++)
	{
		if (0 == MemCell[ict])
			continue;

		unsigned char uctmp;
		int itmp;

		itmp = (MemCell[ict] ^ DeveloperID) & 0xffff; // •œ†
		uctmp = (itmp >> 8) & 0xff;
		ReadArray.append(uctmp);
		uctmp = itmp & 0xff;
		ReadArray.append(uctmp);
	}

	return true;
}

void Sentinellib::Return(QStringList &RetData)
{
	int imax = ReadArray.size();
	imax /= 16;

	for (int ict = 0; ict < imax; ict++)
	{
		RetData.append(ReadArray.mid(ict * 16 + 8, 8));
		RetData.append(ReadArray.mid(ict * 16, 8));
	}
}

bool Sentinellib::SentinelExecute(QStringList &Ret)
{
	if (true == SentinelLogin())
		while (true == Session())
			if (false == ReadSentinel())
				return false;

	if (false == bFirstSession)
		return false;

	if (0 == ReadArray.size())
	{
		Ret.append(/**/"");
		return false;
	}

	Return(Ret);
	return true;
}
