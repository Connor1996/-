#ifndef MAPWIDGET_H
#define MAPWIDGET_H

//#include "ui_widget.h"
#include "widget.h"
#include "point.h"
#include <QWidget>
#include <QTextEdit>
#include <QBrush>
#include <QPalette>
#include <QPixmap>
#include <QPen>
#include <QDebug>
#include <QRectF>
#include <QDateTime>
#include <QPointF>

class MapWidget : public QWidget
{
public:
    MapWidget(QWidget *);

    void paintEvent(QPaintEvent *);
    QPixmap setPointGraph();
    QPointF setPointPos(std::vector<Attribute> &path, QWidget *fatherPtr);
    QDateTime getSplitTime(QDateTime former, QDateTime later);
    QPointF getCityCor(int city);

signals:

};

#endif // MAPWIDGET_H
