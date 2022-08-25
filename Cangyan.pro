INCLUDEPATH += include

HEADERS += include/window/ImageViewer.hpp \
           include/window/Window.hpp \
           include/window/Editor.hpp \
           include/window/New.hpp \
           include/tool/BezierCurve.hpp \
           include/tool/CYFile.hpp \
           include/tool/Text.hpp \
           include/tool/Math.hpp \
           include/tool/Byte.hpp

SOURCES += src/window/ImageViewer.cpp \
           src/window/Window.cpp \
           src/window/Editor.cpp \
           src/window/New.cpp \
           src/tool/BezierCurve.cpp \
           src/tool/CYFile.cpp \
           src/tool/Text.cpp \
           src/tool/Math.cpp \
           src/Cangyan.cpp

RESOURCES += qrc/resources.qrc

QT += widgets

CONFIGS += console

OBJECTS_DIR = out/
RCC_DIR = out/
MOC_DIR = out/
UI_DIR = out/

DESTDIR = out/
