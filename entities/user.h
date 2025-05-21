#ifndef USER_H
#define USER_H

#include <string>

struct User
{
    std::string username;
    std::string password;
    int role; // 0=Admin, 1=Attendant, 2=Driver
};

#endif