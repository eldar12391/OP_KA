#include "Room.h"
#include <limits>
#include <iostream>

Room::Room() : number(0), price(0.0), type(RoomType::Standard), status(RoomStatus::Available), currClient(nullptr) {}  // Или любое другое значение по умолчанию
Room::Room(unsigned int num, double p, RoomType t) : number(num), price(p), type(t), status(RoomStatus::Available), currClient(nullptr){}

unsigned int Room::getNumber() const { return number; }
RoomType Room::getType() const { return type; }
RoomStatus Room::getStatus() const { return status; }
double Room::getPrice() const { return price; }
Client* Room::getCurrClient() const { return currClient; }

void Room::setStatus(RoomStatus newStatus){ status = newStatus; }
void Room::removeClient() { delete currClient; currClient = nullptr; status = RoomStatus::Available; }

void Room::assignClient() { 
    std::cout << "Введите ФИО: " << std::endl;
    std::cin >> getCurrClient()->fullName;
    
    std::cout << "Введите дату заселения: ";
    std::cin >> getCurrClient()->checkInDate;
    std::cout << std::endl;

    std::cout << "Введите дату выселения: ";
    std::cin >> getCurrClient()->checkOutDate;
    std::cout << std::endl;

    std::cout << "Введите размер скидки: ";
    std::cin >> getCurrClient()->discountAmount;
    std::cout << std::endl;

    std::cout << "Введите сумму доплаты: ";
    std::cin >> getCurrClient()->extraSum;
    std::cout << std::endl;
}

void Room::editClient() { 
    std::cout << "Выберите поле для редактирования: ";
    std::cout << "1. Дата выселения" << std::endl;
    std::cout << "2. Скидка" << std::endl;
    std::cout << "3. Доплата" << std::endl;
    std::cout << ">> ";

    int choice = 0;
    std::cin >> choice;

    switch(choice){
        case 1:
        {   std::cout << "Введите новое значание";
            std::cout << ">> ";
            std::cin >> getCurrClient()->checkOutDate;
            break;
        }
        case 2:
        {
            std::cout << "Введите новое значание";
            std::cout << ">> ";
            std::cin >> getCurrClient()->discountAmount;
            break;
        }
        case 3:
        {
            std::cout << "Введите новое значание";
            std::cout << ">> ";
            std::cin >> getCurrClient()->extraSum;
            break;
        }
        default:
        {
            std::cout << "Ошибка ввода.";
            break;
        }
    }
}

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

std::string Room::getTypeToStr() const{
    RoomType type = getType();
        switch (type) {
            case RoomType::Standard:  return "Standard";
            case RoomType::Superlor:  return "Superior";
            case RoomType::Deluxe:    return "Deluxe";
            case RoomType::Suite:     return "Suite";
            case RoomType::Apartment: return "Apartment";
            default:                  return "Неизвестный класс номера";
        }
}

std::string Room::getStatusToStr() const {
    RoomStatus status = getStatus();
    switch (status) {
        case RoomStatus::Available: return "Свободна";
        case RoomStatus::Reserved:  return "Забронирована";
        case RoomStatus::Occupied:  return "Занята";
        default:                  return "Unknown Room Status";
    }
}
