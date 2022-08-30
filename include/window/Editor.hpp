#ifndef GOOLNN_CANGYAN_WINDOW_EDITOR
#define GOOLNN_CANGYAN_WINDOW_EDITOR

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QSplitter>
#include <QWidget>
#include <QLabel>

#include "window/NotesViewer.hpp"
#include "window/ImageViewer.hpp"

class Editor : public QWidget{
    Q_OBJECT
    
    private:
        QVBoxLayout* layout;

        QSplitter* splitter;

        ImageViewer* imageViewer;

        QWidget* textWidget;
        QVBoxLayout* textLayout;
        QLabel* indexLabel;
        // NotesViewer* notesViewer;

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
