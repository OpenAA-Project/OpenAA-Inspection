/*
 * Copyright (C) 2021
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

#include <QString>
#include <QByteArray>
#include "NList.h"

class	QSqlDatabase;
#define	CountryListFileName		"CountryList.csv"
#define	LanguageListFileName	"LanguageList.csv"
#define	CurrencyListFileName	"CurrencyList.csv"

#define	CryptoKey		612675099134028634LL
#define CookieKey       "RegSpector1"
#define CartKey         "RegSpectorCart"
#define CookieLanguage  "RegSpectorLanguage"
#define CookieCurrency  "RegSpectorCurrency"
#define CookieSupport   "RegSpectorSupport"

#define	FullPriceCode		1
#define	MonthlyPriceCode	2

bool	InitialRegSpectorDatabase(QSqlDatabase &database);


#define TextClass_CategoryName              1
#define TextClass_CategoryRemark            2
#define TextClass_ApplicationName           10
#define TextClass_ApplicationSubTypeName    11
#define TextClass_ApplicationRemark         12


namespace Ui {
class InputTextInLanguageDialog;
}

class   TextList : public NPList<TextList>
{
public:
    QString CountryCode;
    QString CountryName;
    QString JPCountryStr;
    QString TextStr;
    QString MainCurrencyCode;

    TextList(void){}
    TextList(const TextList &src);

    TextList   &operator=(const TextList &src);
};

class   TextContainer : public NPListPack<TextList>
{
public:
    TextContainer(void);
    TextContainer(const TextContainer &src);

    bool    LoadFromCSV(const QString &FileName=LanguageListFileName);
    TextContainer   &operator=(const TextContainer &src);
    QString     Find(const QString &CountryCode);
    TextList   *FindTextList(const QString &CountryCode);
    QString     FindMainCurrencyCode(const QString &CountryCode);
};

//======================================================================================

class   PriceList : public NPList<PriceList>
{
public:
    QString CurrencyCode;
    QString CurrencyMark;
    QString CurrencyName;
    bool    Head;
    double  PriceValue;

    PriceList(void){    PriceValue=0.0; Head=true;  }
    PriceList(const PriceList &src);

    PriceList   &operator=(const PriceList &src);

    bool    LoadFromDB(const QSqlDatabase &DBase ,int ApplicationAutoCount ,int PriceCode);
    bool    SaveToDB  (const QSqlDatabase &DBase ,int ApplicationAutoCount ,int PriceCode);

    QString MakePriceStr(double priceValue);
};

class   PriceContainer : public NPListPack<PriceList>
{
public:

    PriceContainer(void);
    PriceContainer(const PriceContainer &src);

    PriceContainer   &operator=(const PriceContainer &src);

    double  FindPrice(const QString &CurrencyCode);
    PriceList   *FindPriceList(const QString &CurrencyCode);

    bool    LoadFromDB(const QSqlDatabase &DBase ,int ApplicationAutoCount ,int PriceCode);
    bool    SaveToDB  (const QSqlDatabase &DBase ,int ApplicationAutoCount ,int PriceCode);

    bool    LoadFromCSV(const QString &FileName=CurrencyListFileName);
};

#pragma	pack(push,1)
struct	LicenseKeyStruct
{
	qint32	mtUserAutoCount;
	qint32	LicenseID;
};
#pragma	pack(pop)

QByteArray  ConvDat2YCode(const QByteArray &d);
QByteArray  ConvYCode2Dat(const QByteArray &d);

QByteArray  ConvDat2TxtCode(const QByteArray &d);
QByteArray  ConvTxtCode2Dat(const QByteArray &d);