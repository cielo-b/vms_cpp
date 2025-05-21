#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "../utils/datetime.h"

struct VehicleRecord
{
    std::string plate_number;
    std::string parking_code;
    DateTime entry_time;
    DateTime exit_time;
    float charged_amount;
    std::string owner_name;
};

#endif