#pragma once
#include <string>

struct Client{
    std::string fullName;
    std::string checkInDate;
    std::string checkOutDate;
    int discountAmount;
    int extraSum;

    Client() : fullName("Пустое поле"), checkInDate("Пустое поле"), checkOutDate("Пустое поле"), discountAmount(-1), extraSum(-1){}

};
