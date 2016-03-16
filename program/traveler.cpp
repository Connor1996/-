#include "traveler.h"

Traveler::Traveler(int id, QDateTime startTime, int strategy, int origin, int destination) :
    id(id), startTime(startTime), strategy(strategy), origin(origin), destination(destination)
{
    time(11, QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59)));
    plan = Schedule::Dijkstra(startTime, strategy, origin, destination, time);
}

void Traveler::getTotalTime(int &durationDay, int &durationHour, int &duratioMin)
{
    QDateTime endTime = time[destination];

    durationMin = ((endTime.time().minute() - startTime.time().minute()) % 60;
    durationHour = (endTime.time().hour() - startTime.time().hour() - (durationMin >= 0)?0:1) % 24;
    durationDay = (endTime.date().day() - startTime.date().day() - (durationHour >= 0)?0:1)
            % QDate::daysInMonth(startTime.date().month());

}

std::vector<Attribute> Traveler::getPlan()
{
    return this->plan;
}

void Traveler::changePlan(int strategy, int destination)
{
    this->strategy = strategy;
    this->destiantion = destination;

    plan = Schedule::Dijkstra(startTime, strategy, orgin, destiantion, time);
}

int Traveler::getID()
{
    return this->id;
}

int Traveler::getStrategy()
{
    return this->strategy;
}

QDateTime getStartTime()
{
    return this->startTime;
}

QDateTime getDeadlineTime()
{
    return this->deadlineTime;
}

int getOrigin()
{
    return this->origin;
}

int getDestination()
{
    return this->destination;
}
