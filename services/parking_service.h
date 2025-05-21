#ifndef PARKING_SERVICE_H
#define PARKING_SERVICE_H

#include "../entities/parking.h"
#include <vector>

class ParkingService
{
public:
    static bool registerParking(const Parking &parking);
    static std::vector<Parking> getAllParkings();
    static Parking *findParkingByCode(const std::string &code);
    static bool updateParkingSpaces(const std::string &code, int spaces_change);
};

#endif