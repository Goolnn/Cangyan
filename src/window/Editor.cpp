#include "window/Window.hpp"
#include "window/Editor.hpp"

Editor::Editor(CYFile* file){
    this->layout = new QVBoxLayout();

    this->splitter = new QSplitter();

    this->signer = new Signer(file);

    this->textWidget = new QWidget();
    this->textLayout = new QVBoxLayout();
    this->textEdit   = new QTextEdit();

    this->buttonLayout = new QHBoxLayout();
    this->addButton    = new QPushButton("添加");
    this->removeButton = new QPushButton("删除");

    this->buttomLayout   = new QHBoxLayout();
    this->previousButton = new QPushButton("上一页");
    this->pageLabel      = new QLabel(QString("%1/%2").arg(this->signer->getIndex()+1).arg(this->signer->getSize()));
    this->nextButton     = new QPushButton("下一页");

    this->previousButton->setDisabled(true);
    this->textEdit->setDisabled(true);
    this->removeButton->setDisabled(true);

    this->textWidget->setLayout(this->textLayout);
    this->textLayout->addWidget(this->textEdit);
    this->textLayout->addLayout(this->buttonLayout);

    this->buttonLayout->addStretch();
    this->buttonLayout->addWidget(this->removeButton);
    this->buttonLayout->addWidget(this->addButton);
    this->buttonLayout->addStretch();

    this->buttomLayout->addWidget(this->previousButton);
    this->buttomLayout->addStretch();
    this->buttomLayout->addWidget(this->pageLabel);
    this->buttomLayout->addStretch();
    this->buttomLayout->addWidget(this->nextButton);

    this->signer->setParent(this->splitter);
    this->textWidget->setParent(this->splitter);

    this->layout->addWidget(this->splitter);
    this->layout->addLayout(this->buttomLayout);

    this->setLayout(this->layout);

    QObject::connect(this->addButton, SIGNAL(clicked()), this, SLOT(add()));

    QObject::connect(this->previousButton, SIGNAL(clicked()), this->signer, SLOT(previous()));
    QObject::connect(this->nextButton, SIGNAL(clicked()), this->signer, SLOT(next()));

    QObject::connect(this->removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(this->signer, SIGNAL(pageChanged()), this, SLOT(updatePage()));
    QObject::connect(this->signer, SIGNAL(focusChanged()), this, SLOT(updateText()));
    QObject::connect(this->signer, SIGNAL(focusChanged()), this, SLOT(updateDelete()));

    QObject::connect(this->textEdit, SIGNAL(textChanged()), this, SLOT(saveText()));

    QObject::connect(this->signer, SIGNAL(addDone()), this, SLOT(addDone()));

    QObject::connect(this->signer, SIGNAL(tryRemove()), this, SLOT(remove()));
    QObject::connect(this->signer, SIGNAL(tryAdd()), this, SLOT(add()));
    
}

Editor::~Editor(){
    delete textEdit;
    
    delete addButton;
    delete removeButton;
    delete buttonLayout;

    delete textLayout;
    delete textWidget;

    delete previousButton;
    delete pageLabel;
    delete nextButton;
    delete buttomLayout;

    delete signer;

    delete splitter;

    delete layout;

}

void Editor::updatePage(){
    this->pageLabel->setText(QString("%1/%2").arg(this->signer->getIndex()+1).arg(this->signer->getSize()));

    if(this->signer->getIndex() == 0){
        this->previousButton->setDisabled(true);

    }else{
        this->previousButton->setDisabled(false);

    }

    if(this->signer->getIndex() == this->signer->getSize() - 1){
        this->nextButton->setDisabled(true);

    }else{
        this->nextButton->setDisabled(false);

    }

}

void Editor::updateText(){
    if(this->signer->getFocusIndex() != 0){
        this->textEdit->setDisabled(false);
        Text text = this->signer->getCYFile()->texts.at(this->signer->getIndex()).at(this->signer->getFocusIndex() - 1);
        this->textEdit->setText(text.getText());

    }else{
        this->textEdit->setDisabled(true);
        this->textEdit->setText("");

    }

}

void Editor::updateDelete(){
    if(this->signer->getFocusIndex() != 0){
        this->removeButton->setDisabled(false);

    }else{
        this->removeButton->setDisabled(true);

    }

}

void Editor::saveText(){
    if(this->signer->getFocusIndex() != 0){
        Text* text = (Text*)&(this->signer->getCYFile()->texts.at(this->signer->getIndex()).at(this->signer->getFocusIndex() - 1));
        text->setText(this->textEdit->toPlainText());

    }

}

void Editor::add(){
    this->addButton->setDisabled(true);
    this->signer->add();

}

void Editor::addDone(){
    this->addButton->setDisabled(false);

}

void Editor::remove(){
    if(this->signer->getFocusIndex() != 0){
        QList<Text>* list = (QList<Text>*)&(this->signer->getCYFile()->texts.at(this->signer->getIndex()));
        list->removeAt(this->signer->getFocusIndex() - 1);

        this->signer->setFocusIndex(0);

        this->update();

    }

}
