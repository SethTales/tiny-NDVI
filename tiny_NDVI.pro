QT += widgets \

INCLUDEPATH += /urs/local/include

LIBS += -lGL
LIBS += -L/urs/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui

SOURCES += \
    main.cpp \
    inputimagegui.cpp \
    outputimagegui.cpp \
    ndviprocessor.cpp \
    maingui.cpp \
    ndviworkerthread.cpp

HEADERS += \
    inputimagegui.h \
    outputimagegui.h \
    ndviprocessor.h \
    maingui.h \
    ndviworkerthread.h
