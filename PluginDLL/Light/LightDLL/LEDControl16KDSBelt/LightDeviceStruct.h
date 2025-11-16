#if	!defined(LightDeviceStruct_H)
#define	LightDeviceStruct_H

#include <QBuffer>
#include <QIODevice>
#include "XTypeDef.h"

#define	MaxCountLEDPattern	16
#define	MaxCountLines   	16
#define MaxBoardCount       10

class	LEDControl16KDSBeltPanel;

class   LightBoard
{
public:
	LEDControl16KDSBeltPanel	*Parent;
    class   __LineInfo
    {
    public:
        uint32    TargetValue[MaxCountLEDPattern];    //Micro ampare
        uint32    CurrentValue;                       //Micro ampare

        __LineInfo(void);
        bool    Save(QIODevice *f);
        bool    Load(QIODevice *f);

    }LineInfo[MaxCountLines];
    int		DipSW;
    bool    AllON;

	LightBoard(void);

	void	SetParent(LEDControl16KDSBeltPanel *p);

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

    bool    SetTestLED(bool b);
    bool    SetAllON(bool b);
    bool    SetCurrentPatternNo(int n);

    bool    GetLightData(int PatternNo);
    bool    SetLightData(int PatternNo);
    bool    GetCurrentValue(void);
private:

};

int  ReadBoardID(int DipSW);
void DummyClock(void);
void WriteRegister(int DipSW ,int Data[] ,int DataLen);
void WriteRegisterData(int Data);
void ReadRegister4Bit(int DipSW ,int Data[] ,int DataLen);
void ReadRegister4Bit(int &Data);


#endif
