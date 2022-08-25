#ifndef GOOLNN_CANGYAN_WINDOW_IMAGESIGNER
#define GOOLNN_CANGYAN_WINDOW_IMAGESIGNER

#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QImage>
#include <QList>

#include "tool/CYFile.hpp"
#include "tool/Text.hpp"

class ImageViewer : public QWidget{
    Q_OBJECT
    
    private:
        const Byte RADIUS = 24;
        
        CYFile* file;

        unsigned char index;
        unsigned char size;

        // 图片缩放
        float scale;

        // 显示坐标
        float viewX;
        float viewY;

        // 图像坐标
        float imageX;
        float imageY;

        // 图像宽高
        float imageWidth;
        float imageHeight;

        bool adding;

        Byte focusIndex;

        //鼠标坐标
        int mouseX;
        int mouseY;

        float oldViewX;
        float oldViewY;

        bool moving;
    
    public:
        ImageViewer(CYFile* file);
        ~ImageViewer();

        void setFocusIndex(Byte index);

        CYFile* getCYFile();

        unsigned char getIndex();
        unsigned char getSize();
        Byte getFocusIndex();
    
    protected:
        void paintEvent(QPaintEvent*);

        void keyPressEvent(QKeyEvent*);

        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);
        void wheelEvent(QWheelEvent*);
    
    public slots:
        void previous();
        void next();

        void add();
    
    signals:
        void pageChanged();
        void focusChanged();

        void addDone();

        void tryRemove();
        void tryAdd();

};

#endif
