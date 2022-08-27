#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QWidget>

#include "window/ImagesList.hpp"
#include "window/Window.hpp"
#include "window/Editor.hpp"
#include "tool/BezierCurve.hpp"

Window::Window(QWidget* parent) : QMainWindow(parent){
    // 菜单栏
    this->menuBar = new QMenuBar(this);

    this->fileMenu = new QMenu("文件(&F)", this);
    this->editMenu = new QMenu("编辑(&E)", this);
    this->helpMenu = new QMenu("帮助(&H)", this);

    this->newAction   = new QAction("新建文件", this);
    this->openAction  = new QAction("打开文件", this);
    this->saveAction  = new QAction("保存文件", this);
    this->closeAction = new QAction("关闭界面", this);
    this->exitAction  = new QAction("退出程序", this);

    this->imagesListAction = new QAction("图像列表", this);
    // this->undoAction  = new QAction("撤销", this);
    // this->redoAction  = new QAction("重做", this);
    // this->cutAction   = new QAction("剪切", this);
    // this->copyAction  = new QAction("复制", this);
    // this->pasteAction = new QAction("粘贴", this);

    this->aboutAction = new QAction("关于", this);

    // 汉化组徽标
    this->logo = new QImage(":/res/logo.png");

    this->file = nullptr;

    this->filesaved = true;

    // 设置菜单快捷键
    this->newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    this->openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    this->saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    this->closeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
    this->exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    this->imagesListAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));

    // 连接菜单栏
    this->menuBar->addMenu(this->fileMenu);
    // this->menuBar->addMenu(this->editMenu);
    this->menuBar->addMenu(this->helpMenu);

    this->fileMenu->addAction(this->newAction);
    this->fileMenu->addAction(this->openAction);
    this->fileMenu->addAction(this->saveAction);
    this->fileMenu->addAction(this->closeAction);
    this->fileMenu->addSeparator();
    this->fileMenu->addAction(this->exitAction);

    this->editMenu->addAction(this->imagesListAction);
    // this->editMenu->addAction(this->undoAction);
    // this->editMenu->addAction(this->redoAction);
    // this->editMenu->addSeparator();
    // this->editMenu->addAction(this->cutAction);
    // this->editMenu->addAction(this->copyAction);
    // this->editMenu->addAction(this->pasteAction);

    this->helpMenu->addAction(this->aboutAction);

    // 信号连接
    QObject::connect(this->newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    QObject::connect(this->openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(this->saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(this->closeAction, SIGNAL(triggered()), this, SLOT(closeView()));

    QObject::connect(this->imagesListAction, SIGNAL(triggered()), this, SLOT(openImagesList()));

    QObject::connect(this->exitAction, SIGNAL(triggered()), this, SLOT(close()));

    QObject::connect(this->aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    // 窗口参数
    this->setWindowTitle("苍眼汉化组");
    this->setMinimumSize(640, 480);
    this->setMenuBar(this->menuBar);
    this->setWindowIcon(QIcon(":/res/icon.png"));
    this->resize(960, 640);

}

Window::~Window(){
    delete this->menuBar;

    delete this->fileMenu;
    delete this->editMenu;
    delete this->helpMenu;

    delete this->newAction;
    delete this->openAction;
    delete this->saveAction;
    delete this->closeAction;
    delete this->exitAction;

    delete this->imagesListAction;
    // delete this->undoAction;
    // delete this->redoAction;
    // delete this->cutAction;
    // delete this->copyAction;
    // delete this->pasteAction;

    delete this->aboutAction;

    delete this->logo;

}

void Window::setCYFile(CYFile* file){
    this->file = file;

    QObject::connect(this->file, SIGNAL(fileSaved()), this, SLOT(fileSaved()));
    QObject::connect(this->file, SIGNAL(fileChanged()), this, SLOT(fileChanged()));

}

void Window::paintEvent(QPaintEvent*){
    QPainter p = QPainter(this);

    // 组徽显示动画
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    static long startTime = 0;

    p.setOpacity(0);

    long deltaTime = ms.count() - startTime - 500;

    if(startTime == 0){
        startTime = ms.count();
        this->update();
        
    }else{
        float process = deltaTime / 1000.0;

        if(process <= 1.0){
            p.setOpacity(process);
            this->update();

        }else{
            p.setOpacity(1.0);

        }

    }

    // 绘制组徽
    p.drawImage((this->width() - this->logo->width()) / 2, (this->height() - this->logo->height()) / 2, *this->logo);

}

void Window::closeEvent(QCloseEvent* event){
    if(this->file != nullptr && !this->filesaved){
        QMessageBox::StandardButton result = QMessageBox::question(this, "保存", "是否先进行最后一次保存后再进行新建操作？", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::StandardButton::Yes);

        if(result == QMessageBox::Yes){
            this->saveFile();

            event->accept();
            return;

        }else if(result == QMessageBox::No){
            event->accept();
            return;

        }else if(result == QMessageBox::Cancel){
            event->ignore();

        }
        
    }else{
        event->accept();

    }

}

void Window::newFile(){
    if(this->file != nullptr && !this->filesaved){
        QMessageBox::StandardButton result = QMessageBox::question(this, "保存", "是否先进行最后一次保存后再进行新建操作？", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::StandardButton::Yes);

        if(result == QMessageBox::StandardButton::Yes){
            this->file->saveFile();
            this->file = nullptr;

        }else if(result == QMessageBox::StandardButton::Cancel){
            return;

        }

    }

    New* newInterface = new New();

    this->setCentralWidget(newInterface);
    newInterface->show();

}

void Window::openFile(){
    if(this->file != nullptr && !this->filesaved){
        QMessageBox::StandardButton result = QMessageBox::question(this, "保存", "是否先进行最后一次保存后再进行打开操作？", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::StandardButton::Yes);

        if(result == QMessageBox::StandardButton::Yes){
            this->file->saveFile();
            this->file = nullptr;

        }else if(result == QMessageBox::StandardButton::Cancel){
            return;

        }

    }

    this->setCentralWidget(nullptr);

    QString filepath = QFileDialog::getOpenFileName(this, QStringLiteral("打开"), "./", QStringLiteral("翻译文件(*cy)"));

    if(filepath.compare("") != 0){
        CYFile* file = new CYFile(filepath);
        file->loadFile();
        this->setCYFile(file);

        Editor* editor = new Editor(file);

        this->setCentralWidget(editor);
        editor->show();

    }

}

void Window::saveFile(){
    if(this->file != nullptr && !this->filesaved){
        this->file->saveFile();
        this->filesaved = true;

    }

}

void Window::closeView(){
    if(this->file != nullptr && !this->filesaved){
        QMessageBox::StandardButton result = QMessageBox::question(this, "保存", "是否先进行最后一次保存后再进行打开操作？", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::StandardButton::Yes);

        if(result == QMessageBox::StandardButton::Yes){
            this->file->saveFile();
            this->file = nullptr;

        }else if(result == QMessageBox::StandardButton::Cancel){
            return;

        }

    }

    if(this->centralWidget() != nullptr){
        this->setCentralWidget(nullptr);
        this->file = nullptr;
        
        this->setWindowTitle("苍眼汉化组");

    }

}

void Window::openImagesList(){
    if(this->file != nullptr && !this->filesaved){
        QMessageBox::StandardButton result = QMessageBox::question(this, "保存", "是否先进行最后一次保存后再编辑图像列表？", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::StandardButton::Yes);

        if(result == QMessageBox::StandardButton::Yes){
            this->file->saveFile();
            this->file = nullptr;

        }else if(result == QMessageBox::StandardButton::Cancel){
            return;

        }

    }

    if(this->file != nullptr){
        ImagesList* imagesList = new ImagesList();

        this->setCentralWidget(imagesList);
        imagesList->show();

    }

}

void Window::about(){
    QMessageBox::about(this, "关于", "由谷林为苍眼汉化组便于开展工作而设计的小程序~\n如果有任何更新建议都可以向谷林提出哦！\n\n程序代码由 谷林 编写，程序背景图标、应用图标由 柴白 绘制。\n\n版本：1.0.14");

}

void Window::fileSaved(){
    this->setWindowTitle("苍眼汉化组");
    this->filesaved = true;

}

void Window::fileChanged(){
    this->setWindowTitle(" • 苍眼汉化组");
    this->filesaved = false;

}
