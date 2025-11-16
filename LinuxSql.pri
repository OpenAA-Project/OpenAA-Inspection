win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Qt5.15.8/5.15.8/gcc_64/lib/release/ -lQt5Sql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Qt5.15.8/5.15.8/gcc_64/lib/debug/ -lQt5Sql
else:unix: LIBS += -L$$PWD/../../../../Qt5.15.8/5.15.8/gcc_64/lib/ -lQt5Sql
