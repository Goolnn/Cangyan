#ifndef GOOLNN_CANGYAN_TOOL_TEXT
#define GOOLNN_CANGYAN_TOOL_TEXT

#include <QString>

class Text{
    private:
        unsigned short x;
        unsigned short y;

        QString text;
    
    public:
        Text(unsigned short x, unsigned short y, QString text);

        void setText(QString text);

        unsigned short getX();
        unsigned short getY();

        QString getText();

};

#endif
