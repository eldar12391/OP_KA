#pragma once
#include "Room.h"
#include <vector>

class Hotel{
    private:
        std::vector<Room> rooms;
    
    public:
        Room* findRoom(unsigned int number);
        std::vector<Room>& getRooms();

        void addRoom(const Room& room);
        void editRoom(int number);
        void generateRooms(int N);
        std::vector<const Room*> getRoomsByType(RoomType type) const;


};