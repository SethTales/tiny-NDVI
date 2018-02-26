QT += widgets \

INCLUDEPATH += /urs/local/include

LIBS += -lGL
LIBS += -L/urs/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui

SOURCES += \
    main.cpp \
    tinyndvigui.cpp \
    inputimagegui.cpp \
    outputimagegui.cpp \
    ndviprocessor.cpp

HEADERS += \
    tinyndvigui.h \
    inputimagegui.h \
    outputimagegui.h \
    ndviprocessor.h
