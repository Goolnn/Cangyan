#ifndef GOOLNN_CANGYAN_WINDOW_IMAGESIGNER
#define GOOLNN_CANGYAN_WINDOW_IMAGESIGNER

#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QImage>
#include <QList>

#include "tool/CYFile.hpp"
#include "tool/Text.hpp"

class Signer : public QWidget{
    Q_OBJECT
    
    private:
        CYFile* file;

        unsigned char index;
        unsigned char size;

        // 图像坐标
        float imageX;
        float imageY;

        // 图像宽高
        float imageWidth;
        float imageHeight;

        bool adding;

        Byte focusIndex;
    
    public:
        Signer(CYFile* file);
        ~Signer();

        void setFocusIndex(Byte index);

        CYFile* getCYFile();

        unsigned char getIndex();
        unsigned char getSize();
        Byte getFocusIndex();
    
    protected:
        void paintEvent(QPaintEvent*);

        void keyPressEvent(QKeyEvent*);

        void mousePressEvent(QMouseEvent*);
    
    public slots:
        void previous();
        void next();

        void add();
    
    signals:
        void pageChanged();
        void focusChanged();

        void addDone();

};

#endif
