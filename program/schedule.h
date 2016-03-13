#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "attribute.h"

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <QString>
#include <QDate>
#include <QFile>
#include <QTextStream>

class Schedule
{
public:
    Schedule();

    std::vector<Attribute> Dijkstra(int, int, int);
    int CityToNum(QString);
    void UpdateAdjacents(int, std::vector<int>&, std::vector<bool>&,
                         std::vector<Attribute>&);

private:
    std::multimap<int, Attribute> database;

};

#endif // SCHEDULE_H
