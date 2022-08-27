#ifndef GOOLNN_CANGYAN_WINDOW_IAMGESEDITOR
#define GOOLNN_CANGYAN_WINDOW_IAMGESEDITOR

#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>

#include "window/ImagesManager.hpp"

class ImagesList : public QWidget{
    private:
        QVBoxLayout* layout;

        QScrollArea* scrollArea;
        ImagesManager* imageManager;

        QHBoxLayout* hBox;
        QPushButton* addButton;
        QPushButton* removeButton;
        QPushButton* cancelButton;
        QPushButton* acceptButton;
    
    public:
        ImagesList(QWidget* parent = nullptr);

        ~ImagesList();

};

#endif
