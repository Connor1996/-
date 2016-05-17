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
    QPixmap setPointGraph();//设置图标
    QPointF setPointPos();//设置图标位置
    QDateTime getSplitTime(QDateTime former, QDateTime later);//获取两时间点时间间隔
    QPointF getCityCor(int city);//获得城市对应坐标
    double getTimeDifference(QDateTime shorterDateTime, QDateTime longerDateTime);//获得两时间间隔时间差
    QPointF getMoveDistance(QDateTime spentTime, QDateTime start2Begin, QDateTime start2End,
                            int from, int to);//获得坐标增量
    int nextCity();//获得新计划的始发地

private slots:
    void update();//刷新画面
private:
    int state;
    QTimer * paintmstimer;
};

#endif // MAPWIDGET_H
