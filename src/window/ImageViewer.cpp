#include <QDataStream>
#include <QPainter>
#include <QRectF>
#include <QFile>

#include <math.h>

#include "window/ImageViewer.hpp"
#include "window/Editor.hpp"

ImageViewer::ImageViewer(CYFile* file) : QWidget(nullptr){
    this->file = file;

    this->index = 0;
    this->size = this->file->images.size();

    this->focusIndex = 0;

    this->adding = false;

    this->setFocusPolicy(Qt::StrongFocus);

    // 缩放
    this->scale = 1.0;

    // 计算坐标
    this->viewX = this->file->images.at(0).width() / 2;
    this->viewY = this->file->images.at(0).height() / 2;

}

ImageViewer::~ImageViewer(){
    delete this->file;

}

void ImageViewer::setFocusIndex(Byte index){
    this->focusIndex = index;

    emit focusChanged();

}

CYFile* ImageViewer::getCYFile(){
    return this->file;

}

unsigned char ImageViewer::getIndex(){
    return this->index;

}

unsigned char ImageViewer::getSize(){
    return this->size;

}

Byte ImageViewer::getFocusIndex(){
    return this->focusIndex;

}

void ImageViewer::keyPressEvent(QKeyEvent* event){
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

    if(event->key() == Qt::Key_Q){
        if(this->focusIndex == 0){
            this->focusIndex = this->getCYFile()->texts.at(this->index).size();

        }else{
            this->focusIndex -= 1;

        }

        if(event->modifiers() == Qt::AltModifier && this->focusIndex != 0){
            Text* text = (Text*)&this->getCYFile()->texts.at(this->index).at(this->focusIndex - 1);

            this->viewX = text->getX();
            this->viewY = text->getY();

        }

        emit focusChanged();
        this->update();

    }

    if(event->key() == Qt::Key_E){
        if(this->focusIndex == this->getCYFile()->texts.at(this->index).size()){
            this->focusIndex = 0;

        }else{
            this->focusIndex += 1;

        }

        if(event->modifiers() == Qt::AltModifier && this->focusIndex != 0){
            Text* text = (Text*)&this->getCYFile()->texts.at(this->index).at(this->focusIndex - 1);

            this->viewX = text->getX();
            this->viewY = text->getY();
            
        }

        emit focusChanged();
        this->update();

    }

    if(event->key() == Qt::Key_Space){
        if(this->focusIndex != 0){
            Text* text = (Text*)&this->getCYFile()->texts.at(this->index).at(this->focusIndex - 1);

            this->viewX = text->getX();
            this->viewY = text->getY();
            
        }

        this->update();

    }

    if(event->key() == Qt::Key_R){
        this->viewX = this->getCYFile()->images.at(this->index).width() / 2;
        this->viewY = this->getCYFile()->images.at(this->index).height() / 2;

        this->scale = 1;

        this->update();

    }

}

void ImageViewer::mousePressEvent(QMouseEvent* event){
    QPoint pos = event->pos();

    this->moving = false;

    if(event->button() == Qt::MouseButton::LeftButton){
        if(this->adding){
            if(QRect(this->imageX, this->imageY, this->imageWidth, this->imageHeight).contains(pos.x(), pos.y())){
                this->file->addText(this->index, Text((pos.x() - this->imageX) * (this->file->images.at(this->index).width() / this->imageWidth), (pos.y() - this->imageY) * (this->file->images.at(this->index).height() / this->imageHeight), ""));

                QList<Text>* list = (QList<Text>*)&(this->file->texts.at(this->index));
                this->setFocusIndex(list->size());

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

                float textX = imageX + text.getX() * (this->imageWidth / this->file->images.at(this->index).width());
                float textY = imageY + text.getY() * (this->imageHeight / this->file->images.at(this->index).height());

                if(sqrt((pos.x() - textX) * (pos.x() - textX) + (pos.y() - textY) * (pos.y() - textY)) <= this->RADIUS - 10){
                    this->focusIndex = i + 1;

                    break;

                }

            }

            emit focusChanged();

            this->update();

        }

    }else if(event->button() == Qt::MouseButton::RightButton){
        if(QRect(this->imageX, this->imageY, this->imageWidth, this->imageHeight).contains(pos.x(), pos.y())){
            this->mouseX = pos.x();
            this->mouseY = pos.y();

            this->oldViewX = this->viewX;
            this->oldViewY = this->viewY;

            this->moving = true;

        }

    }else if(event->button() == Qt::MouseButton::MiddleButton){
        this->scale = 1.0;

        this->viewX = this->file->images.at(index).width() / 2;
        this->viewY = this->file->images.at(index).height() / 2;

        this->update();

    }

}

void ImageViewer::mouseMoveEvent(QMouseEvent* event){
    if(event->buttons() & Qt::MouseButton::RightButton && this->moving){
        this->viewX = this->oldViewX - (event->pos().x() - this->mouseX) / (this->imageWidth / this->file->images.at(index).width());
        this->viewY = this->oldViewY - (event->pos().y() - this->mouseY) / (this->imageHeight / this->file->images.at(index).height());

        if(this->viewX < 0){
            this->viewX = 0;

        }
        
        if(this->viewY < 0){
            this->viewY = 0;

        }

        if(this->viewX > this->file->images.at(index).width()){
            this->viewX = this->file->images.at(index).width();

        }
        
        if(this->viewY > this->file->images.at(index).height()){
            this->viewY = this->file->images.at(index).height();

        }

        this->update();

    }

}

void ImageViewer::wheelEvent(QWheelEvent* event){
    if(event->angleDelta().y() > 0){
        if(this->scale < 1 && this->scale * 1.125 > 1){
            this->scale = 1;

        }else{
            this->scale *= 1.125;

            if(this->scale > 10){
                this->scale = 10;

            }

        }

    }else{
        if(this->scale > 1 && this->scale / 1.125 < 1){
            this->scale = 1;

        }else{
            this->scale /= 1.125;

            if(this->scale < 0.25){
                this->scale = 0.25;

            }

        }

    }

    this->update();

}

void ImageViewer::paintEvent(QPaintEvent*){
    QPainter p = QPainter(this);

    p.setRenderHint(QPainter::Antialiasing, true);

    // 控件宽高
    float widgetWidth  = this->width();
    float widgetHeight = this->height();

    // 图像缩放
    if(widgetWidth / widgetHeight > (float)this->file->images.at(index).width() / this->file->images.at(index).height()){
        this->imageWidth  = widgetHeight / this->file->images.at(index).height() * this->file->images.at(index).width() * this->scale;
        this->imageHeight = widgetHeight * this->scale;

    }else{
        this->imageWidth  = widgetWidth * this->scale;
        this->imageHeight = widgetWidth / this->file->images.at(index).width() * this->file->images.at(index).height() * this->scale;

    }

    // 坐标运算
    this->imageX = widgetWidth / 2 - this->viewX * (this->imageWidth / this->file->images.at(index).width());
    this->imageY = widgetHeight / 2 - this->viewY * (this->imageHeight / this->file->images.at(index).height());

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

    // 绘制缩放倍数
    if(this->scale != 1){
        p.setBrush(QBrush(QColor(0, 0, 0, 0.25 * 255)));
        p.setPen(QPen(QColor(0, 0, 0, 0)));

        p.drawRoundedRect(10 ,10, 65, 25, 16, 16);

        p.setPen(QPen(QColor(255, 255, 255)));
        p.drawText(10, 10, 65, 25, Qt::AlignCenter, QString("x%1").arg(this->scale, 0, 'f', 2));

    }

}

void ImageViewer::previous(){
    if(this->index > 0){
        this->focusIndex = 0;
        this->index--;

        this->scale = 1.0;

        this->viewX = this->file->images.at(index).width() / 2;
        this->viewY = this->file->images.at(index).height() / 2;

        this->update();

        emit pageChanged();
        emit focusChanged();

    }

}

void ImageViewer::next(){
    if(this->index < this->size - 1){
        this->focusIndex = 0;
        this->index++;

        this->scale = 1.0;

        this->viewX = this->file->images.at(index).width() / 2;
        this->viewY = this->file->images.at(index).height() / 2;

        this->update();

        emit pageChanged();
        emit focusChanged();

    }

}

void ImageViewer::add(){
    this->adding = true;

}
