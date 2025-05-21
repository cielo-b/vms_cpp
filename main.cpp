#include <iostream>
#include <iomanip>
#include "auth/auth.h"
#include "services/parking_service.h"
#include "services/vehicle_service.h"
#include "services/report_service.h"
#include "utils/datetime.h"

using namespace std;

void showAdminMenu();
void showAttendantMenu();
void showDriverMenu();
void handleParkingRegistration();
void handleVehicleEntry();
void handleVehicleExit();
void generateReports();

int main()
{
    string username, password;

    cout << "=== PARKING MANAGEMENT SYSTEM ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    User *user = authenticateUser(username, password);
    if (!user)
    {
        cout << "Authentication failed!" << endl;
        return 1;
    }

    UserRole role = getUserRole(username);

    switch (role)
    {
    case UserRole::ADMIN:
        showAdminMenu();
        break;
    case UserRole::ATTENDANT:
        showAttendantMenu();
        break;
    case UserRole::DRIVER:
        showDriverMenu();
        break;
    }

    delete user;
    return 0;
}

void showAdminMenu()
{
    int choice;
    do
    {
        cout << "\n=== ADMIN MENU ===" << endl;
        cout << "1. Register Parking" << endl;
        cout << "2. View All Parkings" << endl;
        cout << "3. Generate Reports" << endl;
        cout << "4. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            handleParkingRegistration();
            break;
        case 2:
            // Display all parkings
            break;
        case 3:
            generateReports();
            break;
        case 4:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);
}

void showAttendantMenu()
{
    int choice;
    do
    {
        cout << "\n=== ATTENDANT MENU ===" << endl;
        cout << "1. Record Vehicle Entry" << endl;
        cout << "2. Record Vehicle Exit" << endl;
        cout << "3. View Available Parkings" << endl;
        cout << "4. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            handleVehicleEntry();
            break;
        case 2:
            handleVehicleExit();
            break;
        case 3:
            // Display available parkings
            break;
        case 4:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);
}

void showDriverMenu()
{
    int choice;
    do
    {
        cout << "\n=== DRIVER MENU ===" << endl;
        cout << "1. View Available Parkings" << endl;
        cout << "2. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Display available parkings
            break;
        case 2:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 2);
}

void handleParkingRegistration()
{
    Parking parking;

    cout << "\nEnter Parking Code: ";
    cin >> parking.code;
    cout << "Enter Parking Name: ";
    cin.ignore();
    getline(cin, parking.name);
    cout << "Enter Location: ";
    getline(cin, parking.location);
    cout << "Enter Total Spaces: ";
    cin >> parking.total_spaces;
    parking.available_spaces = parking.total_spaces;
    cout << "Enter Charge Per Hour: ";
    cin >> parking.charge_per_hour;

    if (ParkingService::registerParking(parking))
    {
        cout << "Parking registered successfully!" << endl;
    }
    else
    {
        cout << "Failed to register parking!" << endl;
    }
}

void handleVehicleEntry()
{
    VehicleRecord record;
    DateTime now = DateTime::now();

    cout << "\nEnter Plate Number: ";
    cin >> record.plate_number;
    cout << "Enter Parking Code: ";
    cin >> record.parking_code;
    cout << "Enter Owner Name: ";
    cin.ignore();
    getline(cin, record.owner_name);

    record.entry_time = now;
    record.exit_time = DateTime(); // Default null time
    record.charged_amount = 0.0f;

    if (VehicleService::recordVehicleEntry(record))
    {
        ParkingService::updateParkingSpaces(record.parking_code, -1);
        cout << "\n=== PARKING TICKET ===" << endl;
        cout << "Plate: " << record.plate_number << endl;
        cout << "Parking: " << record.parking_code << endl;
        cout << "Entry Time: " << record.entry_time.toString() << endl;
        cout << "Owner: " << record.owner_name << endl;
        cout << "=====================" << endl;
    }
    else
    {
        cout << "Failed to record vehicle entry!" << endl;
    }
}

void handleVehicleExit()
{
    string plate_number;
    DateTime now = DateTime::now();

    cout << "\nEnter Plate Number: ";
    cin >> plate_number;

    VehicleRecord *record = VehicleService::findActiveRecord(plate_number);
    if (!record)
    {
        cout << "No active parking found for this vehicle!" << endl;
        return;
    }

    Parking *parking = ParkingService::findParkingByCode(record->parking_code);
    if (!parking)
    {
        cout << "Parking information not found!" << endl;
        return;
    }

    // Calculate duration and charge
    double hours = now.differenceInHours(record->entry_time);
    float amount = hours * parking->charge_per_hour;

    if (VehicleService::recordVehicleExit(plate_number, now, amount))
    {
        ParkingService::updateParkingSpaces(record->parking_code, 1);

        cout << "\n=== PARKING BILL ===" << endl;
        cout << "Plate: " << record->plate_number << endl;
        cout << "Parking: " << record->parking_code << endl;
        cout << "Entry Time: " << record->entry_time.toString() << endl;
        cout << "Exit Time: " << now.toString() << endl;
        cout << "Duration: " << fixed << setprecision(2) << hours << " hours" << endl;
        cout << "Charge: $" << amount << endl;
        cout << "===================" << endl;
    }
    else
    {
        cout << "Failed to record vehicle exit!" << endl;
    }
}

void generateReports()
{
    int choice;
    DateTime from, to;

    cout << "\n=== REPORT GENERATION ===" << endl;
    cout << "1. Current Parkings Report" << endl;
    cout << "2. Parking History Report" << endl;
    cout << "Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        ReportService::generateCurrentParkingsReport();
        break;
    case 2:
        cout << "Enter Start Date Time (YYYY-MM-DD HH:MM): ";
        cin >> from;
        cout << "Enter End Date Time (YYYY-MM-DD HH:MM): ";
        cin >> to;
        ReportService::generateParkingHistoryReport(from, to);
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
}