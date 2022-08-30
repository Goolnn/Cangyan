#include "window/Window.hpp"
#include "window/Editor.hpp"

Editor::Editor(CYFile* file){
    this->layout = new QVBoxLayout();

    this->splitter = new QSplitter();

    this->imageViewer = new ImageViewer(file);

    this->textWidget = new QWidget();
    this->textLayout = new QVBoxLayout();
    this->indexLabel = new QLabel(QString("%1").arg(this->imageViewer->getCYFile()->texts.at(this->imageViewer->getIndex()).size()));
    // this->notesViewer = new NotesViewer();

    this->textEdit   = new QTextEdit();

    this->buttonLayout = new QHBoxLayout();
    this->addButton    = new QPushButton("添加");
    this->removeButton = new QPushButton("删除");

    this->buttomLayout   = new QHBoxLayout();
    this->previousButton = new QPushButton("上一页");
    this->pageLabel      = new QLabel(QString("%1/%2").arg(this->imageViewer->getIndex()+1).arg(this->imageViewer->getSize()));
    this->nextButton     = new QPushButton("下一页");

    this->previousButton->setDisabled(true);
    this->textEdit->setDisabled(true);
    this->removeButton->setDisabled(true);

    this->indexLabel->setAlignment(Qt::AlignCenter);

    this->textWidget->setLayout(this->textLayout);
    this->textLayout->addWidget(this->indexLabel);
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

    this->imageViewer->setParent(this->splitter);
    this->textWidget->setParent(this->splitter);

    this->layout->addWidget(this->splitter);
    this->layout->addLayout(this->buttomLayout);

    this->setLayout(this->layout);

    QObject::connect(this->addButton, SIGNAL(clicked()), this, SLOT(add()));

    QObject::connect(this->previousButton, SIGNAL(clicked()), this->imageViewer, SLOT(previous()));
    QObject::connect(this->nextButton, SIGNAL(clicked()), this->imageViewer, SLOT(next()));

    QObject::connect(this->removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(this->imageViewer, SIGNAL(pageChanged()), this, SLOT(updatePage()));
    QObject::connect(this->imageViewer, SIGNAL(focusChanged()), this, SLOT(updateText()));
    QObject::connect(this->imageViewer, SIGNAL(focusChanged()), this, SLOT(updateDelete()));

    QObject::connect(this->textEdit, SIGNAL(textChanged()), this, SLOT(saveText()));

    QObject::connect(this->imageViewer, SIGNAL(addDone()), this, SLOT(addDone()));

    QObject::connect(this->imageViewer, SIGNAL(tryRemove()), this, SLOT(remove()));
    QObject::connect(this->imageViewer, SIGNAL(tryAdd()), this, SLOT(add()));
    
}

Editor::~Editor(){
    delete textEdit;
    delete indexLabel;
    
    delete addButton;
    delete removeButton;
    delete buttonLayout;

    delete textLayout;
    delete textWidget;

    delete previousButton;
    delete pageLabel;
    delete nextButton;
    delete buttomLayout;

    delete imageViewer;

    delete splitter;

    delete layout;

}

void Editor::updatePage(){
    this->pageLabel->setText(QString("%1/%2").arg(this->imageViewer->getIndex()+1).arg(this->imageViewer->getSize()));

    if(this->imageViewer->getIndex() == 0){
        this->previousButton->setDisabled(true);

    }else{
        this->previousButton->setDisabled(false);

    }

    if(this->imageViewer->getIndex() == this->imageViewer->getSize() - 1){
        this->nextButton->setDisabled(true);

    }else{
        this->nextButton->setDisabled(false);

    }

}

void Editor::updateText(){
    if(this->imageViewer->getFocusIndex() != 0){
        this->textEdit->setDisabled(false);
        Text text = this->imageViewer->getCYFile()->texts.at(this->imageViewer->getIndex()).at(this->imageViewer->getFocusIndex() - 1);
        this->textEdit->setText(text.getText());
        this->indexLabel->setText(QString("%1/%2").arg(this->imageViewer->getFocusIndex()).arg(this->imageViewer->getCYFile()->texts.at(this->imageViewer->getIndex()).size()));

    }else{
        this->textEdit->setDisabled(true);
        this->textEdit->setText("");
        this->indexLabel->setText(QString("%1").arg(this->imageViewer->getCYFile()->texts.at(this->imageViewer->getIndex()).size()));

    }

}

void Editor::updateDelete(){
    if(this->imageViewer->getFocusIndex() != 0){
        this->removeButton->setDisabled(false);

    }else{
        this->removeButton->setDisabled(true);

    }

}

void Editor::saveText(){
    if(this->imageViewer->getFocusIndex() != 0){
        this->imageViewer->getCYFile()->setText(this->imageViewer->getIndex(), this->imageViewer->getFocusIndex() - 1, this->textEdit->toPlainText());

    }

}

void Editor::add(){
    this->addButton->setDisabled(true);
    this->imageViewer->add();

}

void Editor::addDone(){
    this->addButton->setDisabled(false);

}

void Editor::remove(){
    if(this->imageViewer->getFocusIndex() != 0){
        this->imageViewer->getCYFile()->removeText(this->imageViewer->getIndex(), this->imageViewer->getFocusIndex() - 1);
        this->imageViewer->setFocusIndex(0);

        this->update();

    }

}
