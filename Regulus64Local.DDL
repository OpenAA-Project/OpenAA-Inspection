/* Extract Database D:/Data/Regulus64.fdb */
CREATE DATABASE 'D:/Data/Regulus64.fdb' user 'sysdba' password 'masterkey' PAGE_SIZE 8192;


/* Table: Inspection Library Type, Owner: SYSDBA */
CREATE TABLE INSPECTLIBTYPE (
        LIBTYPE INTEGER NOT NULL,			/*	Library type		*/
        TYPENAME VARCHAR(32),				/*	Library Type Name	*/
CONSTRAINT INSPECTLIBTYPEPRIMARYKEY1 PRIMARY KEY (LIBTYPE));

/* Table: Inspection Library, Owner: SYSDBA */
CREATE TABLE INSPECTLIB (
		LIBTYPE INTEGER NOT NULL,			/*	Library type		*/
		LIBID INTEGER NOT NULL,				/*	Library ID			*/
		LIBFOLDERID INTEGER NOT NULL,		/*	Library Folder ID	*/
		LIBNAME VARCHAR(32),				/*	Library Name		*/
		LASTWORKER INTEGER,					/*	Last update worker	*/
		LASTUPDATED TIMESTAMP,				/*	Last update daytime	*/
		DATAVERSION INTEGER,				/*	Data Version		*/
		LIBDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,
		ANYDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,
		ADAPTEDLAYERS BLOB SUB_TYPE 0 SEGMENT SIZE 80,
		SOURCEID INTEGER,					/*	source LibID.  No source = -1	*/
		LIBCOLOR BLOB SUB_TYPE 0 SEGMENT SIZE 80,
		LIBCOMMENT BLOB SUB_TYPE 0 SEGMENT SIZE 80,
CONSTRAINT INSPECTLIBPRIMARYKEY1 PRIMARY KEY (LIBTYPE,LIBID));

/* Table: AnyData by each Library, Owner: SYSDBA */
CREATE TABLE ANYDATAINLIB (
		LIBTYPE INTEGER NOT NULL,			/*	Library type	*/
		LIBID INTEGER NOT NULL,				/*	Library ID		*/
		NGTYPEID INTEGER NOT NULL,			/*	NGTYPE ID		*/
		TYPEUNIQUEID INTEGER NOT NULL,		/*	NGTYPE ID		*/
		DATANAME VARCHAR(32),				/*	Data Name		*/
		LASTUPDATED TIMESTAMP,				/*	Last update daytime		*/
		DATAVERSION INTEGER,				/*	Data Version			*/
		NGCOLOR BLOB SUB_TYPE 0 SEGMENT SIZE 80,/*	NGColor				*/
		MARKSHAPE SMALLINT,					/*	NGMark shape			*/
		NEXTWAITINGTIME INTEGER,			/*	Eaiting time for next	*/
		PRIORITY SMALLINT,					/*	Priority				*/
		BLINK SMALLINT,						/*	Blink					*/
		SPECIFIEDDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,
CONSTRAINT ANYDATAINLIBPRIMARYKEY1 PRIMARY KEY (LIBTYPE,LIBID,NGTYPEID));

/* Table: Folder for Library, Owner: SYSDBA */
CREATE TABLE LIBFOLDER (
		LIBFOLDERID INTEGER NOT NULL,		/*	Library Folder ID	*/
		LIBPARENTID INTEGER,				/*	Parent ID			*/
		NUMBERINFOLDER INTEGER,				/*	Number in Folder	*/
		FOLDERNAME VARCHAR(32),				/*	Library Name		*/
		RELATEDMASTERCODE INTEGER,			/*	Related MasterCode	*/
CONSTRAINT LIBFOLDERPRIMARYKEY1 PRIMARY KEY (LIBFOLDERID));

/* Table: Machine Information, Owner: SYSDBA */
CREATE TABLE MACHINE (
		MACHINEID INTEGER NOT NULL,			/*	Machine ID Code		*/
		NETID VARCHAR(15),					/*	IP Address		*/
		NAME VARCHAR(32),					/*	Machine Name		*/
		VERSION VARCHAR(32),				/*	Machine Version		*/
		REMARK VARCHAR(64),					/*	Remark			*/
		OUTLINEOFFSET BLOB SUB_TYPE 0 SEGMENT SIZE 80,	/*	OutlineOffset		*/
CONSTRAINT MACHINEPRIMARYKEY1 PRIMARY KEY (MACHINEID));

/* Table: MASTERDATA, Owner: SYSDBA */
CREATE TABLE MASTERDATA (
	MASTERCODE INTEGER NOT NULL,			/*	ID Code of Master Data		*/
        MACHINEID INTEGER,					/*	Machine Code			*/
        REGTIME TIMESTAMP,					/*	Registered time			*/
        WORKERID INTEGER,					/*	Registered worker		*/
        MASTERNAME VARCHAR(64),				/*	Master Name			*/
        REMARK VARCHAR(64),					/*	Remark				*/
        VERSION INTEGER,					/*	Version of Master Data		*/
        LASTEDITTIME TIMESTAMP,				/*	Last updated time		*/
        CATEGORYID INTEGER,					/*	Category of Master Data		*/
        TOPVIEW BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	256 x 256 Reference Image	*/
        DOTPERLINE INTEGER,					/*	Horizontal dots in page		*/
        MAXLINES INTEGER,					/*	Vertical lines in page		*/
        PAGENUMB INTEGER,					/*	Pages				*/
        LAYERNUMB INTEGER,					/*	Layers				*/
        PHASENUMB INTEGER,					/*	Phase				*/
        GENERALDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	Layer information		*/
        SETTINGDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	Setting data(ParamGlobal ,ParamComm)	*/
	 MASTERTYPE SMALLINT,					/*	0:Normal data 1:Piece data		*/
        LIGHTDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,	/*	Light data		*/
	 RELATIONCODE	INTEGER,				/*	Relation index	*/
        RELATIONID 	INTEGER,				/*	ID in Relation	*/
        GENERALSTOCKER BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	GeneralStocker information		*/
        RESULTANALIZER BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	ResultAnalizerItemBaseContainer information		*/
        LIBFOLDERID 	INTEGER,			/*	LibFolderID	*/
        THRESHOLDLEVELID INTEGER,			/*	ThresholdLevelID of Master Data			*/
        THRESHOLDLEVELPARENTID INTEGER,		/*	ThresholdLevelParentID of Master Data	*/
CONSTRAINT MASTERDATAPRIMARYKEY1 PRIMARY KEY (MASTERCODE));

/* Table: MASTERRELATION, Owner: SYSDBA */
CREATE TABLE MASTERRELATION (
	 RELATIONCODE INTEGER NOT NULL,			/*	ID Code of Relation		*/
        REGTIME TIMESTAMP,					/*	Registered time			*/
        RELATIONNAME VARCHAR(64),				/*	Relation Name			*/
        RELATIONNUMBER VARCHAR(64),				/*	Relation Number			*/
        REMARK VARCHAR(64),					/*	Remark				*/
        VERSION INTEGER,					/*	Version of Master Data		*/
		RELATIONTYPE SMALLINT,				/*			*/
        COMMONDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	Common data for all relations		*/
        THRESHOLDLEVELID INTEGER,			/*	ThresholdLevelID of Master Data			*/
        LASTLOADEDTIME TIMESTAMP,					/*	Last loaded time			*/
CONSTRAINT MASTERRELATIONPRIMARYKEY1 PRIMARY KEY (RELATIONCODE));

/* Table: MASTERPAGE, Owner: SYSDBA */
CREATE TABLE MASTERPAGE (
	MASTERCODE INTEGER NOT NULL,			/*	ID Code of Master Data		*/
	PAGECODE INTEGER NOT NULL,				/*	PAGE number in Global Master Data		*/
        VERSION INTEGER,					/*	Version of Master Data		*/
        DOTPERLINE INTEGER,					/*	Horizontal dots in page		*/
        MAXLINES INTEGER,					/*	Vertical lines in page		*/
        LAYERNUMB INTEGER,					/*	Layers				*/
        SETTINGDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	Setting data(ParamGlobal ,ParamComm)	*/
        GENERALDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	Layer ,OutlineOffset information		*/
        MASTERIMAGE BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	Master Image			*/
CONSTRAINT MASTERPAGEPRIMARYKEY1 PRIMARY KEY (MASTERCODE,PAGECODE));


/* Table: Master Category data, Owner: SYSDBA */
CREATE TABLE MASTERCATEGORY (
	CATEGORYID INTEGER NOT NULL,			/*	Category ID			*/
        PARENTID INTEGER,					/*	Parent ID 	Root=0		*/
	/*NUMBERINFOLDER INTEGER,*/				/*	Number in Folder		*/
        FOLDERNAME VARCHAR(64),				/*	Category Name			*/
        REMARK VARCHAR(64),					/*	Remark				*/
	 MASTERTYPE SMALLINT,					/*	0:Normal data 1:Piece data		*/
CONSTRAINT MASTERCATEGORYPRIMARYKEY1 PRIMARY KEY (CATEGORYID));


/* Table: Inspection Lot data, Owner: SYSDBA */
CREATE TABLE INSPECTIONLOT (
	LOTAUTOCOUNT INTEGER NOT NULL,			/*	Unique ID					*/
       MASTERCODE INTEGER NOT NULL,			/*	MasterCode. This is index to MasterData	*/
	LASTUPDATED TIMESTAMP,					/*	Last updated daytime				*/
       IDNAME VARCHAR(64),					/*	User-side ID Name				*/
       LOTNAME VARCHAR(64),					/*	User-side ID Name				*/
       REMARK VARCHAR(64),					/*	Remark						*/
CONSTRAINT INSPECTIONLOTPRIMARYKEY1 PRIMARY KEY (LOTAUTOCOUNT,MASTERCODE));


/* Table: Worker data, Owner: SYSDBA */
CREATE TABLE WORKER(
	ALIVE		SMALLINT not null,			/*	Dead code = 0	*/
	WORKERID	INTEGER not null,			/*	Worker ID	*/
	SECTION		varchar(64) not null,		/*	Section Code	*/
	NAME		varchar(64) not null,		/*	Name		*/
	REMARK		varchar(64),				/*	Remark		*/
	UPDATETIME	timestamp,					/*	UpdateTime	*/
CONSTRAINT WORKERPRIMARYKEY1 PRIMARY KEY (ALIVE,WORKERID));


/* Table: ColorSample data, Owner: SYSDBA */
CREATE TABLE COLORSAMPLE(
	AUTOCOUNT	INTEGER not null,			/*	autocount code = 0	*/
	NAME		varchar(64) ,				/*	Name		*/
	UPDATETIME	timestamp,					/*	UpdateTime	*/
	SAMPLETYPE	INTEGER,					/*	Sample data type  1:ColorLogic 	2:RGBStock	*/
       SAMPLEDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,	/*	Sample data	*/	
	COLORFOLDERID INTEGER,
CONSTRAINT COLORSAMPLEPRIMARYKEY1 PRIMARY KEY (AUTOCOUNT));


/* Table: Folder for ColorSample, Owner: SYSDBA */
CREATE TABLE COLORSAMPLEFOLDER (
        COLORFOLDERID INTEGER NOT NULL,		/*	Color Folder ID	*/
        COLORPARENTID INTEGER,				/*	Parent ID 		*/
	NUMBERINFOLDER INTEGER,					/*	Number in Folder	*/
        FOLDERNAME VARCHAR(32),				/*	Folder Name		*/
CONSTRAINT COLORFOLDERPRIMARYKEY1 PRIMARY KEY (COLORFOLDERID));

/* Table: Worker data, Owner: SYSDBA */
CREATE TABLE LIGHT(
	MACHINEID	integer not null,			/*	Machine ID		*/
	LIGHTID	integer not null,				/*	Light ID		*/
       LIGHTDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	Light data		*/
	DLLIDNAME	varchar(64),				/*	ID Name of DLL	*/
	NAME		varchar(64),				/*	Name			*/
	REMARK		varchar(64),				/*	Remark			*/
	UPDATETIME	timestamp,					/*	UpdateTime		*/
       LIGHTIMAGE BLOB SUB_TYPE 0 SEGMENT SIZE 80,		/*	Light image data	*/
CONSTRAINT LIGHTPRIMARYKEY1 PRIMARY KEY (MACHINEID,LIGHTID));

CREATE TABLE LEARNING(
	LEARNINGID	INTEGER not null,			/*	autocount code 		*/
	MACHINEID	INTEGER not null,			/*	Machine ID			*/
	UPDATETIME	timestamp NOT NULL,			/*	UpdateTime			*/
       MASTERCODE	INTEGER,				/*	MasterCode, -1:NoCode	*/
       SAMPLETYPE	INTEGER NOT NULL,			/*	1:OK 2:NG			*/
       PRIORITY	INTEGER,				/*	0:Strongest 1:lower		*/
       VERSION 	INTEGER,				/*	Version of Master Data		*/
       XSIZE 		INTEGER,				/*	Horizontal dots of SampleImage	*/
       YSIZE 		INTEGER,				/*	Vertical lines of SampleImage	*/
       LAYER		INTEGER,				/*	Layer count of SampleImage		*/
       MASTERIMAGE BLOB SUB_TYPE 0 SEGMENT SIZE 80,	/*	Sample master image data		*/
       TARGETIMAGE BLOB SUB_TYPE 0 SEGMENT SIZE 80,	/*	Sample target image data		*/
       POINTDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,	/*	NG Point mainly			*/
       ALIGNMENT BLOB SUB_TYPE 0 SEGMENT SIZE 80,	/*	Alignment between Master and Target*/
CONSTRAINT LEARNINGPRIMARYKEY1 PRIMARY KEY (LEARNINGID));

CREATE TABLE LEARNINGPARAM(
	PARAMID	INTEGER not null,			/*	autocount code 			*/
	LEARNINGID	INTEGER not null,			/*	Machine ID				*/
       LIBTYPE 	INTEGER NOT NULL,			/*	Library type				*/
       LIBID		INTEGER NOT NULL,			/*	Library ID				*/
       PARAMDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,	/*	Param data to be learned		*/
CONSTRAINT LEARNINGPARAMPRIMARYKEY1 PRIMARY KEY (PARAMID));

/* Table: CommonData by each LibraryType, Owner: SYSDBA */
CREATE TABLE COMMONDATAINLIBTYPE (
		LIBTYPE INTEGER NOT NULL,			/*	Library type		*/
		COMMONID INTEGER NOT NULL,			/*	Common ID			*/
		DATANAME VARCHAR(32),				/*	Data Name			*/
		LASTUPDATED TIMESTAMP,				/*	Last update daytime		*/
		DATAVERSION INTEGER,				/*	Data Version			*/
		SPECIFIEDDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,
CONSTRAINT COMMONDATAINLIBTYPEPRIMARYKEY1 PRIMARY KEY (LIBTYPE,COMMONID));

/* Table: Level for threshold, Owner: SYSDBA */
CREATE TABLE LEVELFOLDER (
		LEVELID INTEGER NOT NULL,		/*	Unique Level ID	*/
		LEVELVALUE INTEGER,				/*	Level value		*/
		PARENTID INTEGER,				/*	Parent ID		*/
		LEVELNAME VARCHAR(64),			/*	Level Name		*/
		REMARK	varchar(64),			/*	Remark			*/		
CONSTRAINT LEVELIDPRIMARYKEY1 PRIMARY KEY (LEVELID));

/* Table: stocker of threshold, Owner: SYSDBA */
CREATE TABLE THRESHOLDSTOCKER (
		THRESHOLDID INTEGER NOT NULL,		/*	Unique Level ID	*/
		LIBTYPE INTEGER NOT NULL,			/*	Library type		*/
		LIBID INTEGER NOT NULL,				/*	Library ID			*/
		LIBFOLDERID INTEGER NOT NULL,		/*	Library Folder ID	*/
		THRESHOLDNAME VARCHAR(64),			/*	Threshold Name		*/
		THRESHOLDREMARK VARCHAR(64),		/*	Threshold Name		*/
		UPDATETIME	timestamp,				/*	UpdateTime		*/
		THRESHOLDDATA BLOB SUB_TYPE 0 SEGMENT SIZE 80,
CONSTRAINT THRESHOLDSTOCKERPRIMARYKEY1 PRIMARY KEY (LIBTYPE,THRESHOLDID));



CREATE GENERATOR GMASTERCODE;
SET GENERATOR GMASTERCODE TO 1;

CREATE GENERATOR GMASTERCATEGORYID;
SET GENERATOR GMASTERCATEGORYID TO 1;

CREATE GENERATOR GLIBFOLDERID;
SET GENERATOR GLIBFOLDERID TO 1;

CREATE GENERATOR GCOLORFOLDERID;
SET GENERATOR GCOLORFOLDERID TO 1;


