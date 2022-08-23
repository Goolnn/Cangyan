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
    this->nameLabel  = new QLabel("名称");
    this->nameInput  = new QLineEdit();

    this->imagesList = new QListWidget();

    this->buttonLayout = new QHBoxLayout();
    this->acceptButton = new QPushButton("确认");
    this->cancelButton = new QPushButton("取消");

    this->addButton    = new QPushButton("添加");
    this->removeButton = new QPushButton("删除");
    this->upButton     = new QPushButton("上移");
    this->downButton   = new QPushButton("下移");

    this->nameLayout->addWidget(this->nameLabel);
    this->nameLayout->addWidget(this->nameInput);

    this->buttonLayout->addWidget(this->addButton);
    this->buttonLayout->addWidget(this->removeButton);
    this->buttonLayout->addWidget(this->upButton);
    this->buttonLayout->addWidget(this->downButton);
    this->buttonLayout->addStretch();
    this->buttonLayout->addWidget(this->cancelButton);
    this->buttonLayout->addWidget(this->acceptButton);

    this->layout->addLayout(this->nameLayout);
    this->layout->addWidget(this->imagesList);
    this->layout->addLayout(this->buttonLayout);

    this->setLayout(layout);
    
    QObject::connect(this->addButton, SIGNAL(clicked()), this, SLOT(add()));
    QObject::connect(this->removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    QObject::connect(this->upButton, SIGNAL(clicked()), this, SLOT(up()));
    QObject::connect(this->downButton, SIGNAL(clicked()), this, SLOT(down()));

    QObject::connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(this->acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
    
}

New::~New(){
    qDebug("New has being deleted.");

    delete nameLabel;
    delete nameInput;

    delete imagesList;

    delete acceptButton;
    delete cancelButton;
    delete addButton;
    delete removeButton;

    delete nameLayout;
    delete buttonLayout;
    
    delete layout;

}

void New::add(){
    QStringList fileNames = QFileDialog::getOpenFileNames(this, QStringLiteral("添加图片"), "./", QStringLiteral("图片文件(*png *jpg *jpeg)"));

    this->imagesList->addItems(fileNames);

}

void New::remove(){
    delete this->imagesList->currentItem();

}

void New::up(){
    QListWidgetItem* currentItem = this->imagesList->currentItem();

    if(currentItem != nullptr){
        int currentRow = this->imagesList->currentRow();
        QString currentString = currentItem->text();

        if(currentRow > 0){
            delete currentItem;

            this->imagesList->insertItem(currentRow - 1, currentString);

        }

        this->imagesList->setCurrentRow(currentRow - 1);

    }

}

void New::down(){
    QListWidgetItem* currentItem = this->imagesList->currentItem();

    if(currentItem != nullptr){
        int currentRow = this->imagesList->currentRow();
        QString currentString = currentItem->text();

        if(this->imagesList->count() - currentRow > 0){
            delete currentItem;

            this->imagesList->insertItem(currentRow + 1, currentString);

        }

        this->imagesList->setCurrentRow(currentRow + 1);

    }

}

void New::cancel(){
    this->setParent(nullptr);
    this->hide();

    delete this;

}

void New::accept(){
    QString filename = this->nameInput->text();
    int count  = this->imagesList->count();

    if(filename.compare("") == 0 || count == 0){
        QMessageBox::warning(this, "苍眼汉化组 - 警告", "不输入名称或不导入图片的情况下无法保存！");

    }else{
        //选择文件保存位置
        QString savefile = QFileDialog::getExistingDirectory(this, "保存", "./");

        if(savefile.compare("") != 0){
            CYFile* file = new CYFile(savefile.append(QString("/%1.cy").arg(filename)));

            for(int i = 0; i < count; i++){
                QListWidgetItem* item = this->imagesList->item(i);
                QFile image = QFile(item->text());

                if(image.open(QIODevice::ReadOnly)){
                    unsigned int imageSize = image.size();

                    file->images.push_back(QImage::fromData((unsigned char*)image.readAll().data(), imageSize));
                    file->texts.push_back(QList<Text>());

                }

                image.close();

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
