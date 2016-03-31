#ifndef TRAVELER_H
#define TRAVELER_H

#include <vector>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include "attribute.h"
#include "schedule.h"

class Traveler
{
public:
    bool isChecked;
    int id, strategy;
    int origin, destination;
    QDateTime startTime, deadlineTime, systemStartTime;
    QDateTime totalTime;
    std::vector<bool> throughCity;

    Traveler(int, QDateTime, QDateTime, QDateTime, int, int, int, bool, std::vector<bool>);
    std::vector<Attribute> getPlan();
    QDateTime getCityArrivalDateTime(int);
    QDateTime getCityDepartureDateTime(int);
    std::vector<Attribute> changePlan(int ,int);


private:
    std::vector<Attribute> plan;
    std::vector<QDateTime> time; //记录每个城市的到达时间

    QDateTime TotalDateTime();
};

#endif // TRAVELER_H
