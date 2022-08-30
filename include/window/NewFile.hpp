#ifndef GOOLNN_CANGYAN_WINDOW_NEWFILE
#define GOOLNN_CANGYAN_WINDOW_NEWFILE

#include <QVBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>

#include "window/ImagesManager.hpp"

class New : public QWidget{
    Q_OBJECT

    private:
        QVBoxLayout* layout;

        QHBoxLayout* nameLayout;
        QLineEdit*   nameInput;

        QScrollArea* scrollArea;
        ImagesManager* imagesManager;

        QHBoxLayout* buttonLayout;
        QPushButton* acceptButton;
        QPushButton* cancelButton;
        QPushButton* addButton;
        QPushButton* removeButton;

    public:
        New(QWidget* parent = nullptr);
        ~New();
    
    private slots:
        void add();

        void cancel();
        void accept();

        void focusChanged(Byte newIndex);

};

#endif
