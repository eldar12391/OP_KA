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
        void loadFile(std::vector<Room> rooms);

        std::vector<Room> getClientsInRoomType(RoomType type) const;

        std::vector<Room> getClientsStayingLongerThan(int days) const;
        std::vector<Room> getClientsStayingShorterThan(int days) const;
        std::vector<Room> getClientsStayingEqual(int days) const;


        std::vector<Room> getClientsPayingMoreThan(int amount) const;
        std::vector<Room> getClientsPayingLessThan(int amount) const;
        std::vector<Room> getClientsLeavingWithinDays(int days) const;
        std::vector<std::pair<Room, int>> getMaxMinStay(); // Возвращает max и min в виде пары.
        std::vector<Room> getReservedRoomNumbers() const;
        std::vector<Room> getClientsNeedingToPayExtra() const;
};