#include "services/report_service.h"
#include "services/vehicle_service.h"
#include <iomanip>
#include <iostream>

void ReportService::generateCurrentParkingsReport()
{
    auto active = VehicleService::getActiveParkings();

    std::cout << "\n=== CURRENT PARKINGS REPORT ===\n";
    std::cout << std::left << std::setw(15) << "Plate Number"
              << std::setw(15) << "Parking Code"
              << std::setw(20) << "Entry Time"
              << std::setw(20) << "Owner" << "\n";

    for (const auto &record : active)
    {
        std::cout << std::setw(15) << record.plate_number
                  << std::setw(15) << record.parking_code
                  << std::setw(20) << record.entry_time.toString()
                  << std::setw(20) << record.owner_name << "\n";
    }
}

void ReportService::generateParkingHistoryReport(const DateTime &from, const DateTime &to)
{
    auto history = VehicleService::getParkingHistory(from, to);

    std::cout << "\n=== PARKING HISTORY REPORT (" << from.toString()
              << " to " << to.toString() << ") ===\n";
    std::cout << std::left << std::setw(15) << "Plate Number"
              << std::setw(15) << "Parking Code"
              << std::setw(20) << "Entry Time"
              << std::setw(20) << "Exit Time"
              << std::setw(10) << "Amount" << "\n";

    for (const auto &record : history)
    {
        std::cout << std::setw(15) << record.plate_number
                  << std::setw(15) << record.parking_code
                  << std::setw(20) << record.entry_time.toString()
                  << std::setw(20) << record.exit_time.toString()
                  << std::setw(10) << record.charged_amount << "\n";
    }
}