TEMPLATE = app
TARGET = XMLDB_MakeDatThread
QT += core \
    gui \
    sql \
    xml \
    network
HEADERS += MakeDat/clsMakeDat.h \
    Common/clsDb.h \
    Common/clsLog.h \
    Common/clsRand.h \
    xmldb_makedatthread.h
SOURCES += MakeDat/clsMakeDat.cpp \
    Common/clsDb.cpp \
    Common/clsLog.cpp \
    Common/clsRand.cpp \
    Common/createDb.cpp \
    main.cpp \
    xmldb_makedatthread.cpp
FORMS += xmldb_makedatthread.ui
RESOURCES += 
INCLUDEPATH+= \
	./Common \
	./MakeDat \
	/opt/firebird/include
	
LIBS+= -L/opt/firebird/lib -lfbclient
	