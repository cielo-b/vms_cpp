#include "services/vehicle_service.h"
#include <vector>

static std::vector<VehicleRecord> vehicleRecords;

bool VehicleService::recordVehicleEntry(const VehicleRecord &record)
{
    vehicleRecords.push_back(record);
    return true;
}

bool VehicleService::recordVehicleExit(const std::string &plate_number, const DateTime &exit_time, float amount)
{
    for (auto &record : vehicleRecords)
    {
        if (record.plate_number == plate_number && record.exit_time.toString().empty())
        {
            record.exit_time = exit_time;
            record.charged_amount = amount;
            return true;
        }
    }
    return false;
}

std::vector<VehicleRecord> VehicleService::getActiveParkings()
{
    std::vector<VehicleRecord> active;
    for (const auto &record : vehicleRecords)
    {
        if (record.exit_time.toString().empty())
        {
            active.push_back(record);
        }
    }
    return active;
}

std::vector<VehicleRecord> VehicleService::getParkingHistory(const DateTime &from, const DateTime &to)
{
    std::vector<VehicleRecord> history;
    for (const auto &record : vehicleRecords)
    {
        if (!record.exit_time.toString().empty() &&
            record.entry_time.differenceInHours(from) >= 0 &&
            record.exit_time.differenceInHours(to) <= 0)
        {
            history.push_back(record);
        }
    }
    return history;
}

VehicleRecord *VehicleService::findActiveRecord(const std::string &plate_number)
{
    for (auto &record : vehicleRecords)
    {
        if (record.plate_number == plate_number && record.exit_time.toString().empty())
        {
            return &record;
        }
    }
    return nullptr;
}