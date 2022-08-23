INCLUDEPATH += include

HEADERS += include/window/Window.hpp \
           include/window/Signer.hpp \
           include/window/Editor.hpp \
           include/window/New.hpp \
           include/tool/CYFile.hpp \
           include/tool/Text.hpp \
           include/tool/Byte.hpp

SOURCES += src/window/Window.cpp \
           src/window/Signer.cpp \
           src/window/Editor.cpp \
           src/window/New.cpp \
           src/tool/CYFile.cpp \
           src/tool/Text.cpp \
           src/Cangyan.cpp

QT += widgets \
      gui

CONFIGS += console

OBJECTS_DIR = out/
RCC_DIR = out/
MOC_DIR = out/
UI_DIR = out/

DESTDIR = out/
