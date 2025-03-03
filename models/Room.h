#pragma once
#include <string>
#include "Client.h"

enum class RoomType{ Standard, Superlor, Deluxe, Suite, Apartment };
enum class RoomStatus { Available, Reserved, Occupied };

class Room
{
    private:
        unsigned int number;
        double price;
        RoomType type;
        RoomStatus status;
        Client* currClient;
    
    public:
        Room(unsigned int num, double p, RoomType t);
        Room();
        unsigned int getNumber() const;
        RoomType getType() const;
        RoomStatus getStatus() const;
        double getPrice() const;
        Client* getCurrClient() const;
        void addClient();
        void setStatus(RoomStatus newStatus);
        void assignClient();
        void editClient();
        void removeClient();
        void serializeToText(std::ofstream& os) const;
        void deserializeFromText(std::ifstream& is);
        std::string getTypeToStr() const;
        std::string getStatusToStr() const;

};
