#ifndef GOOLNN_CANGYAN_WINDOW_NEWFILE
#define GOOLNN_CANGYAN_WINDOW_NEWFILE

#include <QVBoxLayout>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>

class New : public QWidget{
    Q_OBJECT

    private:
        QVBoxLayout* layout;

        QHBoxLayout* nameLayout;
        QLabel*      nameLabel;
        QLineEdit*   nameInput;

        QListWidget* imagesList;

        QHBoxLayout* buttonLayout;
        QPushButton* acceptButton;
        QPushButton* cancelButton;
        QPushButton* addButton;
        QPushButton* removeButton;
        QPushButton* upButton;
        QPushButton* downButton;

    public:
        New(QWidget* parent = nullptr);
        ~New();
    
    private slots:
        void add();
        void remove();
        void up();
        void down();

        void cancel();
        void accept();

};

#endif
