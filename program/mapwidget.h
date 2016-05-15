#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include "widget.h"

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
#include <QMessageBox>
#include <QTimer>
#include <QThread>

class MapWidget : public QWidget
{
public:
    MapWidget(QWidget *);
    void paintEvent(QPaintEvent *);
    QPixmap setPointGraph();
    QPointF setPointPos(const std::vector<Attribute> &path);
    QDateTime getSplitTime(QDateTime former, QDateTime later);
    QPointF getCityCor(int city);
    double getTimeDifference(QDateTime shorterDateTime, QDateTime longerDateTime);
    QPointF getMoveDistance(QDateTime spentTime, QDateTime start2Begin, QDateTime start2End,
                            int from, int to);

private slots:
    void update();
private:
    int state;
    QTimer * paintmstimer;
};

#endif // MAPWIDGET_H
