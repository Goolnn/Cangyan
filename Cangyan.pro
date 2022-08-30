INCLUDEPATH += include

HEADERS += include/window/ImagesManager.hpp \
           include/window/NotesViewer.hpp \
           include/window/ImageViewer.hpp \
           include/window/ImagesList.hpp \
           include/window/NewFile.hpp \
           include/window/Window.hpp \
           include/window/Editor.hpp \
           include/tool/BezierCurve.hpp \
           include/tool/CYFile.hpp \
           include/tool/Text.hpp \
           include/tool/Math.hpp \
           include/tool/Byte.hpp

SOURCES += src/window/ImagesManager.cpp \
           src/window/NotesViewer.cpp \
           src/window/ImageViewer.cpp \
           src/window/ImagesList.cpp \
           src/window/NewFile.cpp \
           src/window/Window.cpp \
           src/window/Editor.cpp \
           src/tool/BezierCurve.cpp \
           src/tool/CYFile.cpp \
           src/tool/Text.cpp \
           src/tool/Math.cpp \
           src/Cangyan.cpp

RESOURCES += qrc/resources.qrc

QT += widgets

RC_ICONS = qrc/res/logo.png

OBJECTS_DIR = out/
RCC_DIR = out/
MOC_DIR = out/
UI_DIR = out/

DESTDIR = out/
