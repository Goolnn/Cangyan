#ifndef GOOLNN_CANGYAN_TOOL_CYFILE
#define GOOLNN_CANGYAN_TOOL_CYFILE

#include <QString>
#include <QImage>
#include <QList>

#include "tool/Text.hpp"
#include "tool/Byte.hpp"

class CYFile : public QObject{
    Q_OBJECT

    private:
        // 文件头部
        const Byte HEADER[15] = {0xE8, 0x8B, 0x8D, 0xE7, 0x9C, 0xBC, 0xE6, 0xB1, 0x89, 0xE5, 0x8C, 0x96, 0xE7, 0xBB, 0x84};
        // 数据版本
        const Byte VERSION[2] = {0x00, 0x00};

        QString filepath;

    public:
        QList<QImage> images;
        QList<QList<Text>> texts;
        
        CYFile(QString filepath);

        Byte loadFile();
        void saveFile();

        void setText(Byte page, Byte index, QString text);
        void addText(Byte page, Text text);
        void removeText(Byte page, Byte index);
    
    private:
        bool dataCompare(Byte* data1, Byte* data2, unsigned int size);
    
    signals:
        void fileSaved();
        void fileChanged();

};

#endif
