#include <QPainter>
#include <QPointF>
#include <QRectF>
#include <QColor>
#include <QBrush>
#include <QList>
#include <QPen>

#include "window/ImagesManager.hpp"

ImagesManager::ImagesManager(QWidget* parent) : QWidget(parent){
    this->setMouseTracking(true);
    this->setFixedSize(1, 1);

    this->hoverIndex = 0;
    this->focusIndex = 0;

}

void ImagesManager::addFiles(QStringList files){
    QList<QImage> images = QList<QImage>();

    // 加载图片
    for(QString filepath : files){
        images.push_back(QImage(filepath));

    }

    // 添加图片
    if(this->focusIndex == 0){
        this->files.append(files);
        this->images.append(images);

    }else{
        for(int i = 0; i < files.size(); i++){
            this->files.insert(this->focusIndex - 1 + i, files.at(i));
            this->images.insert(this->focusIndex - 1 + i, images.at(i));

        }

    }

    this->update();

}

void ImagesManager::paintEvent(QPaintEvent*){
    QPainter p = QPainter(this);

    if(this->files.size() != 0){
        if(this->files.size() % this->ROW_SIZE == 0){
            this->setMinimumSize(this->parentWidget()->width(), this->parentWidget()->width() / this->ROW_SIZE * (this->files.size() / this->ROW_SIZE) + (this->files.size() / this->ROW_SIZE) * this->INDEX_SIZE);

        }else{
            this->setMinimumSize(this->parentWidget()->width(), this->parentWidget()->width() / this->ROW_SIZE * (this->files.size() / this->ROW_SIZE + 1) + (this->files.size() / this->ROW_SIZE + 1) * this->INDEX_SIZE);

        }

    }

    // 控件尺寸
    float imageSize  = (float)this->parentWidget()->width() / this->ROW_SIZE;

    if(this->files.size() != 0){
        if(this->hoverIndex != 0 && this->hoverIndex != this->focusIndex){
            p.setBrush(QBrush(QColor(0, 0, 0, 255 * 0.0625)));
            p.setPen(QPen(QColor(0, 0, 0, 0)));

            p.drawRect(imageSize * ((this->hoverIndex - 1) % this->ROW_SIZE), (imageSize + this->INDEX_SIZE) * ((this->hoverIndex - 1) / this->ROW_SIZE), imageSize, imageSize + this->INDEX_SIZE);

        }

        if(this->focusIndex != 0){
            p.setBrush(QBrush(QColor(0, 0, 0, 255 * 0.125)));
            p.setPen(QPen(QColor(0, 0, 0, 0)));

            p.drawRect(imageSize * ((this->focusIndex - 1) % this->ROW_SIZE), (imageSize + this->INDEX_SIZE) * ((this->focusIndex - 1) / this->ROW_SIZE), imageSize, imageSize + this->INDEX_SIZE);

        }
        
        for(int i = 0; i < this->files.size(); i++){
            QImage image = this->images.at(i);

            float imageWidth;
            float imageHeight;

            // 图像缩放
            if(1 > (float)image.width() / image.height()){
                imageWidth  = imageSize / image.height() * image.width();
                imageHeight = imageSize;

            }else{
                imageWidth  = imageSize;
                imageHeight = imageSize / image.width() * image.height();

            }

            p.setBrush(QBrush(QColor(0, 0, 0, 0)));
            p.setPen(QPen(QColor(0, 0, 0)));

            p.drawImage(QPointF(imageSize * (i % this->ROW_SIZE) + (imageSize - imageWidth) / 2, (imageSize + this->INDEX_SIZE) * (i / this->ROW_SIZE) + (imageSize - imageHeight) / 2), image.scaled(imageWidth, imageHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            p.drawText(QRectF(imageSize * (i % this->ROW_SIZE), (imageSize + this->INDEX_SIZE) * (i / this->ROW_SIZE) + imageSize, imageSize, this->INDEX_SIZE), Qt::AlignCenter, QString("%1").arg(i + 1));

        }

    }

}

void ImagesManager::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        // 控件尺寸
        float imageSize  = (float)this->parentWidget()->width() / this->ROW_SIZE;

        int width = imageSize;
        int height = imageSize + this->INDEX_SIZE;
        
        Byte index = event->pos().y() / height * this->ROW_SIZE + event->pos().x() / width + 1;

        if(index <= this->images.size()){
            this->focusIndex = index;

        }else{
            this->focusIndex = 0;

        }

        emit focusChanged(this->focusIndex);

        this->update();

    }else if(event->button() == Qt::RightButton){
        this->focusIndex = 0;
        emit focusChanged(this->focusIndex);

        this->update();

    }

}

void ImagesManager::mouseMoveEvent(QMouseEvent* event){
    float imageSize  = (float)this->parentWidget()->width() / this->ROW_SIZE;

    int width = imageSize;
    int height = imageSize + this->INDEX_SIZE;
    
    Byte index = event->pos().y() / height * this->ROW_SIZE + event->pos().x() / width + 1;

    if(index <= this->images.size()){
        this->hoverIndex = index;

    }else{
        this->hoverIndex = 0;

    }

    this->update();

}

void ImagesManager::removeImage(){
    if(this->focusIndex != 0){
        this->images.removeAt(this->focusIndex - 1);
        this->files.removeAt(this->focusIndex - 1);

        this->focusIndex = 0;
        emit focusChanged(this->focusIndex);

        this->update();

    }

}
