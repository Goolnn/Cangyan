#include <QDataStream>
#include <QBuffer>
#include <QFile>

#include "tool/CYFile.hpp"

CYFile::CYFile(QString filepath){
    this->filepath = filepath;

}

Byte CYFile::loadFile(){
    QFile file = QFile(this->filepath);

    if(file.open(QIODevice::ReadOnly)){
        QDataStream stream = QDataStream(&file);

        // 小端序流
        stream.setByteOrder(QDataStream::LittleEndian);

        // 校验文件头
        Byte header[15];
        stream.readRawData((char*)header, 15);

        if(!this->dataCompare(header, (Byte*)this->HEADER, 15)){
            file.close();

            return 1;

        }

        // 校验版本号
        Byte version[2];
        stream.readRawData((char*)version, 2);

        if(!this->dataCompare(version, (Byte*)this->VERSION, 2)){
            file.close();

            return 2;

        }

        // 加载图片
        Byte imagesCount;
        stream.readRawData((char*)&imagesCount, 1);

        for(int i = 0; i < imagesCount; i++){
            unsigned int imageSize;
            stream.readRawData((char*)&imageSize, 4);

            Byte* imageData = (Byte*)malloc(imageSize);
            stream.readRawData((char*)imageData, imageSize);

            this->images.push_back(QImage::fromData(imageData, imageSize));

            free(imageData);

            // 加载注释
            Byte textsCount;
            stream.readRawData((char*)&textsCount, 1);

            QList<Text> list;

            for(int j = 0; j < textsCount; j++){
                unsigned short x;
                unsigned short y;
                stream.readRawData((char*)&x, 2);
                stream.readRawData((char*)&y, 2);

                unsigned short textSize;
                stream.readRawData((char*)&textSize, 2);

                Byte* textData = (Byte*)malloc(textSize);
                stream.readRawData((char*)textData, textSize);

                Text text = Text(x, y, QString((const char*)textData));

                free(textData);

                list.push_back(text);

            }

            this->texts.push_back(list);

        }

        file.close();

        return 0;

    }

    return 3;

}

void CYFile::saveFile(){
    QFile file = QFile(this->filepath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QDataStream stream = QDataStream(&file);

        // 小端序流
        stream.setByteOrder(QDataStream::LittleEndian);

        stream.writeRawData((const char*)this->HEADER, 15);
        stream.writeRawData((const char*)this->VERSION, 2);

        stream << (Byte)this->images.size();

        // 写入图像数据
        for(int i = 0; i < this->images.size(); i++){
            QByteArray byteArray;
            QBuffer buffer = QBuffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            images.at(i).save(&buffer, "PNG");
            buffer.close();
            
            unsigned int imageSize = byteArray.size();

            stream << imageSize;
            stream.writeRawData(byteArray.data(), imageSize);

            // 写入注释数据
            QList<Text> lists = this->texts.at(i);

            stream << (Byte)lists.size();

            for(Text text : lists){
                stream << text.getX();
                stream << text.getY();

                unsigned short size = text.getText().toStdString().size() + 1;
                stream.writeRawData((const char*)&size, 2);
                stream.writeRawData(text.getText().toStdString().data(), size);
                
            }

        }

    }

    file.close();

    emit fileSaved();

}

void CYFile::setText(Byte page, Byte index, QString text){
    QList<Text>* list = (QList<Text>*)&(this->texts.at(page));
    Text* t = (Text*)&list->at(index);

    if(t->getText().compare(text) != 0){
        t->setText(text);

        emit fileChanged();

    }

}

void CYFile::addText(Byte page, Text text){
    QList<Text>* list = (QList<Text>*)&(this->texts.at(page));

    list->push_back(text);

    emit fileChanged();

}

void CYFile::removeText(Byte page, Byte index){
    QList<Text>* list = (QList<Text>*)&(this->texts.at(page));

    list->removeAt(index);

    emit fileChanged();

}

bool CYFile::dataCompare(Byte* data1, Byte* data2, unsigned int size){
    for(unsigned int i = 0; i < size; i++){
        if(data1[i] != data2[i]){
            return false;

        }

    }

    return true;

}
