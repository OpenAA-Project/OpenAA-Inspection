#include "LicenseKey.h"
#include "XHaspDLL.h"

#include "XTypeDef.h"
#include "XDLLType.h"
#include "XGeneralFunc.h"
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QSettings>
#include <QCryptographicHash>
#include <QByteArray>
#include "XDataInLayer.h"
#include "XAuthentication.h"
#include <QCryptographicHash> 
#include "XSimpleCrypt.h"

LicenseKey::LicenseKey(LayersBase *base)
	:ServiceForLayers(base)
{
}

#define	RegistryPath	"HKEY_CURRENT_USER\\SOFTWARE"
#define	RegKey			/**/"ParamKey"
#define	CryptoKey		41267507777778634LL

LicenseKey::~LicenseKey(void)
{
}

bool3	LicenseKey::PermitByDate(const QString &DLLRoot ,const QString &DLLName
								,qint64 SpanSecFromInstall
								,const QString &_CurrentVersion
								,QString &FailMessage
								,int &ErrorCode)
{
	CmdReqLicenseKeyInfo	LCmd(GetLayersBase());
	TransmitDirectly(&LCmd);

	FailMessage	=LCmd.FailMessage;
	ErrorCode	=LCmd.ErrorCode;

	if(LCmd.PassLicense==true){
		if(LCmd.LicenseTimeOK==true){
			return true3;
		}
		else{
			return false3;
		}
	}

	return none3;
}
bool3	LicenseKey::PermitByProgram(const QString &ProgramCode
									,const QString &_CurrentVersion
									,QString &FailMessage
									,int &ErrorCode)
{
	CmdReqLicenseKeyInfo	LCmd(GetLayersBase());
	TransmitDirectly(&LCmd);

	FailMessage=LCmd.FailMessage;
	ErrorCode	=LCmd.ErrorCode;

	if(LCmd.PassLicense==true){
		if(LCmd.LicenseTimeOK==true){
			return true3;
		}
		else{
			return false3;
		}
	}

	return none3;
}
bool3	LicenseKey::PermitByID(const QString &DLLRoot ,const QString &DLLName ,int id
							,const QString &_CurrentVersion
							,QString &FailMessage
							,int &ErrorCode)
{
	return none3;
}
void	LicenseKey::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqLicenseKeyInfo	*CmdReqLicenseKeyInfoVar=dynamic_cast<CmdReqLicenseKeyInfo *>(packet);
	if(CmdReqLicenseKeyInfoVar!=NULL){
		QString	NumberStr=GetLayersBase()->GetApplicationCode();

		QSettings	Settings(RegistryPath, QSettings::NativeFormat);
		QString		GroupName=QString(/**/"Regulus64_")+NumberStr;
		Settings.beginGroup(GroupName);
		qint64 tm64;
		if(Settings.contains(RegKey)==false){
			return;
		}

		{
			QByteArray HashCode=Settings.value(RegKey).toByteArray();
			SimpleCrypt	Crypto(CryptoKey);
			QByteArray Data=Crypto.decryptToByteArray(HashCode) ;
			CmdReqLicenseKeyInfoVar->LicenseKeyStr=Data;
			CmdReqLicenseKeyInfoVar->LoadedOK=true;

			if(Decrypt(CmdReqLicenseKeyInfoVar->LicenseKeyStr
					,CmdReqLicenseKeyInfoVar->decipheredMailAddress
					,CmdReqLicenseKeyInfoVar->decipheredSoftware
					,CmdReqLicenseKeyInfoVar->decipheredLimit
					,CmdReqLicenseKeyInfoVar->LicenseTimeOK
					,CmdReqLicenseKeyInfoVar->FailMessage
					,CmdReqLicenseKeyInfoVar->ErrorCode)==true){

				bool	ok;
				CmdReqLicenseKeyInfoVar->LicensedYear	=CmdReqLicenseKeyInfoVar->decipheredLimit.mid(0,2).toInt(&ok);
				if(ok==false)
					return;
				CmdReqLicenseKeyInfoVar->LicensedMonth	=CmdReqLicenseKeyInfoVar->decipheredLimit.mid(2,2).toInt(&ok);
				if(ok==false)
					return;
				CmdReqLicenseKeyInfoVar->LicensedDay	=CmdReqLicenseKeyInfoVar->decipheredLimit.mid(4,2).toInt(&ok);
				if(ok==false)
					return;

				if(CmdReqLicenseKeyInfoVar->LicenseTimeOK==true){
					CmdReqLicenseKeyInfoVar->PassLicense=true;
				}
			}
		}
		return;
	}
	CmdSetLicenseKeyInfo	*CmdSetLicenseKeyInfoVar=dynamic_cast<CmdSetLicenseKeyInfo *>(packet);
	if(CmdSetLicenseKeyInfoVar!=NULL){
		QString decipheredMailAddress;
		QString decipheredSoftware;
		QString decipheredLimit;
						
		CmdSetLicenseKeyInfoVar->SavedOK=false;
		if(CmdSetLicenseKeyInfoVar->LicenseKeyStr.isEmpty()==false){
			if(Decrypt(CmdSetLicenseKeyInfoVar->LicenseKeyStr
					,decipheredMailAddress
					,decipheredSoftware
					,decipheredLimit
					,CmdSetLicenseKeyInfoVar->PassLicense
					,CmdSetLicenseKeyInfoVar->FailMessage
					,CmdSetLicenseKeyInfoVar->ErrorCode)==true){
				if(decipheredSoftware==QString(/**/"00")){
					CmdSetLicenseKeyInfoVar->SavedOK=true;

					QString	NumberStr=GetLayersBase()->GetApplicationCode();
					QSettings	Settings(RegistryPath, QSettings::NativeFormat);
					QString		GroupName=QString(/**/"Regulus64_")+NumberStr;
					Settings.beginGroup(GroupName);
					//if(Settings.contains(RegKey)==false){
					//	return;
					//}
					SimpleCrypt	Crypto(CryptoKey);

					QByteArray	Data;
					Data.append(CmdSetLicenseKeyInfoVar->LicenseKeyStr.toUtf8());
					QByteArray HashCode=Crypto.encryptToByteArray(Data) ;

					Settings.setValue(RegKey, HashCode);
				}
			}
		}
		else{
			CmdSetLicenseKeyInfoVar->SavedOK=true;

			QString	NumberStr=GetLayersBase()->GetApplicationCode();
			QSettings	Settings(RegistryPath, QSettings::NativeFormat);
			QString		GroupName=QString(/**/"Regulus64_")+NumberStr;
			Settings.beginGroup(GroupName);

			Settings.remove(RegKey);
		}
		return;
	}
}
 QString	LicenseKey::encryption(const QString &plainData)
{

    QString encryptedData; //暗号化後の文字列

    //暗号化
    for (int i = 0; i < plainData.length(); i++) {

        encryptedData += plainData.at(i);
        if (i < 8) continue; //認証コードは暗号化せずにそのまま

        //奇数桁・偶数桁の各合計を計算
        int oddNum = 0;     //奇数桁の合計
        int evenNum = 0;    //偶数桁の合計
        for (int j = 0; j < encryptedData.length(); j++) {
			QString	numstr=encryptedData.at(j);
			bool	ok;
			int		num=numstr.toInt(&ok);
			if(ok==true){
				if ((j + 1) % 2 == 1) oddNum += num;
				else evenNum += num;
			}
        }

        if (encryptedData.length() % 2 == 1) oddNum *= 3;    //奇数桁目のときは奇数桁を3倍
        else evenNum *= 3; //偶数桁目のときは偶数桁を3倍

        //暗号を計算
        encryptedData = encryptedData.mid(0, encryptedData.length() - 1);

        int insertData = 10 - (oddNum + evenNum) % 10;
        if (insertData == 10) insertData = 0;
        encryptedData += QString::number(insertData);
    }

    //チェックデジットを計算（常に偶数桁を3倍）
    encryptedData = checkDigit(encryptedData);

    //4桁ごとにハイフン追加
    QString encryptedDataSep;
    for (int i = 0; i < encryptedData.length(); i++) {
        encryptedDataSep += encryptedData.at(i);
        if (i % 4 == 3 && i < encryptedData.length() - 1){
			encryptedDataSep += '-';
		}
    }

    return encryptedDataSep;
}

QString LicenseKey::checkDigit(const QString &data)
{

    QString encryptedData = data;

    //奇数桁・偶数桁の各合計を計算
    int oddNum = 0;     //奇数桁の合計
    int evenNum = 0;    //偶数桁の合計
    for (int j = 0; j < encryptedData.length(); j++) {
		QString	numstr=encryptedData.at(j);
		bool	ok;
		int		num=numstr.toInt(&ok);
		if(ok==true){
			if ((j + 1) % 2 == 1) oddNum += num;
			else evenNum += num;
		}
    }

    //偶数桁を3倍
    evenNum *= 3;

    //チェックデジットを計算
    int insertData = 10 - (oddNum + evenNum) % 10;
    if (insertData == 10) insertData = 0;
    encryptedData += QString::number(insertData);

    return encryptedData;
}

bool	LicenseKey::Decrypt(const QString &keyRaw
							,QString &decipheredMailAddress
							,QString &decipheredSoftware
							,QString &decipheredLimit
							,bool &LicenseTimeOK
							,QString &FailMessage
							,int &ErrorCode)
{
	//QString	HStr=encryption(/**/"1234-5678-9510-3738-6495-9138-4027-6774-9468-5077-7448-4212-0152-261");

    //ハイフン削除
    QString key;
    for (int i = 0; i < keyRaw.length(); i++) {
        if (keyRaw[i] != '-') key += keyRaw[i];
    }

	QString	decipheredData;
    //復号
    for (int i = 0; i < key.length()-1; i++) {

        //ライセンスキーは復号しない
        if (i < 8) {
            decipheredData += key.at(i);
            continue;
        }

        for (int j = 0; j <= 9; j++) {

            QString testData = key.mid(0, i) + QString::number(j);

            //奇数桁・偶数桁の各合計を計算
            int oddNum = 0;     //奇数桁の合計
            int evenNum = 0;    //偶数桁の合計
            for (int k = 0; k < testData.length(); k++) {
				QString	numstr=testData.at(k);
				bool	ok;
				int		num=numstr.toInt(&ok);
				if(ok==true){
					if (((k + 1) % 2) == 1) oddNum += num;
					else evenNum += num;
				}
				else{
					FailMessage=/**/"数値ではない文字が含まれます";
					ErrorCode=Error_Authentic_InvalidLicenseKey;
					return false;
				}
            }

            if ((testData.length() % 2) == 1) oddNum *= 3;    //奇数桁目のときは奇数桁を3倍
            else evenNum *= 3; //偶数桁目のときは偶数桁を3倍

            //計算
            int check = 10 - (oddNum + evenNum) % 10;
            if (check == 10) check = 0;

			QString	CheckStr=key.at(i);
			bool	ok;
			int		CheckInt=CheckStr.toInt(&ok);
			if(ok==false)
				return false;
            if (check == CheckInt) {
                decipheredData += QString::number(j);
                break;
            }
        }
    }
	//QString	AuthenticationCode=decipheredData.left(8);
	//if(AuthenticationCode!=/**/"12345678"){
	//	FailMessage=/**/"認証コード不一致";
	//	ErrorCode=Error_Authentic_InvalidLicenseKey;
	//	return false;
	//}

	int	IndexCheckDigit=key.length()-1;
	bool	CheckOK=false;
	//for (int j = 0; j <= 9; j++) {
		QString testData = key.mid(0, IndexCheckDigit);// + QString::number(j);

        //奇数桁・偶数桁の各合計を計算
        int oddNum = 0;     //奇数桁の合計
        int evenNum = 0;    //偶数桁の合計
        for (int k = 0; k < testData.length(); k++) {
			QString	numstr=testData.at(k);
			bool	ok;
			int		num=numstr.toInt(&ok);
			if(ok==true){
				if (((k + 1) % 2) == 1) oddNum += num;
				else evenNum += num;
			}
			else{
				FailMessage=/**/"数値ではない文字が含まれます";
				ErrorCode=Error_Authentic_InvalidLicenseKey;
				return false;
			}
        }

        if ((testData.length() % 2) == 1) oddNum *= 3;    //奇数桁目のときは奇数桁を3倍
        else evenNum *= 3; //偶数桁目のときは偶数桁を3倍

        //計算
        int check = 10 - (oddNum + evenNum) % 10;
        if (check == 10) check = 0;

		QString	CheckStr=key.at(IndexCheckDigit);
		bool	ok;
		int		CheckInt=CheckStr.toInt(&ok);
		if(ok==false)
			return false;
        if (check == CheckInt) {
            CheckOK=true;
            //break;
        }
	//}
	if(CheckOK==false){
		FailMessage=/**/"";	//	/**/"チェックが不一致";
		ErrorCode=Error_Authentic_InvalidLicenseKey;
		return false;
	}


    QString	mailAddressAscii = decipheredData.mid(12,decipheredData.length()-12-8);
    QString mailAddress;

    for (int i = 0; i < mailAddressAscii.length(); i += 2) {
		bool	ok;
		int		n=mailAddressAscii.mid(i  ,2).toInt(&ok);
		if(ok==false){
			FailMessage=/**/"正しくない数値が含まれます";
			ErrorCode=Error_Authentic_InvalidLicenseKey;
			return false;
		}
		n+=33;
        mailAddress += QChar(n);
    }

    decipheredMailAddress =  mailAddress;

    decipheredSoftware	= decipheredData.right(8).left(2);
    decipheredLimit		= decipheredData.right(6);

	LicenseTimeOK=false;
	if(decipheredSoftware==/**/"00"){
		bool	ok;
		int	LimitYear=decipheredLimit.mid(0,2).toInt(&ok);
		if(ok==false){
			//FailMessage=/**/"有効期間を読み取れません";
			ErrorCode=Error_Authentic_InvalidTerm;
			return false;
		}
		int	LimitMonth=decipheredLimit.mid(2,2).toInt(&ok);
		if(ok==false){
			//FailMessage=/**/"有効期間を読み取れません";
			ErrorCode=Error_Authentic_InvalidTerm;
			return false;
		}
		if((LimitMonth<1 || 12<LimitMonth) && LimitMonth!=99){
			//FailMessage=/**/"有効期間を読み取れません";
			ErrorCode=Error_Authentic_InvalidTerm;
			return false;
		}
		int	LimitDay=decipheredLimit.mid(4,2).toInt(&ok);
		if(ok==false){
			//FailMessage=/**/"有効期間を読み取れません";
			ErrorCode=Error_Authentic_InvalidTerm;
			return false;
		}
		QDate	LDate;
		if(LDate.setDate(2000+LimitYear, LimitMonth, LimitDay)==false && LimitDay!=99){
			//FailMessage=/**/"有効期間が正しくありません";
			ErrorCode=Error_Authentic_InvalidTerm;
			return false;
		}

		QDateTime	CTime=QDateTime::currentDateTime();
		int		CYear	=CTime.date().year()%100;
		int		CMonth	=CTime.date().month()%100;
		int		CDay	=CTime.date().day()%100;

		if((LimitYear==99 && LimitMonth==99 && LimitDay==99)
		|| ((LimitYear>CYear)
		|| (LimitYear==CYear && (LimitMonth>CMonth || (LimitMonth==CMonth && LimitDay>=CDay))))){
			LicenseTimeOK=true;
		}
		else{
			FailMessage=/**/"ライセンスキーの有効期限が切れています。";
			ErrorCode=Error_Authentic_InvalidTerm;
		}
	}
	else{
		FailMessage=/**/"";		//   /**/"CamPlusのライセンスキーではありません";
		ErrorCode=Error_Authentic_MismatchID;
	}

	return true;
}

//=================================================================================================

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLHaspMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="LicenseKey";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Hasp DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2024.07";
	return true;
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "LicenseKey control DLL";
}

HaspHandleContainer		*_cdecl	DLL_Initial(LayersBase *base,const QString &ParamStr)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	HaspHandleContainer	*H=new HaspHandleContainer();
	LicenseKey	*p=new LicenseKey(base);
	H->AppendList(p);
	return H;
}

bool		_cdecl	DLL_Close(HaspHandleContainer *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	HaspHandleContainer	*H=(HaspHandleContainer *)handle;
	if(H!=NULL){
		delete	H;
	}

	return true;
}
