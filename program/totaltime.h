#ifndef TOTALTIME
#define TOTALTIME

#include <QString>
#include <QDate>

class TotalTime
{
public:
    TotalTime();
    TotalTime(int, int,int);

    int day, hour, min;
};

#endif // TOTALTIME

