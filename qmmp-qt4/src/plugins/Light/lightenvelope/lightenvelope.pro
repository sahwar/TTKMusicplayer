include(../../plugins.pri)

TARGET=$$PLUGINS_PREFIX/Light/lightenvelope
QMAKE_CLEAN =$$PLUGINS_PREFIX/Light/liblightenvelope.so

include(../../Visual/common/common.pri)

SOURCES += \
        lightenvelope.cpp \
        visuallightenvelopefactory.cpp

HEADERS  += \
        lightenvelope.h \
        visuallightenvelopefactory.h

win32:{
    INCLUDEPATH += ./
}

unix{
    target.path = $$LIB_DIR/qmmp/Visual
    INSTALLS += target
    LIBS += -L/usr/lib -I/usr/include
}
