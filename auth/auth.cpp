#include "auth/auth.h"
#include "../entities/user.h"
#include <vector>

// Simple in-memory user storage (replace with database in real implementation)
static std::vector<User> users = {
    {"admin", "admin123", 0},         // role 0 = Admin
    {"attendant", "attendant123", 1}, // role 1 = Attendant
    {"driver", "driver123", 2}        // role 2 = Driver
};

User *authenticateUser(const std::string &username, const std::string &password)
{
    for (auto &user : users)
    {
        if (user.username == username && user.password == password)
        {
            return new User(user);
        }
    }
    return nullptr;
}

UserRole getUserRole(const std::string &username)
{
    for (const auto &user : users)
    {
        if (user.username == username)
        {
            return static_cast<UserRole>(user.role);
        }
    }
    return UserRole::DRIVER; // default
}

bool registerUser(const std::string &username, const std::string &password, UserRole role)
{
    // Check if user exists
    for (const auto &user : users)
    {
        if (user.username == username)
        {
            return false;
        }
    }

    // Add new user
    users.push_back({username, password, static_cast<int>(role)});
    return true;
}