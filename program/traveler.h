#ifndef TRAVELER_H
#define TRAVELER_H

#include "attribute.h"
#include "schedule.h"

#include <vector>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <cmath>


class Traveler
{
public:
    bool isChecked;
    int id, strategy;
    int origin, destination;
    QDateTime startTime, deadlineTime, usedTime;
    QDateTime totalTime;
    std::vector<bool> throughCity;

    Traveler(int, QDateTime, QDateTime, int, int, int, bool, std::vector<bool>);
    std::vector<Attribute> getPlan();
    QDateTime getCityArrivalDateTime(int);
    QDateTime getCityDepartureDateTime(int);
    std::vector<Attribute> changePlan(int city, int strategy, int destination, QDateTime deadlineTime,
                                      bool isChecked, std::vector<bool> throughCity);


private:
    std::vector<Attribute> plan; //记录最优路径
    std::vector<QDateTime> time; //记录每个城市的到达时间
    std::vector<Attribute> Dijkstra(std::vector<bool> &, std::vector<QDateTime> &);
    void DFS(int city, std::vector<Attribute>&, std::vector<bool>&,
             std::vector<QDateTime>&, std::vector<int> &);
    void MakePlan(int, const std::vector<Attribute>&, std::vector<Attribute> &);
    void UpdateAdjacents(int, std::vector<int>&, std::vector<bool>&, std::vector<Attribute>&);
    QDateTime CalculateTime(const std::multimap<int, Attribute>::iterator&,
                                      std::vector<QDateTime>&);
    QDateTime TotalDateTime();

    int min;
    QDateTime minTime;
};

#endif // TRAVELER_H
