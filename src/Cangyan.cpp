#include <QApplication>

#include "window/Window.hpp"

/**
 * 苍眼汉化组
 */
int main(int argc, char* argv[]){
    QApplication application = QApplication(argc, argv);
    Window window;

    window.show();

    return application.exec();

}
