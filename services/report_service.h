#ifndef REPORT_SERVICE_H
#define REPORT_SERVICE_H

#include "../entities/vehicle.h"
#include <vector>

class ReportService
{
public:
    static void generateCurrentParkingsReport();
    static void generateParkingHistoryReport(const DateTime &from, const DateTime &to);
};

#endif