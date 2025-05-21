#ifndef PARKING_H
#define PARKING_H

#include <string>

struct Parking
{
    std::string code;
    std::string name;
    std::string location;
    int total_spaces;
    int available_spaces;
    float charge_per_hour;
};

#endif