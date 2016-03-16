#include "traveler.h"

Traveler::Traveler(int id, QDateTime startTime, QDateTime deadlineTime, int strategy, int origin, int destination) :
    id(id), startTime(startTime), deadlineTime(deadlineTime), strategy(strategy), origin(origin), destination(destination),
    time(11, QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59)))
{
    plan = Schedule::Dijkstra(startTime, strategy, origin, destination, time);
}

void Traveler::getTotalTime(int &durationDay, int &durationHour, int &durationMin)
{
    QDateTime endTime = time[destination];

    durationMin = (endTime.time().minute() - startTime.time().minute()) % 60;
    durationHour = (endTime.time().hour() - startTime.time().hour() - (durationMin >= 0)?0:1) % 24;
    durationDay = (endTime.date().day() - startTime.date().day() - (durationHour >= 0)?0:1)
            % startTime.date().daysInMonth();

}

std::vector<Attribute> Traveler::getPlan()
{
    return this->plan;
}

std::vector<Attribute> Traveler::changePlan(int strategy, int destination)
{
    this->strategy = strategy;
    this->destination = destination;

    return plan = Schedule::Dijkstra(startTime, strategy, origin, destination, time);
}


