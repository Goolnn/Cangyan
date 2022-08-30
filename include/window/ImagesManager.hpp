#ifndef GOOLNN_CANGYAN_WINDOW_IAMGESMANAGER
#define GOOLNN_CANGYAN_WINDOW_IAMGESMANAGER

#include <QStringList>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWidget>

#include "tool/Byte.hpp"

class ImagesManager : public QWidget{
    Q_OBJECT

    private:
        const Byte ROW_SIZE = 6;
        const Byte INDEX_SIZE = 50;

        Byte hoverIndex;
        Byte focusIndex;

    public:
        QStringList files;
        QList<QImage> images;

        ImagesManager(QWidget* parent = nullptr);

        void addFiles(QStringList files);

        void loadFiles();

    protected:
        void paintEvent(QPaintEvent*);

        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
    
    public slots:
        void removeImage();
    
    signals:
        void focusChanged(Byte newIndex);

};

#endif
