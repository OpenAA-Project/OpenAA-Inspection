#if	!defined(XAlignmentCommon_h)
#define	XAlignmentCommon_h

class	CmdGetAlignmentAreas : public GUIDirectMessage
{
public:
	FlexAreaPointerContainer	Areas;

	CmdGetAlignmentAreas(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlignmentAreas(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAlignmentSetSearchDot : public GUIDirectMessage
{
public:
	int32	SearchDotX;
	int32	SearchDotY;

	CmdAlignmentSetSearchDot(LayersBase *base):GUIDirectMessage(base){}
	CmdAlignmentSetSearchDot(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
