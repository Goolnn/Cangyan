#include <QPainter>

#include "window/NotesViewer.hpp"

NotesViewer::NotesViewer(){
    this->setMinimumHeight(this->SIZE);

}

void NotesViewer::paintEvent(QPaintEvent*){
    QPainter p = QPainter(this);

    p.setRenderHint(QPainter::Antialiasing, true);

    p.drawLine(0, 0, this->width(), this->height());
    p.drawLine(this->width(), 0, 0, this->height());

    if(this->count != 0){
        p.setBrush(QBrush(QColor(255, 0, 0)));
        p.setPen(QPen(QColor(0, 0, 0, 0)));
        p.drawEllipse(this->width() / 2 - this->RADIUS / 2, this->height() / 2 - this->RADIUS / 2, this->RADIUS, this->RADIUS);
        p.setPen(QPen(QColor(255, 255, 255)));
        p.drawText(QRect(this->width() / 2 - this->RADIUS / 2, this->height() / 2 - this->RADIUS / 2, this->RADIUS, this->RADIUS), Qt::AlignCenter, QString("%1").arg(this->index + 1));

        for(int i = 0; i < this->count; i++){
            if(this->index - i >= 0){
                p.setBrush(QBrush(QColor(255, 0, 0, 255 * 0.25)));
                p.setPen(QPen(QColor(0, 0, 0, 0)));
                p.drawEllipse(this->width() / 2 - this->RADIUS / 2 - this->RADIUS * 1.5 * i, this->height() / 2 - this->RADIUS / 2, this->RADIUS, this->RADIUS);
                p.setPen(QPen(QColor(255, 255, 255)));
                p.drawText(QRect(this->width() / 2 - this->RADIUS / 2 - this->RADIUS * 1.5 * i, this->height() / 2 - this->RADIUS / 2, this->RADIUS, this->RADIUS), Qt::AlignCenter, QString("%1").arg(this->index + 1 - i));

            }

            if(this->index + i < this->SIZE){
                p.setBrush(QBrush(QColor(255, 0, 0, 255 * 0.25)));
                p.setPen(QPen(QColor(0, 0, 0, 0)));
                p.drawEllipse(this->width() / 2 - this->RADIUS / 2 + this->RADIUS * 1.5 * i, this->height() / 2 - this->RADIUS / 2, this->RADIUS, this->RADIUS);
                p.setPen(QPen(QColor(255, 255, 255)));
                p.drawText(QRect(this->width() / 2 - this->RADIUS / 2 + this->RADIUS * 1.5 * i, this->height() / 2 - this->RADIUS / 2, this->RADIUS, this->RADIUS), Qt::AlignCenter, QString("%1").arg(this->index + 1 + i));

            }

        }

    }

}
