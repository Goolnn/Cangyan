#ifndef GOOLNN_CANGYAN_WINDOW_EDITOR
#define GOOLNN_CANGYAN_WINDOW_EDITOR

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QSplitter>
#include <QWidget>
#include <QLabel>

#include "window/Signer.hpp"

class Editor : public QWidget{
    Q_OBJECT
    
    private:
        QVBoxLayout* layout;

        QSplitter* splitter;

        Signer* signer;

        QWidget* textWidget;
        QVBoxLayout* textLayout;
        QTextEdit* textEdit;

        QHBoxLayout* buttonLayout;
        QPushButton* addButton;
        QPushButton* removeButton;

        QHBoxLayout* buttomLayout;
        QPushButton* previousButton;
        QLabel* pageLabel;
        QPushButton* nextButton;
    
    public:
        Editor(CYFile* file);

        ~Editor();
    
    private slots:
        void updatePage();
        void updateText();
        void updateDelete();

        void saveText();

        void add();
        void addDone();

        void remove();

};

#endif
