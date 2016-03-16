#ifndef TRAVELER_H
#define TRAVELER_H

#include <vector>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include "attribute.h"

class Traveler
{
public:
    Traveler(int, QDateTime , int , int , int );

    void getTotalTime(int &, int &, int &);
    std::vector<Attribute> getPlan();
    void changePlan(int ,int);
    int getID();
    int getStrategy();
    QDateTime getStartTime();
    QDateTIme getDeadlineTime();
    int getOrigin();
    int getDestination();


private:
    int id, strategy;
    int origin, destiantion;
    QDateTime startTime, deadlineTime;

    std::vector<Attribute> plan;
    std::vector<QDateTime> time;
};

#endif // TRAVELER_H
