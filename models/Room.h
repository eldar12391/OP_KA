#pragma once
#include <string>
#include "Client.h"

enum class RoomType{ Standard, Superlor, Deluxe, Suite, Apartment };
enum class RoomStatus { Available, Reserved, Occupied };

int daysBetween(const std::string& date1, const std::string& date2);

class Room
{
    private:
        unsigned int number;
        int price;
        RoomType type;
        RoomStatus status;
        Client* currClient;
    
    public:
        Room(unsigned int num, int p, RoomType t);
        Room();
        int getNumber() const;
        RoomType getType() const;
        RoomStatus getStatus() const;
        int getPrice() const;
        Client* getCurrClient() const;
        std::string getCheckInDate() const;
        std::string getCheckOutDate() const;
        int getAmountPaid() const;

        void addClient();
        void setStatus(RoomStatus newStatus);
        void assignClient(const Client& client);
        void editClient();
        void removeClient();
        void populateClient();
        void serializeToText(std::ofstream& os) const;
        void deserializeFromText(std::ifstream& is);
        std::string getTypeToStr() const;
        std::string getStatusToStr() const;

};
