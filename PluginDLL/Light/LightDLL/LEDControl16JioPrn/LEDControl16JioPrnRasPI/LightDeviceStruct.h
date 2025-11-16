#if	!defined(LightDeviceStruct_H)
#define	LightDeviceStruct_H

#include <QBuffer>
#include <QIODevice>
#include "XTypeDef.h"

#define	MaxCountLEDPattern	16
#define	MaxCountLines   	16
#define MaxBoardCount       10

class	LEDControl16JioPanel;
class LEDControl16JioPrnRasPIMain;

class   LightBoard
{
public:
	LEDControl16JioPanel	*Parent;
    class   __LineInfo
    {
    public:
        uint32    TargetValue[MaxCountLines];    //Micro ampare

        __LineInfo(void);
        bool    Save(QIODevice *f);
        bool    Load(QIODevice *f);

    }LineInfo[MaxCountLEDPattern];
    int32   CurrentValue[MaxCountLines];    //Micro ampare

    int		DipSW;
    int     Brd;
    bool    AllON;

	LightBoard(void);

	void	SetParent(LEDControl16JioPanel *p);

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

    bool    SetTestLED(LEDControl16JioPrnRasPIMain *p,bool b);
    bool    SetAllON(LEDControl16JioPrnRasPIMain *p,bool b);
    bool    SetCurrentPatternNo(LEDControl16JioPrnRasPIMain *p,int n);

    bool    GetLightData(LEDControl16JioPrnRasPIMain *p,int PatternNo);
    bool    SetLightData(LEDControl16JioPrnRasPIMain *p,int PatternNo);
    bool    GetCurrentValue(LEDControl16JioPrnRasPIMain *p);
private:

};

#if	!defined(PCMode)


#endif

#endif
