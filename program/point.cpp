#include "point.h"

Point::Point(QWidget *parent) :
    QLabel(parent)
{

}

void Point::MoveEvent(QEvent *event)
{
    qDebug() << "moveevent";
    if(this->pos() == QPoint(250, 250))
        emit arrival();
    else if(this->pos() == QPoint(0, 0))
        emit arrival();
}

