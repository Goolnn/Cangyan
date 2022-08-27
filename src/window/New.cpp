#include <QMessageBox>
#include <QFileDialog>
#include <QDataStream>
#include <QImage>

#include "window/Window.hpp"
#include "window/Editor.hpp"
#include "window/New.hpp"

New::New(QWidget* parent) : QWidget(parent){
    this->layout = new QVBoxLayout();

    this->nameLayout = new QHBoxLayout();
    this->nameInput  = new QLineEdit();

    this->scrollArea = new QScrollArea();
    this->imagesManager = new ImagesManager();

    this->buttonLayout = new QHBoxLayout();
    this->acceptButton = new QPushButton("确认");
    this->cancelButton = new QPushButton("取消");

    this->addButton    = new QPushButton("添加");
    this->removeButton = new QPushButton("删除");

    this->removeButton->setDisabled(true);

    this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scrollArea->setWidget(this->imagesManager);

    this->nameInput->setPlaceholderText("文件名称");
    this->nameInput->setAlignment(Qt::AlignHCenter);

    this->nameLayout->addStretch();
    this->nameLayout->addWidget(this->nameInput);
    this->nameLayout->addStretch();

    this->buttonLayout->addWidget(this->addButton);
    this->buttonLayout->addWidget(this->removeButton);
    this->buttonLayout->addStretch();
    this->buttonLayout->addWidget(this->cancelButton);
    this->buttonLayout->addWidget(this->acceptButton);

    this->layout->addLayout(this->nameLayout);
    this->layout->addWidget(this->scrollArea);
    this->layout->addLayout(this->buttonLayout);

    this->setLayout(layout);
    
    QObject::connect(this->addButton, SIGNAL(clicked()), this, SLOT(add()));
    QObject::connect(this->removeButton, SIGNAL(clicked()), this->imagesManager, SLOT(removeImage()));

    QObject::connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(this->acceptButton, SIGNAL(clicked()), this, SLOT(accept()));

    QObject::connect(this->imagesManager, SIGNAL(focusChanged(Byte)), this, SLOT(focusChanged(Byte)));
    
}

New::~New(){
    delete this->nameInput;

    delete this->imagesManager;
    delete this->scrollArea;

    delete this->acceptButton;
    delete this->cancelButton;
    delete this->addButton;
    delete this->removeButton;

    delete this->nameLayout;
    delete this->buttonLayout;
    
    delete this->layout;

}

void New::add(){
    QStringList files = QFileDialog::getOpenFileNames(this, QStringLiteral("添加图片"), "./", QStringLiteral("图片文件(*png *jpg *jpeg)"));

    this->imagesManager->addFiles(files);

}

void New::cancel(){
    this->setParent(nullptr);
    this->hide();

    delete this;

}

void New::accept(){
    QString filename = this->nameInput->text();
    int count  = this->imagesManager->files.size();

    if(filename.compare("") == 0 || count == 0){
        QMessageBox::warning(this, "警告", "不输入名称或不导入图片的情况下无法保存！");

    }else{
        //选择文件保存位置
        QString savefile = QFileDialog::getExistingDirectory(this, "保存", "./");

        if(savefile.compare("") != 0){
            CYFile* file = new CYFile(savefile.append(QString("/%1.cy").arg(filename)));

            file->images = this->imagesManager->images;

            for(int i = 0; i < count; i++){
                file->texts.push_back(QList<Text>());

            }

            file->saveFile();

            Window* window = (Window*)this->parentWidget();
            window->setCYFile(file);

            // 关闭新建界面
            this->setParent(nullptr);
            this->hide();

            delete this;

            Editor* editor = new Editor(file);

            window->setCentralWidget(editor);
            editor->show();

        }

    }

}

void New::focusChanged(Byte newIndex){
    if(newIndex != 0){
        this->removeButton->setDisabled(false);

    }else{
        this->removeButton->setDisabled(true);

    }

}
