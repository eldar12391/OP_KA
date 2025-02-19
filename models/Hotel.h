#pragma once
#include "Room.h"
#include <vector>

class Hotel{
    private:
        std::vector<Room> rooms;
    
    public:
        bool addRoom(const Room& room);

        const Room* findRoom(unsigned int number) const;

        std::vector<const Room*> getRoomsByType(RoomType type) const;


};