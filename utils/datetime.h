#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

class DateTime
{
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;

public:
    // Default constructor (creates a null/invalid date)
    DateTime() : year(0), month(0), day(0), hour(0), minute(0) {}

    // Constructor with parameters
    DateTime(int y, int mo, int d, int h, int mi)
        : year(y), month(mo), day(d), hour(h), minute(mi) {}

    // Get current date and time
    static DateTime now()
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);
        return DateTime(
            now->tm_year + 1900,
            now->tm_mon + 1,
            now->tm_mday,
            now->tm_hour,
            now->tm_min);
    }

    // Calculate difference in hours between two dates
    double differenceInHours(const DateTime &other) const
    {
        std::tm tm1 = {0, minute, hour, day, month - 1, year - 1900};
        std::tm tm2 = {0, other.minute, other.hour, other.day, other.month - 1, other.year - 1900};

        std::time_t time1 = std::mktime(&tm1);
        std::time_t time2 = std::mktime(&tm2);

        if (time1 == -1 || time2 == -1)
        {
            return 0.0;
        }

        double difference = std::difftime(time1, time2) / 3600.0;
        return difference;
    }

    // Convert to string representation
    std::string toString() const
    {
        std::ostringstream oss;
        oss << std::setfill('0')
            << std::setw(4) << year << "-"
            << std::setw(2) << month << "-"
            << std::setw(2) << day << " "
            << std::setw(2) << hour << ":"
            << std::setw(2) << minute;
        return oss.str();
    }

    // Input operator
    friend std::istream &operator>>(std::istream &is, DateTime &dt)
    {
        char dash1, dash2, colon, space;
        is >> dt.year >> dash1 >> dt.month >> dash2 >> dt.day >> space >> dt.hour >> colon >> dt.minute;
        return is;
    }
};

#endif