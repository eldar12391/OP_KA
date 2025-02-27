#include "Room.h"
#include <limits>
#include <iostream>
Room::Room(unsigned int num, double p, RoomType t) : number(num), price(p), type(t), status(RoomStatus::Available), currClient(nullptr){}

unsigned int Room::getNumber() const { return number; }
RoomType Room::getType() const { return type; }
RoomStatus Room::getStatus() const { return status; }
double Room::getPrice() const { return price; }
Client* Room::getCurrClient() const { return currClient; }

void Room::setStatus(RoomStatus newStatus){ status = newStatus; }
void Room::assignClient(Client* client) { currClient = client; status = RoomStatus::Occupied; }
void Room::removeClient() { delete currClient; currClient = nullptr; status = RoomStatus::Available; }
void Room::addClient(){
    if (currClient != nullptr) {
        std::cout << "Room already occupied. Cannot add a new client." << std::endl;
        return; //  Комната уже занята
    }

    currClient = new Client();

    std::cout << "Enter client full name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
        std::getline(std::cin, currClient->fullName); // Используем getline для чтения ФИО с пробелами

        std::cout << "Enter check-in date: ";
        std::cin >> currClient->checkInDate;

        std::cout << "Enter check-out date: ";
        std::cin >> currClient->checkOutDate;

        std::cout << "Enter discount amount: ";
        std::cin >> currClient->discountAmount;

        std::cout << "Enter extra sum: ";
        std::cin >> currClient->extraSum;

        setStatus(RoomStatus::Occupied);  //  Изменяем статус комнаты

}
