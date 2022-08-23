#include <QDataStream>
#include <QPainter>
#include <QRectF>
#include <QFile>

#include <math.h>

#include "window/Signer.hpp"
#include "window/Editor.hpp"

Signer::Signer(CYFile* file) : QWidget(nullptr){
    this->file = file;

    this->index = 0;
    this->size = this->file->images.size();

    this->adding = false;

    this->setFocusPolicy(Qt::StrongFocus);

}

Signer::~Signer(){
    delete this->file;

}

void Signer::setFocusIndex(Byte index){
    this->focusIndex = index;

    emit focusChanged();

}

CYFile* Signer::getCYFile(){
    return this->file;

}

unsigned char Signer::getIndex(){
    return this->index;

}

unsigned char Signer::getSize(){
    return this->size;

}

Byte Signer::getFocusIndex(){
    return this->focusIndex;

}

void Signer::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_A){
        this->previous();

    }
    
    if(event->key() == Qt::Key_D){
        this->next();

    }

    if(event->key() == Qt::Key_S){
        emit tryAdd();

    }

    if(event->key() == Qt::Key_W){
        emit tryRemove();

    }

}

void Signer::mousePressEvent(QMouseEvent* event){
    QPoint pos = event->pos();

    if(this->adding){
        if(QRect(this->imageX, this->imageY, this->imageWidth, this->imageHeight).contains(pos.x(), pos.y())){
            QList<Text>* list = (QList<Text>*)&(this->file->texts.at(this->index));
            list->push_back(Text((pos.x() - this->imageX) * (this->file->images.at(this->index).width() / this->imageWidth), (pos.y() - this->imageY) * (this->file->images.at(this->index).height() / this->imageHeight), ""));

            this->focusIndex = list->size();

            this->update();

            emit focusChanged();
            emit addDone();

            this->adding = false;

        }

    }else{
        QList<Text>* list = (QList<Text>*)&(this->file->texts.at(this->index));

        this->focusIndex = 0;

        for(int i = 0; i < list->size(); i++){
            Text text = list->at(i);

            float mouseX = (pos.x() - this->imageX) * (this->file->images.at(this->index).width() / this->imageWidth);
            float mouseY = (pos.y() - this->imageY) * (this->file->images.at(this->index).height() / this->imageHeight);

            if(sqrt((text.getX() - mouseX) * (text.getX() - mouseX) + (text.getY() - mouseY) * (text.getY() - mouseY)) <= this->RADIUS){
                this->focusIndex = i + 1;

                break;

            }

        }

        emit focusChanged();

        this->update();

    }

}

void Signer::paintEvent(QPaintEvent*){
    QPainter p = QPainter(this);

    p.setRenderHint(QPainter::Antialiasing, true);

    // 控件宽高
    float widgetWidth  = this->width();
    float widgetHeight = this->height();

    // 图像缩放
    if(widgetWidth / widgetHeight > (float)this->file->images.at(index).width() / this->file->images.at(index).height()){
        this->imageWidth  = widgetHeight / this->file->images.at(index).height() * this->file->images.at(index).width();
        this->imageHeight = widgetHeight;

    }else{
        this->imageWidth  = widgetWidth;
        this->imageHeight = widgetWidth / this->file->images.at(index).width() * this->file->images.at(index).height();

    }

    // 坐标运算
    imageX = (widgetWidth - this->imageWidth) / 2;
    imageY = (widgetHeight - this->imageHeight) / 2;

    // 绘制图像
    p.drawImage(this->imageX, this->imageY, this->file->images.at(index).scaled(this->imageWidth, this->imageHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    // 绘制注释
    for(int i = 0; i < this->file->texts.at(this->index).size(); i++){
        Text text = this->file->texts.at(this->index).at(i);

        if(i + 1 == this->focusIndex){
            p.setBrush(QBrush(QColor(255, 0, 0, 0.75 * 255)));

        }else{
            p.setBrush(QBrush(QColor(255, 0, 0, 0.5 * 255)));

        }

        p.setPen(QPen(QColor(0, 0, 0, 0)));

        p.drawEllipse(imageX + text.getX() * (this->imageWidth / this->file->images.at(this->index).width()) - this->RADIUS / 2, imageY + text.getY() * (this->imageHeight / this->file->images.at(this->index).height()) - this->RADIUS / 2, this->RADIUS, this->RADIUS);

        p.setPen(QPen(QColor(255, 255, 255)));
        p.drawText(QRect(imageX + text.getX() * (this->imageWidth / this->file->images.at(this->index).width()) - this->RADIUS / 2, imageY + text.getY() * (this->imageHeight / this->file->images.at(this->index).height()) - this->RADIUS / 2, this->RADIUS, this->RADIUS), Qt::AlignCenter, QString("%1").arg(i + 1));

    }

}

void Signer::previous(){
    if(this->index > 0){
        this->focusIndex = 0;
        this->index--;

        this->update();

        emit pageChanged();
        emit focusChanged();

    }

}

void Signer::next(){
    if(this->index < this->size - 1){
        this->focusIndex = 0;
        this->index++;

        this->update();

        emit pageChanged();
        emit focusChanged();

    }

}

void Signer::add(){
    this->adding = true;

}
