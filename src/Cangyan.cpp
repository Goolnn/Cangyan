#include <QApplication>
#include <QTranslator>

#include "window/Window.hpp"

/**
 * 苍眼汉化组
 */
int main(int argc, char* argv[]){
    QApplication application = QApplication(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load(":/translation/qt_zh_CN.qm");
    application.installTranslator(&qtTranslator);

    QTranslator qtBaseTranslator;
    qtBaseTranslator.load(":/translation/qtbase_zh_CN.qm");
    application.installTranslator(&qtBaseTranslator);

    Window window;
    window.show();

    return application.exec();

}
