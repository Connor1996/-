#include "traveler.h"

Traveler::Traveler(int id, QDateTime startTime, QDateTime deadlineTime, QDateTime systemStartTime, int strategy, int origin,
                   int destination, bool isChecked, std::vector<bool> throughCity) :
    id(id), startTime(startTime), deadlineTime(deadlineTime), systemStartTime(systemStartTime), strategy(strategy), origin(origin),
    destination(destination), isChecked(isChecked), throughCity(throughCity),
    time(11, QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59)))
{
    plan = Schedule::Dijkstra(startTime, strategy, origin, destination, time);
    totalTime = TotalDateTime();
}
QDateTime Traveler::TotalDateTime()
{
    QDateTime endTime = time[destination];

    //qDebug() << endTime.time().hour() << startTime.time().hour();
    int durationMin = (endTime.time().minute() - startTime.time().minute());
    int durationHour = (endTime.time().hour() - startTime.time().hour() - (int)((durationMin >= 0)?0:1));
    int durationDay = (endTime.date().day() - startTime.date().day() - (int)((durationHour >= 0)?0:1) + startTime.date().daysInMonth())
            % startTime.date().daysInMonth();
    durationMin = (durationMin + 60) % 60;
    durationHour = (durationHour + 24) % 24;

    return QDateTime(QDate(0, 0, durationDay), QTime(durationHour, durationMin, 0));
}

std::vector<Attribute> Traveler::getPlan()
{
    return this->plan;
}

std::vector<Attribute> Traveler::changePlan(int strategy, int destination)
{
    this->strategy = strategy;
    this->destination = destination;
    this->totalTime = TotalDateTime();

    return plan = Schedule::Dijkstra(startTime, strategy, origin, destination, time);
}

QDateTime Traveler::getCityArrivalDateTime(int index)
{
    return time[index];
}

QDateTime Traveler::getCityDepartureDateTime(int index)
{
    std::vector<Attribute>::size_type id = 0;
    QTime tempTime;

    for(; id != plan.size(); id++)
        if(plan[id].from == index)
        {
            tempTime = plan[id].begin; //获得当前城市的出发时间
            break;
        }

    QDateTime DepartureDateTime = time[index];
    if(DepartureDateTime.time() <= tempTime)
        return QDateTime(DepartureDateTime.date(), tempTime);
    else
        return QDateTime(DepartureDateTime.date().addDays(1), tempTime);
}


