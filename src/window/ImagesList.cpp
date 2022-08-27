#include "window/ImagesList.hpp"

ImagesList::ImagesList(QWidget* parent) : QWidget(parent){
    this->layout = new QVBoxLayout();

    this->scrollArea = new QScrollArea();
    this->imageManager = new ImagesManager();

    this->hBox = new QHBoxLayout();
    this->addButton    = new QPushButton("添加");
    this->removeButton = new QPushButton("删除");
    this->cancelButton = new QPushButton("取消");
    this->acceptButton = new QPushButton("确定");

    this->removeButton->setDisabled(true);

    this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    this->scrollArea->setWidget(this->imageManager);

    this->hBox->addWidget(this->addButton);
    this->hBox->addWidget(this->removeButton);
    this->hBox->addStretch();
    this->hBox->addWidget(this->cancelButton);
    this->hBox->addWidget(this->acceptButton);

    this->layout->addWidget(this->scrollArea);
    this->layout->addLayout(this->hBox);

    this->setLayout(this->layout);

}

ImagesList::~ImagesList(){
    delete this->addButton;
    delete this->removeButton;
    delete this->cancelButton;
    delete this->acceptButton;

    delete this->imageManager;
    delete this->hBox;

    delete this->layout;
    
}
