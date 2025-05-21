#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

#include "../entities/vehicle.h"
#include <vector>  

class VehicleService
{
public:
    static bool recordVehicleEntry(const VehicleRecord &record);
    static bool recordVehicleExit(const std::string &plate_number, const DateTime &exit_time, float amount);
    static std::vector<VehicleRecord> getActiveParkings();
    static std::vector<VehicleRecord> getParkingHistory(const DateTime &from, const DateTime &to);
    static VehicleRecord *findActiveRecord(const std::string &plate_number);
};

#endif