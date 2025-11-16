TEMPLATE = app
TARGET = XMLServer2
QT += core \
    gui \
    sql \
    xml \
    xmlpatterns \
    network
HEADERS += XMLDB/clsDbCtrl.h \
    clsCalcTime.h \
    Prm/clsLog.h \
    Prm/clsParam.h \
    SockSvr/clsXMLDB_Front.h \
    include/NList.h \
    SockSvr/clsTcpSlot.h \
    SockSvr/clsTcpSvr.h \
    XMLDB/clsDb.h \
    XMLDB/clsXmlReadSql.h \
    XMLDB/clsXmlUpd.h \
    XMLDB/clsXmlWhereLex.h \
    xmlserver2.h
SOURCES += XMLDB/clsDbCtrl.cpp \
    clsCalcTime.cpp \
    Prm/clsLog.cpp \
    XMLDB/createDb.cpp \
    Prm/clsParam.cpp \
    SockSvr/clsXMLDB_Front.cpp \
    include/NList.cpp \
    SockSvr/clsTcpSlot.cpp \
    SockSvr/clsTcpSvr.cpp \
    SockSvr/clsTcpSvrThread.cpp \
    SockSvr/clsTimeOut.cpp \
    XMLDB/clsDb.cpp \
    XMLDB/clsXmlLexBase.cpp \
    XMLDB/clsXmlOrderLex.cpp \
    XMLDB/clsXmlOutLex.cpp \
    XMLDB/clsXmlReadSql.cpp \
    XMLDB/clsXmlUpd.cpp \
    XMLDB/clsXmlWhereLex.cpp \
    main.cpp \
    xmlserver2.cpp
FORMS += Prm/clsParam.ui \
    xmlserver2.ui
RESOURCES += 
INCLUDEPATH += ./include \
    ./SockSvr \
    ./XMLDB \
    ./Prm \
    /opt/firebird/include
LIBS += -L/opt/firebird/lib \
    -lfbclient
