#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "attribute.h"

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <QString>
#include <QObject>
#include <QDate>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class Schedule
{
public:
    Schedule();

    std::vector<Attribute> Dijkstra(QTime, int, int, int);
    int CityToNum(QString);
    void MakePlan(std::vector<Attribute>&, const std::vector<Attribute>&, int, int);
    void UpdateAdjacents(int, std::vector<int>&, std::vector<bool>&,
                         std::vector<Attribute>&, QTime currentTime);

private:
    std::multimap<int, Attribute> database;

};

#endif // SCHEDULE_H
