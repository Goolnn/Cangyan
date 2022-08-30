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

    if(qtTranslator.load(":/translation/qt_zh_CN.qm")){
        QCoreApplication::installTranslator(&qtTranslator);

    }

    if(qtBaseTranslator.load(":/translation/qtbase_zh_CN.qm")){
        QCoreApplication::installTranslator(&qtBaseTranslator);

    }

    // 处理命令行参数
    QString filepath = "";

    if(argc == 2){
        filepath = argv[1];

    }

    // 显示程序窗口
    Window window(filepath);
    window.show();

    return application.exec();

}
