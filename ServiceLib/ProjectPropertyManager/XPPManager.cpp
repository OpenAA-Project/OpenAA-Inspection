#include <QFileInfo>
#include "XPPManager.h"
#include "XGeneralFunc.h"
#include <QDomNamedNodeMap>


bool	PropertyList::Save(QIODevice *f)
{
	if(::Save(f,PropertyFolder)==false)
		return false;
	if(::Save(f,TagName)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	return true;
}

bool	PropertyList::Load(QIODevice *f)
{
	if(::Load(f,PropertyFolder)==false)
		return false;
	if(::Load(f,TagName)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	return true;
}

//-----------------------------------------------------

bool	CompileTypeList::Save(QIODevice *f)
{
	if(::Save(f,Name)==false)
		return false;
	if(::Save(f,BuildType)==false)
		return false;
	if(PropertyPack.Save(f)==false)
		return false;
	return true;
}

bool	CompileTypeList::Load(QIODevice *f)
{
	if(::Load(f,Name)==false)
		return false;
	if(::Load(f,BuildType)==false)
		return false;
	if(PropertyPack.Load(f)==false)
		return false;
	return true;
}

//-----------------------------------------------------
ProjectList::~ProjectList(void)
{
	ProjectData.clear();
}
bool	ProjectList::Save(QIODevice *f)
{
	if(::Save(f,Name)==false)
		return false;
	if(::Save(f,ProjectPath)==false)
		return false;
	if(::Save(f,ProjectFileName)==false)
		return false;
	if(TypePack.Save(f)==false)
		return false;
	return true;
}

bool	ProjectList::Load(QIODevice *f)
{
	if(::Load(f,Name)==false)
		return false;
	if(::Load(f,ProjectPath)==false)
		return false;
	if(::Load(f,ProjectFileName)==false)
		return false;
	if(TypePack.Load(f)==false)
		return false;
	return true;
}


bool	ProjectList::LoadProjectFile(const QString &SolutionFolder)
{
	QString	FileName=SolutionFolder+GetSeparator()+ProjectPath+GetSeparator()+ProjectFileName;
	QFile	ProjectFile(FileName);
	if(ProjectFile.open(QFile::ReadOnly | QFile::Text)==false)
		return false;
	QString	ErrorMsg;
	if(ProjectData.setContent(&ProjectFile,&ErrorMsg)==false)
		return false;

	QString	TagProject="Project";
	QDomNodeList domProjectList = ProjectData.elementsByTagName(TagProject);
	if(domProjectList.count()==0)
		return false;
	QDomElement ProjectElement = domProjectList.at(0).toElement();

	QString	TagItemDefinitionGroup="ItemDefinitionGroup";
	QDomNodeList domItemDefinitionGroupList = ProjectElement.elementsByTagName(TagItemDefinitionGroup);

	for(int i=0;i<domItemDefinitionGroupList.count();i++){
		QDomElement ItemDefinitionGroupElement = domItemDefinitionGroupList.at(i).toElement();
		QDomNamedNodeMap attrMap = ItemDefinitionGroupElement.attributes();
		CompileTypeList	*K=NULL;
		for(int j=0;j<attrMap.count();j++){
			QString	s=attrMap.item(j).toAttr().name();
			if(s=="Condition"){
				
				QString	v=attrMap.item(j).toAttr().value();
				QStringList	LList=v.split("==");
				if(LList.count()>=2){
					QString	t=LList[1].remove('\'');
					QStringList	DList=t.split('|');
					if(DList.count()>=2){
						for(CompileTypeList *k=TypePack.GetFirst();k!=NULL;k=k->GetNext()){
							if(k->Name==DList[0] && k->BuildType==DList[1]){
								K=k;
								break;
							}
						}
					}
				}
			}
		}
		if(K!=NULL){
			{
				QString	tTagName="ClCompile";
				QDomNodeList domClCompileList = ItemDefinitionGroupElement.elementsByTagName(tTagName);
				if(domClCompileList.count()==0)
					continue;
				QDomElement ClCompileElement = domClCompileList.at(0).toElement();

				const char *ClTagList[]={"PreprocessorDefinitions"
										,"AdditionalIncludeDirectories"
										,"DebugInformationFormat"
										,"RuntimeLibrary"
										,"TreatWChar_tAsBuiltInType"
										,"SuppressStartupBanner"
										,"WarningLevel"
										,"TreatWarningAsError"
										,"MultiProcessorCompilation"
										,"UseMSVC"
										,"EnableExpandedLineNumberInfo"
										,"Optimization"
										,"InlineFunctionExpansion"
										,"IntrinsicFunctions"
										,"FavorSizeOrSpeed"
										,"EnableFiberSafeOptimizations"
										,"InterproceduralOptimization"
										,"OptimizeForWindowsApplication"
										,"FlushDenormalResultsToZero"
										,"EnableMatrixMultiplyLibraryCall"
										,"LoopUnrolling"
										,"Parallelization"
										,"UseIntelOptimizedHeaders"
										,"UndefinePreprocessorDefinitions"
										,"UndefineAllPreprocessorDefinitions"
										,"IgnoreStandardIncludePath"
										,"PreprocessToFile"
										,"PreprocessSuppressLineNumbers"
										,"PreprocessKeepComments"
										,"ExceptionHandling"
										,"SmallerTypeCheck"
										,"BasicRuntimeChecks"
										,"StructMemberAlignment"
										,"BufferSecurityCheck"
										,"FunctionLevelLinking"
										,"EnableEnhancedInstructionSet"
										,"FloatingPointModel"
										,"UnmaskFloatingPointExceptions"
										,"FloatingPointExpressionEvaluation"
										,"DisableFunctionSplitting"
										,"GenerateAlternateCodePaths"
										,"UseProcessorExtensions"
										,"CheckPointers"
										,"CheckUndimensionedArrays"
										,"CheckDanglingPointers"
										,"DisableLanguageExtensions"
										,"ForceConformanceInForLoopScope"
										,"RuntimeTypeInfo"
										,"DisableCilkKeywords"
										,"DisableIntelLangExtensions"
										,"OpenMP"
										,"C99Support"
										,"Cpp0xSupport"
										,"RecognizeRestrictKeyword"
										,"EnableAnsiAliasing"
										,"PrecompiledHeader"
										,"PrecompiledHeaderFile"
										,"PrecompiledHeaderOutputFile"
										,"AssemblerOutput"
										,"AssemblerListingLocation"
										,"ObjectFileName"
										,"ProgramDataBaseFileName"
										,"BrowseInformation"
										,"BrowseInformationFile"
										,"ErrorLimit"
										,"DisableSpecificDiagnostics"
										,"EmitDiagnosticsToFile"
										,"DiagnosticsFile"
										,"VectorizerDiagnosticLevel"
										,"OptimizationDiagnosticLevel"
										,"EmitOptimizationDiagnosticsToFile"
										,"OptimizationDiagnosticsFile"
										,"OptimizationDiagnosticPhase"
										,"OptimizationDiagnosticRoutine"
										,"LevelOfStaticAnalysis"
										,"ModeOfStaticAnalysis"
										,"AnalyzeFilesIndividually"
										,"TreatEnumerationsAsKnownRanges"
										,"SCResultsDirectory"
										,"AnalyzeIncludeFiles"
										,"EnableGapAnalysis"
										,"EmitGAPDiagnosticsToFile"
										,"GAPDiagnosticsFile"
										,"CompileAs"
										,"DisableSpecificWarnings"
										,"ForcedIncludeFiles"
										,"ShowIncludes"
										,"UseFullPaths"
										,"OmitDefaultLibName"
										,NULL	};

				for(int g=0;ClTagList[g]!=NULL;g++){
					QString	TmpTag=ClTagList[g];
					QDomNodeList domPropertyList = ClCompileElement.elementsByTagName(TmpTag);
					PropertyList	*w=new PropertyList();
					w->PropertyFolder	=tTagName;
					if(domPropertyList.count()==0){
						w->TagName			=TmpTag;
					}
					else{
						QDomNode	domPropertyNode=domPropertyList.item(0);
						QDomElement	domPropertyNodeElement	=domPropertyNode.toElement();
						QString	TagName	=domPropertyNodeElement.tagName();
						wchar_t CDim[10000];
						memset(CDim,0,sizeof(CDim));
						TagName.toWCharArray(CDim);
						w->TagName=QString::fromWCharArray(CDim);
						
						QString	mValue;
						for(QDomNode n = domPropertyNodeElement.firstChild(); !n.isNull(); n = n.nextSibling()){
							QDomText t = n.toText();
							if (!t.isNull()){
								mValue += t.data();
							}
						}
						memset(CDim,0,sizeof(CDim));
						mValue.toWCharArray(CDim);
						w->Data	=QString::fromWCharArray(CDim);
						
					}
					K->PropertyPack.AppendList(w);
				}
			}
			{
				QString	lTagName="Link";
				QDomNodeList domLinkList = ItemDefinitionGroupElement.elementsByTagName(lTagName);
				if(domLinkList.count()==0)
					continue;
				QDomElement LinkElement = domLinkList.at(0).toElement();

				const char *LkTagList[]={"SubSystem"
										,"OutputFile"
										,"AdditionalLibraryDirectories"
										,"GenerateDebugInformation"
										,"AdditionalDependencies"
										,"ShowProgress"
										,"Version"
										,"SuppressStartupBanner"
										,"RegisterOutput"
										,"PerUserRedirection"
										,"LinkStatus"
										,"PreventDllBinding"
										,"TreatLinkerWarningAsErrors"
										,"ForceFileOutput"
										,"CreateHotPatchableImage"
										,"SpecifySectionAttributes"
										,"IgnoreAllDefaultLibraries"
										,"IgnoreSpecificDefaultLibraries"
										,"ModuleDefinitionFile"
										,"AddModuleNamesToAssembly"
										,"EmbedManagedResourceFile"
										,"ForceSymbolReferences"
										,"DelayLoadDLLs"
										,"AssemblyLinkResource"
										,"ManifestFile"
										,"AdditionalManifestDependencies"
										,"EnableUAC"
										,"UACExecutionLevel"
										,"UACUIAccess"
										,"ProgramDatabaseFile"
										,"StripPrivateSymbols"
										,"GenerateMapFile"
										,"MapFileName"
										,"MapExports"
										,"AssemblyDebug"
										,"MinimumRequiredVersion"
										,"HeapReserveSize"
										,"HeapCommitSize"
										,"StackReserveSize"
										,"StackCommitSize"
										,"LargeAddressAware"
										,"TerminalServerAware"
										,"SwapRunFromCD"
										,"SwapRunFromNET"
										,"Driver"
										,"OptimizeReferences"
										,"EnableCOMDATFolding"
										,"FunctionOrder"
										,"InterproceduralOptimization"
										,"WPOAssemblyOutput"
										,"WPOAsmListLocation"
										,"WPOObjectFile"
										,"MidlCommandFile"
										,"IgnoreEmbeddedIDL"
										,"MergedIDLBaseFileName"
										,"TypeLibraryFile"
										,"TypeLibraryResourceID"
										,"EntryPointSymbol"
										,"NoEntryPoint"
										,"SetChecksum"
										,"BaseAddress"
										,"RandomizedBaseAddress"
										,"FixedBaseAddress"
										,"DataExecutionPrevention"
										,"TurnOffAssemblyGeneration"
										,"SupportUnloadOfDelayLoadedDLL"
										,"SupportNobindOfDelayLoadedDLL"
										,"ImportLibrary"
										,"MergeSections"
										,"TargetMachine"
										,"Profile"
										,"CLRThreadAttribute"
										,"CLRImageType"
										,"KeyContainer"
										,"CLRUnmanagedCodeCheck"
										,"SectionAlignment"
										,"CLRSupportLastError"
										,"ImageHasSafeExceptionHandlers"
										,NULL	};
 	 
				for(int g=0;LkTagList[g]!=NULL;g++){
					QString	TmpTag=LkTagList[g];
					QDomNodeList domPropertyList = LinkElement.elementsByTagName(TmpTag);
					PropertyList	*w=new PropertyList();
					w->PropertyFolder	=lTagName;
					if(domPropertyList.count()==0){
						w->TagName			=TmpTag;
					}
					else{
						QDomNode	domPropertyNode=domPropertyList.item(0);
						QDomElement	domPropertyNodeElement	=domPropertyNode.toElement();

						QString	TagName	=domPropertyNodeElement.tagName();
						wchar_t CDim[10000];
						memset(CDim,0,sizeof(CDim));
						TagName.toWCharArray(CDim);
						w->TagName=QString::fromWCharArray(CDim);

						QString	mValue;
						for(QDomNode n = domPropertyNodeElement.firstChild(); !n.isNull(); n = n.nextSibling()){
							QDomText t = n.toText();
							if (!t.isNull())
								mValue += t.data();
						}

						memset(CDim,0,sizeof(CDim));
						mValue.toWCharArray(CDim);
						w->Data	=QString::fromWCharArray(CDim);
					}
					K->PropertyPack.AppendList(w);
				}
			}
		}
	}
	//ProjectData.clear();

	return true;
}

bool	ProjectList::UpdateToFile(const QString &SolutionFolder)
{
	QString	TagProject="Project";
	QDomNodeList domProjectList = ProjectData.elementsByTagName(TagProject);
	if(domProjectList.count()==0)
		return false;
	QDomElement ProjectElement		= domProjectList.item(0).toElement();
	QDomElement oldProjectElement	= ProjectElement;

	QString	TagItemDefinitionGroup="ItemDefinitionGroup";
	QDomNodeList domItemDefinitionGroupList = ProjectElement.elementsByTagName(TagItemDefinitionGroup);

	bool	Changed=false;
	for(CompileTypeList *k=TypePack.GetFirst();k!=NULL;k=k->GetNext()){
		for(PropertyList *p=k->PropertyPack.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->Changed==true){
	
				for(int i=0;i<domItemDefinitionGroupList.count();i++){
					QDomElement ItemDefinitionGroupElement		= domItemDefinitionGroupList.item(i).toElement();
					QDomElement oldItemDefinitionGroupElement	=ItemDefinitionGroupElement;
					QDomNamedNodeMap attrMap = ItemDefinitionGroupElement.attributes();
					CompileTypeList	*K=NULL;
					for(int j=0;j<attrMap.count();j++){
						QString	s=attrMap.item(j).toAttr().name();
						if(s=="Condition"){
				
							QString	v=attrMap.item(j).toAttr().value();
							QStringList	LList=v.split("==");
							if(LList.count()>=2){
								QString	t=LList[1].remove('\'');
								QStringList	DList=t.split('|');
								if(DList.count()>=2){
									if(k->Name==DList[0] && k->BuildType==DList[1]){
										K=k;
										break;
									}
								}
							}
						}
					}
					if(K!=NULL){
						QDomNodeList domClCompileList = ItemDefinitionGroupElement.elementsByTagName(p->PropertyFolder);
						if(domClCompileList.count()!=0){
							QDomElement ClCompileElement = domClCompileList.item(0).toElement();
							QDomElement oldClCompileElement=ClCompileElement;
							QDomNodeList domPropertyList = ClCompileElement.elementsByTagName(p->TagName);
							if(domPropertyList.count()==0 && p->Data.isEmpty()==false){
								QDomElement PropertyElement=ProjectData.createElement (p->TagName);
								QDomText	txt=ProjectData.createTextNode (p->Data);

								QDomNode Ret=PropertyElement.appendChild(txt);
								Ret=ClCompileElement.appendChild(PropertyElement);

								Changed=true;
							}
							else if(domPropertyList.count()!=0){
								if(p->Data.isEmpty()==true){
									while(domPropertyList.count()!=0){
										QDomNode n=domPropertyList.item(0);
										QDomNode Ret=ClCompileElement.removeChild(n);
									}
									Changed=true;
								}
								else{
									QDomNode	domPropertyNode=domPropertyList.item(0);
									QDomElement	domPropertyNodeElement	=domPropertyNode.toElement();

									QDomNodeList domDataList = domPropertyNodeElement.childNodes();
									while(domDataList.count()!=0){
										QDomNode n=domDataList.item(0);
										QDomNode Ret=domPropertyNodeElement.removeChild(n);
									}
									QDomText	txt=ProjectData.createTextNode (p->Data);
									//txt.setData(p->Data);
									QDomNode Ret=domPropertyNodeElement.appendChild(txt);
									Changed=true;
								}
							}
						}
					}
				}
			}
		}
	}
	if(Changed==true){
		QByteArray	A=ProjectData.toByteArray();

		QString	FileName=SolutionFolder+GetSeparator()+ProjectPath+GetSeparator()+ProjectFileName;
		QFile	ProjectFile(FileName);

		if(ProjectFile.open(QFile::WriteOnly | QFile::Text)==false)
			return false;
		ProjectFile.write(A);
	}

	return true;
}

QString	ProjectList::CheckNode(CompileTypeList *k,PropertyList *p)
{
	QString	RetData;

	QString	TagProject="Project";
	QDomNodeList domProjectList = ProjectData.elementsByTagName(TagProject);
	if(domProjectList.count()==0)
		return "";
	QDomElement ProjectElement = domProjectList.at(0).toElement();

	QString	TagItemDefinitionGroup="ItemDefinitionGroup";
	QDomNodeList domItemDefinitionGroupList = ProjectElement.elementsByTagName(TagItemDefinitionGroup);

	for(int i=0;i<domItemDefinitionGroupList.count();i++){
		QDomElement ItemDefinitionGroupElement = domItemDefinitionGroupList.at(i).toElement();
		QDomNamedNodeMap attrMap = ItemDefinitionGroupElement.attributes();
		CompileTypeList	*K=NULL;
		for(int j=0;j<attrMap.count();j++){
			QString	s=attrMap.item(j).toAttr().name();
			if(s=="Condition"){
				
				QString	v=attrMap.item(j).toAttr().value();
				QStringList	LList=v.split("==");
				if(LList.count()>=2){
					QString	t=LList[1].remove('\'');
					QStringList	DList=t.split('|');
					if(DList.count()>=2){
						if(k->Name==DList[0] && k->BuildType==DList[1]){
							K=k;
							break;
						}
					}
				}
			}
		}
		if(K!=NULL){
			QDomNodeList domClCompileList = ItemDefinitionGroupElement.elementsByTagName(p->PropertyFolder);
			if(domClCompileList.count()!=0){
				QDomElement ClCompileElement = domClCompileList.at(0).toElement();
				QDomNodeList domPropertyList = ClCompileElement.elementsByTagName(p->TagName);
				if(domPropertyList.count()!=0){
					QDomNode	domPropertyNode=domPropertyList.item(0);
					QDomElement	domPropertyNodeElement	=domPropertyNode.toElement();

					QString	mValue;
					for(QDomNode n = domPropertyNodeElement.firstChild(); !n.isNull(); n = n.nextSibling()){
						QDomText t = n.toText();
						if (!t.isNull())
							mValue += t.data();
					}
						
					wchar_t CDim[10000];
					memset(CDim,0,sizeof(CDim));
					mValue.toWCharArray(CDim);
					RetData	=QString::fromWCharArray(CDim);
				}
			}
		}
	}

	return RetData;
}
PropertyList *ProjectList::SearchProperty(const QString &CompileTypeName,const QString &CompileTypeBuildType ,const QString &TagFolder ,const QString &PropertyTagName)
{
	for(CompileTypeList *c=TypePack.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Name==CompileTypeName && c->BuildType==CompileTypeBuildType){
			for(PropertyList *p=c->PropertyPack.GetFirst();p!=NULL;p=p->GetNext()){
				if(p->PropertyFolder==TagFolder && p->TagName==PropertyTagName){
					return p;
				}
			}
		}
	}
	return NULL;
}
bool	ProjectList::IsChanged(void)
{
	for(CompileTypeList *c=TypePack.GetFirst();c!=NULL;c=c->GetNext()){
		for(PropertyList *p=c->PropertyPack.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->Changed==true)
				return true;
		}
	}
	return false;
}
//-----------------------------------------------------
bool	Solution::LoadSolutionFile(const QString &filename)
{
	QFileInfo	FInfo(filename);

	SolutionPath	=FInfo.path();
	SolutionFileName=FInfo.fileName();
	ProjectPack.RemoveAll();

	QFile	File(filename);
	if(File.open(QIODevice::ReadOnly)==true){
		while(File.atEnd()==false){
			QString	LStr=File.readLine();
			QStringList	LList=LStr.split(QRegularExpression("(\x20{0,}=\x20{0,})|(\x20{0,},\x20{0,})"));
			if(LList.count()>=4 && LList[0].left(8)=="Project(" && LList[0].contains("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}")==true){
				ProjectList	*k=new ProjectList();
				k->Name=LList[1].remove('\"');
				QString	ProjFileName=LList[2].remove('\"');
				QFileInfo	tInfo(ProjFileName);
				k->ProjectPath		=tInfo.path();
				k->ProjectFileName	=tInfo.fileName();
				QString			s	=LList[3].remove('\"');
				s					=s.remove('\n');
				k->TagName			=s.remove('\r');
				ProjectPack.AppendList(k);
			}
			if(LStr.left(6)=="Global"){
				break;
			}
		}
		while(File.atEnd()==false){
			QString	LStr=File.readLine();
			LStr=LStr.remove(QRegularExpression("\t|\x20|\n"));
			if(LStr.left(16)=="EndGlobalSection")
				break;
		}
		while(File.atEnd()==false){
			QString	LStr=File.readLine();
			LStr=LStr.remove(QRegularExpression("\t|\x20|\n"));
			if(LStr.left(16)=="EndGlobalSection")
				break;
			QStringList	LList=LStr.split(QRegularExpression("\\.|="));
			if(LList.count()>=4){
				QString	TagName=LList[0];
				for(ProjectList *k=ProjectPack.GetFirst();k!=NULL;k=k->GetNext()){
					if(TagName==k->TagName){
						if(LList[2]=="Build"){
							QStringList	GList=LList[LList.count()-1].split('|');
							CompileTypeList	*t=new CompileTypeList();
							t->Name		=GList[0];								//Debug or Release
							t->BuildType=GList[1].remove('\n').remove('\r');	//win32 or x64
							k->TypePack.AppendList(t);
						}
					}
				}
			}
		}
		for(ProjectList *k=ProjectPack.GetFirst();k!=NULL;k=k->GetNext()){
			k->LoadProjectFile(SolutionPath);
		}
		return true;
	}
	return false;
}
bool	Solution::UpdateToFile(void)
{
	bool	Ret=true;
	for(ProjectList *k=ProjectPack.GetFirst();k!=NULL;k=k->GetNext()){
		if(k->UpdateToFile(SolutionPath)==false){
			Ret=false;
		}
	}
	return Ret;
}
void Solution::Test()
{
	int	ProjIndex=11;
	int	TypeIndex=3;

	ProjectList *Proj=ProjectPack[ProjIndex];
	if(Proj==NULL)
		return;
	CompileTypeList *Comp=Proj->TypePack[TypeIndex];
	if(Comp==NULL)
		return;

	QString	TagFolder="ClCompile";
	int	Row=0;
	int	RowIndex=11;
	for(PropertyList *a=Comp->PropertyPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->PropertyFolder==TagFolder){
			if(RowIndex==Row){
				for(ProjectList *p=ProjectPack.GetFirst();p!=NULL;p=p->GetNext()){
					PropertyList *t=p->SearchProperty(Comp->Name,Comp->BuildType ,TagFolder ,a->TagName);
					if(t!=NULL){
						#ifdef _MSC_VER
						_heapchk();
						#endif
						t->Data=a->Data;
					}
				}
				break;
			}
			Row++;
		}
	}
}

