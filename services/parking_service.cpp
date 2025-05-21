#include "services/parking_service.h"
#include "../entities/parking.h"
#include <vector>

static std::vector<Parking> parkings;

bool ParkingService::registerParking(const Parking &parking)
{
    // Check if parking code already exists
    for (const auto &p : parkings)
    {
        if (p.code == parking.code)
        {
            return false;
        }
    }

    parkings.push_back(parking);
    return true;
}

std::vector<Parking> ParkingService::getAllParkings()
{
    return parkings;
}

Parking *ParkingService::findParkingByCode(const std::string &code)
{
    for (auto &p : parkings)
    {
        if (p.code == code)
        {
            return &p;
        }
    }
    return nullptr;
}

bool ParkingService::updateParkingSpaces(const std::string &code, int spaces_change)
{
    for (auto &p : parkings)
    {
        if (p.code == code)
        {
            p.available_spaces += spaces_change;
            if (p.available_spaces < 0)
                p.available_spaces = 0;
            if (p.available_spaces > p.total_spaces)
                p.available_spaces = p.total_spaces;
            return true;
        }
    }
    return false;
}