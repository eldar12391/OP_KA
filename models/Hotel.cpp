#pragma once
#include "Hotel.h"

bool Hotel::addRoom(const Room& room){ rooms.push_back(room); }
const Room* Hotel::findRoom(unsigned int number) const {
    for(const Room& room : rooms){
        if(room.getNumber() == number){
            return &room;
        }
    }
    return nullptr;
}