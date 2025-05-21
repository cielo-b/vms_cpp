#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "../entities/user.h"

enum class UserRole
{
    ADMIN,
    ATTENDANT,
    DRIVER
};

User *authenticateUser(const std::string &username, const std::string &password);
UserRole getUserRole(const std::string &username);
bool registerUser(const std::string &username, const std::string &password, UserRole role);

#endif