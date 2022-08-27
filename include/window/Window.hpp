#ifndef GOOLNN_CANGYAN_WINDOW_WINDOW
#define GOOLNN_CANGYAN_WINDOW_WINDOW

#include <QPaintEvent>
#include <QMainWindow>
#include <QCloseEvent>
#include <QMenuBar>
#include <QImage>
#include <QMenu>

#include "window/New.hpp"
#include "tool/CYFile.hpp"

class Window : public QMainWindow{
    Q_OBJECT

    private:
        QMenuBar* menuBar;          //菜单

        QMenu* fileMenu;            //文件
        QMenu* editMenu;            //编辑
        QMenu* helpMenu;            //帮助

        QAction* newAction;         //新建
        QAction* openAction;        //打开
        QAction* saveAction;        //保存
        QAction* closeAction;       //关闭
        QAction* exitAction;        //退出

        QAction* imagesListAction;  //图像列表
        // QAction* undoAction;        //撤销
        // QAction* redoAction;        //重做
        // QAction* cutAction;         //剪切
        // QAction* copyAction;        //复制
        // QAction* pasteAction;       //粘贴

        QAction* aboutAction;       //关于

        QImage* logo;               //汉化组徽标

        CYFile* file;

        bool filesaved;

    public:
        Window(QWidget* parent = nullptr);
        ~Window();

        void setCYFile(CYFile* file);

    protected:
        void paintEvent(QPaintEvent*);

        void closeEvent(QCloseEvent* event);
    
    private slots:
        void newFile();
        void openFile();
        void saveFile();
        void closeView();

        void openImagesList();

        void about();

        void fileSaved();
        void fileChanged();
    
};

#endif
