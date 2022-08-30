#ifndef GOOLNN_CANGYAN_WINDOW_NOTESVIEWER
#define GOOLNN_CANGYAN_WINDOW_NOTESVIEWER

#include <QWidget>

#include "tool/Byte.hpp"

class NotesViewer : public QWidget{
    private:
        const Byte RADIUS = 24;
        const Byte SIZE = 30;

        Byte count = 30;
        Byte index = 15;
    
    public:
        NotesViewer();
    
    protected:
        void paintEvent(QPaintEvent*);

};

#endif
