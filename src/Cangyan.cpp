#include <QCoreApplication>
#include <QApplication>
#include <QTranslator>

#include "window/Window.hpp"

/**
 * 苍眼汉化组
 */
int main(int argc, char* argv[]){
    QApplication application = QApplication(argc, argv);

    // 加载中文翻译
    QTranslator qtTranslator;
    QTranslator qtBaseTranslator;
    qtTranslator.load(":/translation/qt_zh_CN.qm");
    qtBaseTranslator.load(":/translation/qtbase_zh_CN.qm");

    QCoreApplication::installTranslator(&qtTranslator);
    QCoreApplication::installTranslator(&qtBaseTranslator);

    // 显示程序窗口
    Window window;
    window.show();

    return application.exec();

}
