#include "mapwidget.h"

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":map.jpg")));
    this->setPalette(palette);
}

